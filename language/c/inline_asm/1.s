	.cpu generic+fp+simd
	.file	"1.c"
	.text
	.align	2
	.global	value_convert
	.type	value_convert, %function
value_convert:
	sub	sp, sp, #32
	str	w0, [sp, 12]
	ldr	w0, [sp, 12]
#APP
// 14 "1.c" 1
	mov x0, x0;
// 0 "" 2
#NO_APP
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	add	sp, sp, 32
	ret
	.size	value_convert, .-value_convert
	.section	.rodata
	.align	3
.LC0:
	.string	"x = %d, y = %d\n"
	.text
	.align	2
	.global	add
	.type	add, %function
add:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	w0, [x29, 28]
	str	w1, [x29, 24]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	ldr	w2, [x29, 24]
	ldr	w1, [x29, 28]
	bl	printf
	ldr	w0, [x29, 28]
#APP
// 28 "1.c" 1
	add x0, x0, x0
// 0 "" 2
#NO_APP
	str	w0, [x29, 24]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	ldr	w2, [x29, 24]
	ldr	w1, [x29, 28]
	bl	printf
	ldr	w0, [x29, 24]
	ldp	x29, x30, [sp], 32
	ret
	.size	add, .-add
	.section	.rodata
	.align	3
.LC1:
	.string	"GCC ARM Inline Assembler CookBook Demo!"
	.align	3
.LC2:
	.string	"call func value_convert with input x = %d,output : %d\n"
	.align	3
.LC3:
	.string	"call func add           with input x = %d, y = %d, output : %d\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	puts
	mov	w0, 3
	str	w0, [x29, 24]
	mov	w0, 2
	str	w0, [x29, 28]
	ldr	w0, [x29, 24]
	bl	value_convert
	mov	w1, w0
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	mov	w2, w1
	ldr	w1, [x29, 24]
	bl	printf
	ldr	w1, [x29, 28]
	ldr	w0, [x29, 24]
	bl	add
	mov	w1, w0
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	mov	w3, w1
	ldr	w2, [x29, 28]
	ldr	w1, [x29, 24]
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.9.1-16kord6) 4.9.1"
	.section	.note.GNU-stack,"",%progbits
