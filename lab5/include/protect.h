
#ifndef _PROTECT_H_
#define _PROTECT_H_

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nitems, size_t size);
void *memalign(size_t alignment, size_t size);
#endif
