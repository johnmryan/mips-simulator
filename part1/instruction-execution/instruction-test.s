# Name and assignment number

# -----------------------------------------
# Data declarations go in this section.
.data 0x10010000
x: .word 0x3210dcba;

# -----------------------------------------
# Program code goes in this section.
.text
.globl main
.ent main
main:

# ALU operations
ori $8, $0, 0xc			  # $8 = b1100
ori $9, $0, 0xa			  # $9 = b1010
ori $10, $0, 1			  # $10 = 1
ori $11, $0, 2			  # $11 = 2
lui $12, 0xffff			  # $12 = 0xffff0000
ori $12, $12, 0xfffe	# $12 = -2
sll $15, $12, 16      # $15 = 0xfffe0000
srl $15, $12, 16      # $15 = 0xffff
and $15, $8, $9			  # $15 = 0x8
or  $15, $8, $9			  # $15 = 0xe
xor $15, $8, $9			  # $15 = 0x6
nor $15, $8, $9       # $15 = 0xfffffff1
andi $15, $12, 0xa0b0	# $15 = 0xa0b0
ori $15, $10, 0x1000	# $15 = 0x1001
xori $15, $8, 0xfffa	# $15 = 0xfff6
add $15, $10, $11		  # $15 = 3
add $15, $10, $12		  # $15 = 0xffffffff
add $15, $11, $12		  # $15 = 0
sub $15, $10, $11		  # $15 = 0xffffffff
sub $15, $10, $12		  # $15 = 3
addu $15, $10, $11		# $15 = 3
addu $15, $10, $12		# $15 = 0xffffffff
addu $15, $11, $12		# $15 = 0
subu $15, $10, $11		# $15 = 0xffffffff
subu $15, $10, $12		# $15 = 3
addi $15, $10, -2		  # $15 = -1
addiu $15, $10, -2		# $15 = -1
slt $15, $12, $11		  # $15 = 1
sltu $15, $12, $11		# $15 = 0
slti $15, $12, -1		  # $15 = 1
sltiu $15, $10, -1		# $15 = 1

# Loads and stores
lui $8, 0x1001			  # $8 = 0x10010000
lw $15, 0($8)			    # $15 = 0x3210dcba
lh $15, 0($8)			    # $15 = 0xffffdcba
lhu $15, 0($8)			  # $15 = 0xdcba
lb $15, 0($8)			    # $15 = 0xffffffba
lbu $15, 0($8)			  # $15 = 0xba
lui $9, 0xdeca			  # $9 = 0xdeca0000
ori $9, $9, 0xfbad		# $9 = 0xdecafbad
sw $9, 4($8)			    # M[10010000] = 0xdecafbad
lw $15, 4($8)			    # $15 = 0xdecafbad
ori $9, $0, 0x12		  # $9 = 0x12
sb $9, 7($8)			    # M[0x10010007] = 0x12
lw $15, 4($8)			    # $15 = 0x12cafbad
ori $9, $0, 0x7654		# $9 = 0x7654
sh $9, 4($8)			    # M[0x10010004] = 0x7654
lw $15, 4($8)			    # $15 = 0x12ca7654

# Branches and jumps
beq $0, $0, L1
ori $15, $0, 1
ori $15, $0, 2
L1:
ori $15, $0, 3
bne $0, $0, L2
ori $15, $0, 4
ori $15, $0, 5
j L3
ori $15, $0, 6
L2:
ori $15, $0, 7
L3:
ori $15, $0, 8
ori $2, $0, 0
jal func
ori $15, $0, 9

# Done, terminate program.
ori $v0, $0, 10
syscall         # exit
.end main

.globl func
.ent func
func:
ori $2, $0, 1
jr $31
ori $15, $0, 10

.end func

