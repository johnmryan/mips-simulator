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
ori $8, $0, 0xc			  # 1100
ori $9, $0, 0xa			  # 1010
ori $10, $0, 1			  # 1
ori $11, $0, 2			  # 2
lui $12, 0xffff			  #
ori $12, $12, 0xfffe	# -2
and $15, $8, $9			  # 0x8
or  $15, $8, $9			  # 0xe
xor $15, $8, $9			  # 0x6
andi $15, $12, 0xa0b0	# 0xa0b0
ori $15, $10, 0x1000	# 0x1001
xori $15, $8, 0xfffa	# 0xfff6
add $15, $10, $11		  # 3
add $15, $10, $12		  # 0xffffffff
add $15, $11, $12		  # 0
sub $15, $10, $11		  # 0xffffffff
sub $15, $10, $12		  # 3
addu $15, $10, $11		# 3
addu $15, $10, $12		# 0xffffffff
addu $15, $11, $12		# 0
subu $15, $10, $11		# 0xffffffff
subu $15, $10, $12		# 3
addi $15, $10, -2		  # -1
addiu $15, $10, -2		# -1
slt $15, $12, $11		  # 1
sltu $15, $12, $11		# 0
slti $15, $12, -1		  # 1
sltiu $15, $10, -1		# 1

# Loads and stores
lui $8, 0x1001			  # 0x1001
lw $15, 0($8)			    # 0x3210abcd
lh $15, 0($8)			    # 0xffffabcd
lhu $15, 0($8)			  # 0xabcd
lb $15, 0($8)			    # 0xffffffcd
lbu $15, 0($8)			  # 0xcd
lui $9, 0xdeca			  # 0xdeca
ori $9, $9, 0xfbad		# 0xfbad
sw $9, 4($8)			    # 0xdecafbad
lw $15, 4($8)			    # 0xdecafbad
ori $9, $0, 0x12		  # 0x12
sb $9, 7($8)			    # 0x12
lw $15, 4($8)			    # 0x12cafbad
ori $9, $0, 0x7654		# 0x7654
sh $9, 4($8)			    # 0x7654
lw $15, 4($8)			    # 0x 12ca7654

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

