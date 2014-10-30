#include "types.h"
#include "stat.h"
#include "user.h"

/* Possible states of a thread; */
#define FREE        0x0
#define RUNNING     0x1
#define RUNNABLE    0x2

#define STACK_SIZE  8192
#define MAX_THREAD  4

void thread_create(void *stack, int size) {
  int pid = clone(stack, size);
  printf(1, "clone %d\n", pid);
}

static void 
mythread(void)
{
  int i;
  printf(1, "my thread running\n");
  for (i = 0; i < 3; i++) {
    printf(1, "[p=%d] my thread 0x%x\n",getpid(), i);
    sleep(100);
  }
  printf(1, "my thread: exit\n");
  exit();
}


int 
main(int argc, char *argv[]) 
{
  int i;
  sthread_create(mythread);
  thread_create((void*)20, 4096);

  for (i = 0; i < 5; i++) {
    printf(1, "[p=%d] main %d\n", getpid(), i);
    sleep(100);
  }
  //thread_schedule();
  wait();
  return 0;
}
