.data
  i:	 .word	 0
val:	 .space	 8	 # $f0
res:	 .space	 8	 # $f2
newline: .asciiz "\n"

.text
main:

# val = 2.5
li.d $f0, 2.5
s.d $f0, val

# res = val + 1
li.d $f4, 1.0
add.d $f2, $f0, $f4
s.d $f2, res

# print values for testing
li $v0, 3
mov.d $f12, $f0
syscall

li $v0, 4
la $a0, newline
syscall

li $v0, 3
mov.d $f12, $f2
syscall

# terminate program
li $v0, 10
syscall
