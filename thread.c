#include "types.h"
#include "user.h"
#include "x86.h"
#include "thread.h"

void* thread_create(void *(*func)(void*), void *arg) {
  void *stack;
  int size = 4096;
  stack = malloc(size);
  int pid = clone(stack, size);
  if (pid < 0) {
    printf(1, "clone error.\n");
    exit();
  }

  if (pid == 0) {
    func((void*)0);
    exit();
  }

  return (void*)0;
}


void lock_init(lock_t *lock) {
  lock->locked = 0;
}

void lock_acquire(lock_t *lock) {
  while(xchg(&lock->locked, 1) != 0)
    ;
}

void lock_release(lock_t *lock) {
  if (lock->locked != 1) {
    printf(1, "lock not locked!\n");
    exit();
  }

  xchg(&lock->locked, 0);
}


