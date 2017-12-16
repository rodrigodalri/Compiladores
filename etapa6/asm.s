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
