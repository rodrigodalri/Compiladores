	.globl	_Temporary_5
	.data
	.type	_Temporary_5, @object
	.size	_Temporary_5, 4
_Temporary_5:
	.long 0
	.globl	_Temporary_3
	.data
	.type	_Temporary_3, @object
	.size	_Temporary_3, 4
_Temporary_3:
	.long 0
	.globl	_Temporary_1
	.data
	.type	_Temporary_1, @object
	.size	_Temporary_1, 4
_Temporary_1:
	.long 0
	.globl	_Temporary_6
	.data
	.type	_Temporary_6, @object
	.size	_Temporary_6, 4
_Temporary_6:
	.long 0
	.globl	_Temporary_4
	.data
	.type	_Temporary_4, @object
	.size	_Temporary_4, 4
_Temporary_4:
	.long 0
	.globl	_Temporary_2
	.data
	.type	_Temporary_2, @object
	.size	_Temporary_2, 4
_Temporary_2:
	.long 0
	.globl	_Temporary_0
	.data
	.type	_Temporary_0, @object
	.size	_Temporary_0, 4
_Temporary_0:
	.long 0
	.globl	_0
	.data
	.type	_0, @object
	.size	_0, 4
_0:
	.long	0
	.globl	_1
	.data
	.type	_1, @object
	.size	_1, 4
_1:
	.long	1
	.globl	_5
	.data
	.type	_5, @object
	.size	_5, 4
_5:
	.long	5
	.globl	_10
	.data
	.type	_10, @object
	.size	_10, 4
_10:
	.long	10
	.globl	_11
	.data
	.type	_11, @object
	.size	_11, 4
_11:
	.long	11
	.section	.rodata
.LC0:
	.string	"%d"
	.section	.rodata
.LC1:
	.string	"%s"
	.globl	_a
	.data
	.type	_a, @object
	.size	_a, 4
_a:
	.globl	_i
	.data
	.type	_i, @object
	.size	_i, 4
_i:
	.globl	_v
	.data
	.type	_v, @object
	.size	_v, 40
_v:
	.globl	_mat
	.data
	.type	_mat, @object
	.size	_mat, 40
_mat:
	.globl	_f
	.data
	.type	_f, @object
	.size	_f, 4
_f:
	.globl	_x
	.data
	.type	_x, @object
	.size	_x, 4
_x:
	.long	0
	.globl	_n
	.data
	.type	_n, @object
	.size	_n, 4
_n:
	.long	0
	.text
	.globl main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	_10(%rip), %eax
	movl	%eax, _a(%rip)
	movl	$.LC2, %esi
	movl	$.LC1, %edi
	call	printf
	movl	$_i, %esi
	movl	$.LC0, %edi
	call	__isoc99_scanf
.Label_0:
	movl	_i(%rip), %edx
	movl	_10(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_0(%rip)
	movl	_Temporary_0(%rip), %eax
	testl	%eax, %eax
	jne	.L2
	jmp	.Label_1
.L2:	movl	_1(%rip), %eax
	movl	%eax, %edi
	movl	_a(%rip), %eax
	movl	%eax, %esi
	call	incn
	movl	%eax, _Temporary_1(%rip)
	movl	_Temporary_1(%rip), %eax
	movl	%eax, _a(%rip)
	movl	_i(%rip), %edx
	movl	_1(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _Temporary_2(%rip)
	movl	_Temporary_2(%rip), %eax
	movl	%eax, _i(%rip)
	jmp	.Label_0
.Label_1:
	movl	$.LC3, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_a(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	call	printf
	movl	$.LC4, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_a(%rip), %edx
	movl	_5(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_3(%rip)
	movl	_Temporary_3(%rip), %eax
	testl	%eax, %eax
	jne	.L3
	jmp	.Label_2
.L3:	movl	$.LC5, %esi
	movl	$.LC1, %edi
	call	printf
.Label_2:
	movl	_a(%rip), %edx
	movl	_11(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_4(%rip)
	movl	_Temporary_4(%rip), %eax
	testl	%eax, %eax
	jne	.L4
	jmp	.Label_3
.L4:.Label_3:
	movl	_a(%rip), %edx
	movl	_11(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_5(%rip)
	movl	_Temporary_5(%rip), %eax
	testl	%eax, %eax
	jne	.L5
	jmp	.Label_4
.L5:.Label_4:
	popq	%rbp
	ret
	.text
	.globl incn
	.type	incn, @function
incn:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, %eax
	movl	%eax, _x(%rip)
	movl	%esi, %eax
	movl	%eax, _n(%rip)
	movl	_x(%rip), %edx
	movl	_n(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _Temporary_6(%rip)
	movl	_Temporary_6(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl voidfunc
	.type	voidfunc, @function
voidfunc:
	pushq	%rbp
	movq	%rsp, %rbp
	popq	%rbp
	ret
