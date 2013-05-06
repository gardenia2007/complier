.section .data
.section .bss
.section .text
.global FUNC_exit

FUNC_exit:
	# 参数为程序返回值
	mov 4(%esp), %ebx
	movl $1, %eax
	int $0x80


