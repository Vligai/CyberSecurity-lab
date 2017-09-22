#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  char *mem;
  /*test 1 malloc simple malloc and free*/
  mem = (char*)malloc(1000 *sizeof(char));
  free(mem);
  
  mem = (char*)malloc(1*sizeof(char));
  free(mem);
  puts ("Malloc test went well");
  /*test 2 calloc simple calloc and free*/
  mem = (char*)calloc(1000, sizeof(char));
  free(mem);
  
  mem = (char*)calloc(1, sizeof(char));
  free(mem);
  puts("Calloc test went well");
  /*test 3 realloc simple realloc and free*/
  mem = (char*)malloc(10 *sizeof(char));  
  strcpy(mem, "123456789");
  printf("mem before realloc: %s \n", mem);
  
  mem = realloc(mem, 4 * sizeof(char));
  printf("mem after realloc: %s \n", mem);
  puts ("Realloc test went well");
  /*test 4 buffer overflow using malloc*/
  puts("overflowing the buffer:");
  char *mem2;
  mem2 = (char*)malloc(5*sizeof(char));
  strcpy(mem2, "This String Is Very Long And Will Overflow The Buffer");
  return 0;
}
