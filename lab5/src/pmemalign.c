#include "protect.h"

void *memalign(size_t alignment, size_t size)
{
  size_t size_p; /*size of page*/
  void *guard_p;
  char *c;
  size_t alin;
  size_t alin2;
  size_t len;
  len = sizeof(size_t);
  size_p = getpagesize();
  /*34 bit system use 4*/
  if ((sizeof(void *) * 8) == 32)
    {
      if(((size + len) % 4) != 0)
	alin = (size + len) + 4 - ((size+len)%4);
      else
	alin = 4096;
      if((alin % 4096) != 0)
	alin2 = alin % 4096 - (alin % 4096);
      else
	alin2 = 4096;
    }
  /*64 bit system use 8*/
  else if((sizeof(void *) * 8) == 64)
    {
      if(((size + len) % 8) != 0)
	alin = (size + len) + 8 - ((size+len)%8);
      else
	alin = 4096;
      if((alin % 4096) != 0)
	alin2 = alin % 4096 - (alin % 4096);
      else
	alin2 = 4096;
    }
  /*guard page*/
  guard_p = mmap(NULL, size_p, PROT_NONE, MAP_ANONYMOUS, -1, 0);
  c = mmap(guard_p - alin2, alin2, PROT_WRITE|PROT_READ, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);

  memcpy(c-(size+len), &alin, sizeof(size_t));
  return (c-(size+len)+sizeof(size_t));
}
