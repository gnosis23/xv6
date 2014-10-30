#include "types.h"
#include "user.h"

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
