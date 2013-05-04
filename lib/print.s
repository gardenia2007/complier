.section .data
.section .bss
	.comm temp, 32
	.comm digits,4
.section .text
.global print_int

print_int:
	# param => eax

	xor %edx, %edx
	xor %ebx, %ebx
	xor %ecx, %ecx
	
	movl $10, %esi
L_1:
	divl %esi
	pushl %edx
	xor %edx, %edx
	inc %ecx
	cmpl %ebx, %eax
	jz L_2
	jmp L_1	
	
L_2:
	movl %ecx, digits
	xor %edi, %edi
L_loop:
	popl %ebx
	addl $0x30, %ebx
	movb %bl, temp(,%edi, 1)
	inc %edi
	loop L_loop

	movl $4, %eax
	movl $1, %ebx
	movl $temp, %ecx
	movl digits, %edx
	int $0x80

	ret

