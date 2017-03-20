	.file	"gdb_zero_length_array.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "sizeof(struct str) = %d\12\0"
LC1:
	.ascii "before f.a->s.\0"
LC2:
	.ascii "before printf f.a->s.\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$0, 28(%esp)
	movl	$4, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$LC1, (%esp)
	call	_puts
	movl	28(%esp), %eax
	addl	$4, %eax
	testl	%eax, %eax
	je	L2
	movl	$LC2, (%esp)
	call	_puts
	movl	28(%esp), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	_printf
	movl	$LC2, (%esp)
	call	_puts
L2:
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
