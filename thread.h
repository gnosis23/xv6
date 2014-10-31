#ifndef _THREAD_H
#define _THREAD_H

#include "types.h"

typedef struct {
  uint locked;
} lock_t;

void* thread_create(void *(*func)(void*), void *arg);
void lock_init(lock_t *);
void lock_acquire(lock_t *);
void lock_release(lock_t *);

#endif
