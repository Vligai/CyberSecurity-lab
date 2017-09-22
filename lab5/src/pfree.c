#include "protect.h"

void free(void *ptr)
{
  size_t alin;
  size_t size;
  size_t x;
  size_t y;
  /*check if pointer is valid*/
  if (ptr == NULL)
    return;

  memcpy(&size, ptr - sizeof(size_t), sizeof(size_t));
  /*  printf("free size: %p \n", size);*/
  if (size == 0)
    return;
  
  alin = 4096 - (size % 4096);
  x = munmap(ptr - sizeof(size_t) - alin, size + alin);/*free from beginning of padding*/
  
  if(x < 0)
    return;

  y = munmap( ptr + size - sizeof(size_t), 4096);/*free from beginning of guard page*/
 
  if(y < 0)
    return;
}
