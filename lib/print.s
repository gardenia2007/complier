.section .data
	br:
		.ascii "\n"
	neg:
		.ascii "-"
.section .bss
	.comm temp, 32
	.comm digits,4
.section .text
.global FUNC_print_int, FUNC_print_br

FUNC_print_br:
	movl $4, %eax
	movl $1, %ebx
	movl $br, %ecx
	movl $1, %edx
	int $0x80
	ret

FUNC_print_int:
	# param => eax
	mov 4(%esp), %eax

	
	cmp $0, %eax
	jge	L_pos

	pushl %eax

	movl $4, %eax
	movl $1, %ebx
	movl $neg, %ecx
	movl $1, %edx
	int $0x80

	popl %ebx
	mov $0, %eax
	subl %ebx, %eax

L_pos:

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

