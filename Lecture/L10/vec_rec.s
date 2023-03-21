	.file	"vec_rec.c"
	.text
	.p2align 4
	.globl	newVec
	.type	newVec, @function
newVec:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	movl	$16, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	malloc@PLT
	movq	%rax, %r12
	testq	%rax, %rax
	je	.L1
	movq	%rbx, (%rax)
	xorl	%eax, %eax
	testq	%rbx, %rbx
	jg	.L10
.L3:
	movq	%rax, 8(%r12)
.L1:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L10:
	.cfi_restore_state
	movl	$8, %edi
	call	malloc@PLT
	testq	%rax, %rax
	jne	.L3
	movq	%r12, %rdi
	xorl	%r12d, %r12d
	call	free@PLT
	jmp	.L1
	.cfi_endproc
.LFE39:
	.size	newVec, .-newVec
	.p2align 4
	.globl	get_vec_element
	.type	get_vec_element, @function
get_vec_element:
.LFB40:
	.cfi_startproc
	endbr64
	xorl	%eax, %eax
	testq	%rsi, %rsi
	js	.L11
	cmpq	%rsi, (%rdi)
	jle	.L11
	movq	8(%rdi), %rax
	movq	(%rax,%rsi,8), %rax
	movq	%rax, (%rdx)
	movl	$1, %eax
.L11:
	ret
	.cfi_endproc
.LFE40:
	.size	get_vec_element, .-get_vec_element
	.p2align 4
	.globl	vec_length
	.type	vec_length, @function
vec_length:
.LFB41:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE41:
	.size	vec_length, .-vec_length
	.p2align 4
	.globl	get_vec_start
	.type	get_vec_start, @function
get_vec_start:
.LFB42:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	ret
	.cfi_endproc
.LFE42:
	.size	get_vec_start, .-get_vec_start
	.p2align 4
	.globl	combine1
	.type	combine1, @function
combine1:
.LFB43:
	.cfi_startproc
	endbr64
	movq	$0, (%rsi)
	cmpq	$0, (%rdi)
	jle	.L17
	movq	8(%rdi), %rcx
	xorl	%edx, %edx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L19:
	addq	(%rcx,%rax,8), %rdx
	addq	$1, %rax
	movq	%rdx, (%rsi)
	cmpq	(%rdi), %rax
	jl	.L19
.L17:
	ret
	.cfi_endproc
.LFE43:
	.size	combine1, .-combine1
	.p2align 4
	.globl	combine2
	.type	combine2, @function
combine2:
.LFB44:
	.cfi_startproc
	endbr64
	movq	$0, (%rsi)
	movq	(%rdi), %r9
	testq	%r9, %r9
	jle	.L22
	movq	%r9, %rcx
	xorl	%edx, %edx
	xorl	%eax, %eax
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L26:
	movq	(%rdi), %rcx
.L25:
	cmpq	%rcx, %rax
	jge	.L24
	movq	8(%rdi), %rcx
	movq	(%rcx,%rax,8), %r8
.L24:
	addq	%r8, %rdx
	addq	$1, %rax
	movq	%rdx, (%rsi)
	cmpq	%rax, %r9
	jne	.L26
.L22:
	ret
	.cfi_endproc
.LFE44:
	.size	combine2, .-combine2
	.p2align 4
	.globl	combine3
	.type	combine3, @function
combine3:
.LFB45:
	.cfi_startproc
	endbr64
	movq	$0, (%rsi)
	movq	(%rdi), %rdx
	movq	8(%rdi), %rax
	testq	%rdx, %rdx
	jle	.L27
	leaq	(%rax,%rdx,8), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L29:
	addq	(%rax), %rdx
	addq	$8, %rax
	movq	%rdx, (%rsi)
	cmpq	%rcx, %rax
	jne	.L29
.L27:
	ret
	.cfi_endproc
.LFE45:
	.size	combine3, .-combine3
	.p2align 4
	.globl	combine4
	.type	combine4, @function
combine4:
.LFB46:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rdx
	movq	8(%rdi), %rax
	testq	%rdx, %rdx
	jle	.L35
	leaq	(%rax,%rdx,8), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L34:
	addq	(%rax), %rdx
	addq	$8, %rax
	cmpq	%rcx, %rax
	jne	.L34
	movq	%rdx, (%rsi)
	ret
	.p2align 4,,10
	.p2align 3
.L35:
	xorl	%edx, %edx
	movq	%rdx, (%rsi)
	ret
	.cfi_endproc
.LFE46:
	.size	combine4, .-combine4
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
