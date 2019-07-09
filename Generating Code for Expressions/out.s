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
BGE $s0, 10, Temp_Label
LW $s0, i($0)
BGT $s0, 5, Temp_Label
LW $s0, i($0)
BNE $s0, 5, Temp_Label
LW $s0, i($0)
MULI $s5, $s0, 2
LI $s6, 0
L.D $f4, val
LW $s0, i($0)
LI.D $f14, 0.0
LW $s3, res($0)
L.D $f4, val
LW $s0, i($0)
LI.D $f16, 0.0
LW $s3, res($0)
LW $s3, res($0)
LW $s4, p($0)
ADDI $t1, $s4, 1
LW $s0, i($0)
BNE $s0, 2, Temp_Label
L.D $f4, val
LI.D $f28, 4.50
C.EQ.D $f4 $f28 
BC1F Temp_Label
AND $s0, $s0, $s0
LW $s0, i($0)
BGE $s0, 12, Temp_Label
LW $s0, i($0)
LW $s1, c($0)
