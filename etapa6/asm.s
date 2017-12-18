	.globl	_Temporary_7
	.data
	.type	_Temporary_7, @object
	.size	_Temporary_7, 4
_Temporary_7:
	.long 0
	.globl	_Temporary_12
	.data
	.type	_Temporary_12, @object
	.size	_Temporary_12, 4
_Temporary_12:
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
	.globl	_Temporary_13
	.data
	.type	_Temporary_13, @object
	.size	_Temporary_13, 4
_Temporary_13:
	.long 0
	.globl	_Temporary_14
	.data
	.type	_Temporary_14, @object
	.size	_Temporary_14, 4
_Temporary_14:
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
	.globl	_2
	.data
	.type	_2, @object
	.size	_2, 4
_2:
	.long	2
	.globl	_3
	.data
	.type	_3, @object
	.size	_3, 4
_3:
	.long	3
	.globl	_4
	.data
	.type	_4, @object
	.size	_4, 4
_4:
	.long	4
	.globl	_5
	.data
	.type	_5, @object
	.size	_5, 4
_5:
	.long	5
	.globl	_6
	.data
	.type	_6, @object
	.size	_6, 4
_6:
	.long	6
	.globl	_7
	.data
	.type	_7, @object
	.size	_7, 4
_7:
	.long	7
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
	.long	0
	.globl	_b
	.data
	.type	_b, @object
	.size	_b, 4
_b:
	.long	0
	.globl	_c
	.data
	.type	_c, @object
	.size	_c, 4
_c:
	.long	0
	.globl	_d
	.data
	.type	_d, @object
	.size	_d, 4
_d:
	.long	0
	.globl	_e
	.data
	.type	_e, @object
	.size	_e, 4
_e:
	.long	0
	.globl	_g
	.data
	.type	_g, @object
	.size	_g, 4
_g:
	.long	0
	.globl	_h
	.data
	.type	_h, @object
	.size	_h, 4
_h:
	.long	0
	.globl	_i
	.data
	.type	_i, @object
	.size	_i, 4
_i:
	.long	0
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
	.float	10.55
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
	movl	_2(%rip), %eax
	movl	%eax, _b(%rip)
	movl	_3(%rip), %eax
	movl	%eax, _c(%rip)
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
	movl	_5(%rip), %edx
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
	movl	_4(%rip), %edx
	movl	_5(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_4(%rip)
	movl	_Temporary_4(%rip), %eax
	testl	%eax, %eax
	jne	.L4
	jmp	.Label_3
.L4:	movl	$.LC6, %esi
	movl	$.LC1, %edi
	call	printf
.Label_3:
	movl	_5(%rip), %edx
	movl	_4(%rip), %eax
	cmpl	%eax, %edx
	setg	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_5(%rip)
	movl	_Temporary_5(%rip), %eax
	testl	%eax, %eax
	jne	.L5
	jmp	.Label_4
.L5:	movl	$.LC7, %esi
	movl	$.LC1, %edi
	call	printf
.Label_4:
	movl	_5(%rip), %edx
	movl	_5(%rip), %eax
	cmpl	%eax, %edx
	setle	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_6(%rip)
	movl	_Temporary_6(%rip), %eax
	testl	%eax, %eax
	jne	.L6
	jmp	.Label_5
.L6:	movl	$.LC8, %esi
	movl	$.LC1, %edi
	call	printf
.Label_5:
	movl	_6(%rip), %edx
	movl	_5(%rip), %eax
	cmpl	%eax, %edx
	setge	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_7(%rip)
	movl	_Temporary_7(%rip), %eax
	testl	%eax, %eax
	jne	.L7
	jmp	.Label_6
.L7:	movl	$.LC9, %esi
	movl	$.LC1, %edi
	call	printf
.Label_6:
	movl	_7(%rip), %edx
	movl	_5(%rip), %eax
	cmpl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_8(%rip)
	movl	_Temporary_8(%rip), %eax
	testl	%eax, %eax
	jne	.L8
	jmp	.Label_7
.L8:	movl	$.LC10, %esi
	movl	$.LC1, %edi
	call	printf
.Label_7:
	movl	_c(%rip), %edx
	movl	_b(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _Temporary_9(%rip)
	movl	_Temporary_9(%rip), %eax
	movl	%eax, _d(%rip)
	movl	$.LC11, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_d(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	call	printf
	movl	$.LC12, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_b(%rip), %edx
	movl	_c(%rip), %eax
	subl	%eax, %edx
	movl	%edx, _Temporary_10(%rip)
	movl	_Temporary_10(%rip), %eax
	movl	%eax, _e(%rip)
	movl	$.LC13, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_e(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	call	printf
	movl	$.LC14, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_c(%rip), %edx
	movl	_b(%rip), %eax
	imull %eax, %edx
	movl	%edx, _Temporary_11(%rip)
	movl	_Temporary_11(%rip), %eax
	movl	%eax, _g(%rip)
	movl	$.LC15, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_g(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	call	printf
	movl	$.LC16, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_c(%rip), %eax
	movl	_b(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%eax, _Temporary_12(%rip)
	movl	_Temporary_12(%rip), %eax
	movl	%eax, _h(%rip)
	movl	$.LC17, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_h(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	call	printf
	movl	$.LC18, %esi
	movl	$.LC1, %edi
	call	printf
	movl	_a(%rip), %edx
	movl	_11(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temporary_13(%rip)
	movl	_Temporary_13(%rip), %eax
	testl	%eax, %eax
	jne	.L9
	jmp	.Label_8
.L9:.Label_8:
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
	movl	%edx, _Temporary_14(%rip)
	movl	_Temporary_14(%rip), %eax
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
	.section	 .rodata
.LC18:
	.string "\n" 
	.section	 .rodata
.LC17:
	.string "2 / 3 = " 
	.section	 .rodata
.LC16:
	.string "\n" 
	.section	 .rodata
.LC15:
	.string "2 * 3 = " 
	.section	 .rodata
.LC14:
	.string "\n" 
	.section	 .rodata
.LC13:
	.string "2 - 3 = " 
	.section	 .rodata
.LC12:
	.string "\n" 
	.section	 .rodata
.LC11:
	.string "2 + 3 = " 
	.section	 .rodata
.LC10:
	.string "diferente funcionou\n" 
	.section	 .rodata
.LC9:
	.string "maior igual funcionou\n" 
	.section	 .rodata
.LC8:
	.string "menor igual funcionou\n" 
	.section	 .rodata
.LC7:
	.string "maior funcionou\n" 
	.section	 .rodata
.LC6:
	.string "menor funcionou\n" 
	.section	 .rodata
.LC5:
	.string "igualdade funcionou\n" 
	.section	 .rodata
.LC4:
	.string "\n" 
	.section	 .rodata
.LC3:
	.string "Incrementado algumas vezes fica " 
	.section	 .rodata
.LC2:
	.string "Digite um numero: \n" 
