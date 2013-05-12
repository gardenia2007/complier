.section .data
input :
	.int 0
ten :
	.int 10
buffer :
	.ascii "this is a buffer"
.section .bss
#.comm buffer, 32
.section .text
.global FUNC_exit, FUNC_read_int

FUNC_exit:
	# 参数为程序返回值
	mov 4(%esp), %ebx
	movl $1, %eax
	int $0x80

FUNC_read_int:
	# linux系统调用read
	movl $3, %eax
	movl $0, %ebx
	movl $buffer, %ecx
	movl $32, %edx
	int $0x80

	movl %eax ,%ecx
	subl $1, %ecx
	xorl %esi, %esi
	xorl %eax, %eax

L_loop:
	movb buffer(,%esi,1), %bl
	movzbl %bl, %ebx
	subl $0x30, %ebx
	mull ten
	addl %ebx, %eax
	incl %esi
	loop L_loop

	ret


