#include "protect.h"

void *realloc(void *ptr ,size_t size)
{
  size_t att1;
  void *mem;
  if(ptr == NULL && size == 0)
    return NULL;
  memcpy(&att1, ptr - sizeof(size_t), sizeof(size_t));
  /*allocate memory*/
  mem = malloc(size);
  if(att1 > size)
    att1 = size;
  memcpy(mem, ptr, att1);
  free(ptr);
  return mem;
}
