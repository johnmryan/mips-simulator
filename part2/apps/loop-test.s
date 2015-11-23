	.file	1 "loop-test.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.gnu_attribute 4, 1
	.abicalls
	.option	pic0
	.globl	A
	.data
	.align	2
	.type	A, @object
	.size	A, 32
A:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.rdata
	.align	2
$LC0:
	.ascii	"sum = %d\012\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	sw	$0,28($fp)
	sw	$0,24($fp)
	j	$L2
	nop

$L3:
	lui	$2,%hi(A)
	lw	$3,24($fp)
	nop
	sll	$3,$3,2
	addiu	$2,$2,%lo(A)
	addu	$2,$3,$2
	lw	$2,0($2)
	lw	$3,28($fp)
	nop
	addu	$2,$3,$2
	sw	$2,28($fp)
	lw	$2,24($fp)
	nop
	addiu	$2,$2,1
	sw	$2,24($fp)
$L2:
	lw	$2,24($fp)
	nop
	slt	$2,$2,8
	bne	$2,$0,$L3
	nop

	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	lw	$5,28($fp)
	jal	tfp_printf
	nop

	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Sourcery CodeBench Lite 2015.05-18) 4.9.2"
