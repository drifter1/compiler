.data
# variables
c: .byte 'c'
i: .word 0
p: .word 0
val: .double 2.500000
res: .double 0.500000, 1.500000, 2.500000, 3.500000, 4.500000, 5.500000
# messages
msg1: .asciiz "\n"
msg2: .asciiz "\n"
msg3: .asciiz "iteration: 3\n"
msg4: .asciiz " "
msg5: .asciiz "\n"

.text
main:
LA $s3, res($0)
LW $s0, i($0)
Relational Expression
LW $s0, i($0)
Relational Expression
LW $s0, i($0)
Equality Expression
LW $s0, i($0)
MULI $s5, $s0, 2
Function Call result
L.D $f4, val
LW $s0, i($0)
Function Call result
LW $s3, res($0)
L.D $f4, val
LW $s0, i($0)
Function Call result
LW $s3, res($0)
LW $s3, res($0)
LW $s4, p($0)
ADDI $t1, $s4, 1
LW $s0, i($0)
Equality Expression
L.D $f4, val
Equality Expression
Boolean Expression
LW $s0, i($0)
Relational Expression
LW $s0, i($0)
LW $s1, c($0)
