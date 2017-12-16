Generating shell code:
	   To generate shell code I needed to write assembly code. I used example assembly code
as a foundation to writing mine. First of all we needed to get rid of all '\0's, because
strcat() would stop its operation at first '\0'. Then I used jmp and pop operations to 
print "Hello, world\n". To generate shell code I went to s-proc folder and made an executable,
copied it into the shellcode directory and used command './sproc -p hello.sc'.

Generated shell code:
	    char shellcode[] = 
	    "\xeb\x3e\x5e\x48\xc7\xc0\x69\x69\x69\x69\x48\x2d\x68\x69\x69"
    	    "\x69\x48\xc7\xc7\x69\x69\x69\x69\x48\x81\xef\x68\x69\x69\x69"
    	    "\x48\xc7\xc2\x69\x69\x69\x69\x48\x81\xea\x5c\x69\x69\x69\x0f"
    	    "\x05\x48\xc7\xc0\x69\x69\x69\x69\x48\x2d\x2d\x69\x69\x69\x48"
   	    "\x31\xff\x0f\x05\xe8\xbd\xff\xff\xff\x48\x65\x6c\x6c\x6f\x2c"
    	    "\x20\x77\x6f\x72\x6c\x64\x0a";

Overflowing the stack:
	    To overflow the stack I first needed to find the location where NOPs and shell code
would go. To do that I used 'gdb ./stack_overflow' and found rbp and subtructed the area that 
needed to be overwritten, which gave me an address, where NOPs and shell code needed to be 
injected. Then I created an exploit.c, which would generate a .txt file with everything needed 
to be injected. exploit.c filled 264 bytes needed to overflow stack with NOPs and shell code.

Building stack overflow:
1) gcc -o exploit exploit.c
2) exploit > exploit123.txt
3) gdb ./stack_overflow
4) r < exploit123.txt

Overflowing the heap:
	    To overflow the heap I needed to do the same procedure as to overflow the stack t
find the address, where existing shell code and NOPs are to be placed. Instead of 264 bytes
exploit.c now needed to fill 262.	    

Building heap overflow:	    
1) gcc -o exploit exploit.c
2) exploit > exploit123.txt
3) gdb ./heap_overflow
4) r < exploit123.txt
