#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

/* Possible states of a thread; */
#define FREE        0x0
#define RUNNING     0x1
#define RUNNABLE    0x2

#define STACK_SIZE  8192
#define MAX_THREAD  4

lock_t glock;
struct Node {
  struct Node *next;
  int value;
};

struct Node *HEAD = 0;

static void* 
mythread(void* v)
{
  int i;
  struct Node *node;
  for (i = 0; i < 10; i++) {
    lock_acquire(&glock);
    node = (struct Node *)malloc(sizeof(struct Node));
    node->next = HEAD;
    if (HEAD == 0) {
      node->value = 1;
    } else {
      node->value = HEAD->value + 1;
    }
    HEAD = node;
    lock_release(&glock);
  }
  return (void*)0;
}

void
node_dump(struct Node *node) {
  int i = 0;
  while (node != 0) {
    printf(1, "%d ", node->value);
    if (i++ % 5 == 0) printf(1, "\n");
    node = node->next;
  }
}

int 
main(int argc, char *argv[]) 
{
  int i;
  int nthread = 5;
  lock_init(&glock);

  for (i = 0; i < nthread; i++) {
    thread_create(mythread, (void*)1);
  }

  for (i = 0; i < 5; i++) {
    printf(1, "[p=%d] main %d\n", getpid(), i);
  }

  for (i = 0; i < nthread; i++)
    wait();

  node_dump(HEAD);
  exit();
}
