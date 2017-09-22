        .global _start

        .text
_start:
	jmp	message
got:	
        # write(1, message, 13)
	pop	%rsi
        mov     $0x69696969, %rax       # system call 1 is write
	sub	$0x69696968, %rax
        mov     $0x69696969, %rdi       # file handle 1 is stdout
	sub	$0x69696968, %rdi
        mov     $0x69696969, %rdx	# number of bytes
	sub	$0x6969695C, %rdx
        syscall                         # invoke operating system to do the write

        # exit(0)
	mov	$0x69696969, %rax
	sub	$0x6969692D, %rax
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
message:
	call 	got
        .ascii  "Hello, world\n"
