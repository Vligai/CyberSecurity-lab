#include "protect.h"

void *malloc(size_t size)
{
  size_t size_p; /*size of page*/
  void *guard_p;
  char *c;
  size_t alin;
  size_t alin2;
  size_t len;
  size_t size_f;

  len = sizeof(size_t);
  size_p = getpagesize();
  size_f = size+len;
  if (size <= 0)
    return NULL;
    
  /*34 bit system use 4*/
  if ((sizeof(void *) * 8) == 32)
    {
      if((size_f % 4) != 0)
	alin = size_f + 4 - (size_f % 4);
      else
	alin = 4096;
  
      alin2 = 4096 - (alin % 4096);
     
    }
  /*64 bit system use 8*/
  else if((sizeof(void *) * 8) == 64)
    {
      if(((size + len) % 8) != 0)
	alin = size_f + 8 - (size_f % 8);
      else
	alin = 4096;
    
      alin2 = 4096 - (alin % 4096);
 
    }
  /*guard page*/
  guard_p = mmap(NULL, size_p, PROT_NONE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  if (guard_p == MAP_FAILED)
    exit(0);
    
  c = mmap(guard_p - alin2 - alin, alin + alin2, PROT_WRITE|PROT_READ, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  /*  printf("malloc: %p \n", size_f);*/
  if (c == MAP_FAILED)
    exit(0);
    
  memcpy(guard_p-alin, &alin, sizeof(size_t));
  return (guard_p - (alin - sizeof(size_t))); 
}
