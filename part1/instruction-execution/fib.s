# -----------------------------------------
# Data declarations go in this section.
.data
A: .space 64
# -----------------------------------------
# Program code goes in this section.
.text
.globl main
main:
li $t1, 5 # $t1 = length
la $t2, A # $t2 = &A
li $t3, 0; # $t3 = 0
sw $t3, 0($t2) # A[0] = $t3
li $t3, 1; # $t3 = 1
sw $t3, 4($t2) # A[1] = $t3
li $t0, 2 # i: $t0 = 2
j loop_condition
loop_body:
la $t2, A # $t2 = &A
addi $t3, $t0, -2 # $t3 = i - 2
sll $t3, $t3, 2 # $t3 = byte offset to &A[i-2]
addu $t4, $t2, $t3 # $t4 = &A[i-2]
lw $t5, 0($t4) # $t5 = A[i-2]
addi $t3, $t0, -1 # $t3 = i - 1
sll $t3, $t3, 2 # $t3 = byte offset to &A[i-1]
addu $t4, $t2, $t3 # $t4 = &A[i-1]
lw $t6, 0($t4) # $t6 = A[i-1]
addu $t6, $t6, $t5 # $t6 = A[i-2] + A[i-1]
sll $t3, $t0, 2 # $t3 = byte offset to &A[i]
addu $t4, $t2, $t3 # $t4 = &A[i]
sw $t6 0($t4) # A[i] = A[i-2] + A[i-1]
addi $t0, $t0, 1 # ++i

loop_condition:
slt $t6, $t0, $t1 # $t6 = (i < length)
bne $t6, $0, loop_body # if (i < length) branch to loop body
# Done, terminate program.
li $v0, 10
syscall # exit
.end main