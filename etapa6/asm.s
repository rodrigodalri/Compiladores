	.globl	_Temporary_7
	.data
	.type	_Temporary_7, @object
	.size	_Temporary_7, 4
_Temporary_7:
	.long 0
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
	.globl	_Temporary_8
	.data
	.type	_Temporary_8, @object
	.size	_Temporary_8, 4
_Temporary_8:
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
	.globl	_Temporary_10
	.data
	.type	_Temporary_10, @object
	.size	_Temporary_10, 4
_Temporary_10:
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
	.globl	_Temporary_11
	.data
	.type	_Temporary_11, @object
	.size	_Temporary_11, 4
_Temporary_11:
	.long 0
	.globl	_Temporary_9
	.data
	.type	_Temporary_9, @object
	.size	_Temporary_9, 4
_Temporary_9:
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
	.globl	_3
	.data
	.type	_3, @object
	.size	_3, 4
_3:
	.long	3
	.globl	_5
	.data
	.type	_5, @object
	.size	_5, 4
_5:
	.long	5
	.globl	_7
	.data
	.type	_7, @object
	.size	_7, 4
_7:
	.long	7
	.globl	_9
	.data
	.type	_9, @object
	.size	_9, 4
_9:
	.long	9
	.globl	_105
	.data
	.type	_105, @object
	.size	_105, 4
_105:
	.long	105
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
	.globl	_65
	.data
	.type	_65, @object
	.size	_65, 4
_65:
	.long	65
	.section	.rodata
.LC0:
	.string	"%d"
	.section	.rodata
.LC1:
	.string	"%s"
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
	movl	_3(%rip), %edx
	movl	_1(%rip), %eax
	subl	%eax, %edx
	movl	%edx, _Temporary_0(%rip)
	movl	_105(%rip), %eax
	movl	%eax, _a(%rip)
	movl	_10(%rip), %edx
	movl	_5(%rip), %eax
	subl	%eax, %edx
	movl	%edx, _Temporary_1(%rip)
	movl	_Temporary_1(%rip), %eax
	movl	%eax, _a(%rip)
	movl	$.LC2, %esi
	movl	$.LC1, %edi
	call	printf
	movl	$_i, %esi
	movl	$.LC0, %edi
	call	__isoc99_scanf
.Label_0:
	movl	_i(%rip), %edx
	movl	_1(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_2(%rip)
	movl	_Temporary_2(%rip), %eax
	testl	%eax, %eax
	jne	.L2
	jmp	.Label_1
.L2:	movl	_1(%rip), %eax
	movl	%eax, %edi
	movl	_a(%rip), %eax
	movl	%eax, %esi
	call	incn
	movl	%eax, _Temporary_3(%rip)
	movl	_Temporary_3(%rip), %eax
	movl	%eax, _a(%rip)
	movl	_i(%rip), %edx
	movl	_1(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _Temporary_4(%rip)
	movl	_Temporary_4(%rip), %eax
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
	movl	_Temporary_5(%rip), %eax
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
	movl	%eax, _Temporary_6(%rip)
	movl	_Temporary_6(%rip), %eax
	testl	%eax, %eax
	jne	.L4
	jmp	.Label_3
.L4:.Label_3:
	movl	$.LC6, %esi
	movl	$.LC1, %edi
	call	printf
	movl	$_i, %esi
	movl	$.LC0, %edi
	call	__isoc99_scanf
.Label_4:
	movl	_i(%rip), %edx
	movl	_10(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_7(%rip)
	movl	_Temporary_7(%rip), %eax
	testl	%eax, %eax
	jne	.L5
	jmp	.Label_5
.L5:	movl	_1(%rip), %eax
	movl	%eax, %edi
	movl	_a(%rip), %eax
	movl	%eax, %esi
	call	incn
	movl	%eax, _Temporary_8(%rip)
	movl	_Temporary_8(%rip), %eax
	movl	%eax, _a(%rip)
	movl	_i(%rip), %edx
	movl	_1(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _Temporary_9(%rip)
	movl	_Temporary_9(%rip), %eax
	movl	%eax, _i(%rip)
	jmp	.Label_4
.Label_5:
	movl	_a(%rip), %edx
	movl	_11(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_10(%rip)
	movl	_Temporary_10(%rip), %eax
	testl	%eax, %eax
	jne	.L6
	jmp	.Label_6
.L6:.Label_6:
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
	movl	%edx, _Temporary_11(%rip)
	movl	_Temporary_11(%rip), %eax
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
