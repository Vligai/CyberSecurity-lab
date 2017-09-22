

Description:
Malloc: allocates memory and returns a pointer to it
Free: frees / deallocates the memory, which was allocated by calloc, malloc or realloc
Calloc: allocates memory and returns a pointer to it. Difference between this and malloc is that calloc sets allocated memory to zero
Realloc: resizes block of memory that was previously allocated with malloc or calloc

Building and running the system:
~ make re
~ gcc -o testmain testmain.c
~ export LD_PRELOAD=/home/vligai/cs577/lab5/lib/libmyprot.so
~ ./testmain

Implementation:
Memory is allocated in the following order: padding -> metadata -> user reserved -> guard page. When implementing malloc first it was needed to generate guard page, it was done so using mmap. User reserved area and metadata was rounded up by 8, because linux lab is using 64 bit system and than that value was rounded up by size of page, which is 4096. Free: find the beginning of padding and munmap everything after it, as well as find beginning of guard page and munmap everything after it. Calloc: calloc is basicly same as malloc, but it sets allocated memory to zero. Realloc: copies content from old allocated space to a new buffer, while adjusting it if necessary.

sources used:
http://www.thegeekstuff.com/2013/06/buffer-overflow/
http://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm
(same for calloc + realloc + free)
