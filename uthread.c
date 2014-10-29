#include "types.h"
#include "stat.h"
#include "user.h"

/* Possible states of a thread; */
#define FREE        0x0
#define RUNNING     0x1
#define RUNNABLE    0x2

#define STACK_SIZE  8192
#define MAX_THREAD  4

static void 
mythread(void)
{
  int i;
  printf(1, "my thread running\n");
  for (i = 0; i < 5; i++) {
    printf(1, "[p=%d] my thread 0x%x\n",getpid(), i);
    sleep(50);
  }
  printf(1, "my thread: exit\n");
  sthread_exit();
}


int 
main(int argc, char *argv[]) 
{
  int i;
  int nthread = 2;
  // thread_init();
  for (i = 0; i < nthread; i++)
    sthread_create(mythread);
  //thread_create(mythread);
  for (i = 0; i < 5; i++) {
    printf(1, "[p=%d] main %d\n", getpid(), i);
    sleep(50);
  }
  //thread_schedule();
  for (i = 0; i < nthread; i++)
    sthread_wait();
  exit();
}
