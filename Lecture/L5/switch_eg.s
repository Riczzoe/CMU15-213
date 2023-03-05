	.file	"switch_eg.c"
	.text
	.globl	switch_eg
	.type	switch_eg, @function
switch_eg:
.LFB0:
	.cfi_startproc
	endbr64
	cmpq	$103, %rsi
	je	.L2
	jg	.L3
	cmpq	$100, %rsi
	je	.L4
	cmpq	$102, %rsi
	jne	.L8
	addq	$10, %rdi
.L2:
	addq	$11, %rdi
.L6:
	movq	%rdi, (%rdx)
	ret
.L8:
	movl	$0, %edi
	jmp	.L6
.L3:
	cmpq	$104, %rsi
	je	.L7
	cmpq	$1000000, %rsi
	jne	.L9
.L7:
	imulq	%rdi, %rdi
	jmp	.L6
.L9:
	movl	$0, %edi
	jmp	.L6
.L4:
	leaq	(%rdi,%rdi,2), %rax
	leaq	(%rdi,%rax,4), %rdi
	jmp	.L6
	.cfi_endproc
.LFE0:
	.size	switch_eg, .-switch_eg
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
