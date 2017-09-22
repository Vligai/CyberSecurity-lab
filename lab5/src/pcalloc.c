#include "protect.h"

void *calloc(size_t nitems,size_t size)
{
  if (nitems == 0)
    return NULL;
  if(size == 0)
    return NULL;
  return malloc(nitems*size);
}
