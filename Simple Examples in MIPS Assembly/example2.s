.data
  i:	 .word	 0   # $f4 as FP
val:	 .space	 8	 # $f2
res:	 .space	 80	 # array with 10 doubles
newline: .asciiz "\n"

.text
main:

	# val = 2.5
	li.d $f2, 2.5
	s.d $f2, val

	# for loop
	li $t0, 0	# i = 0
	li $t1, 0	# address counter
	li $t2, 10	# exit condition
	for: bge $t0, $t2, end_for	# i < 10
		# temp = operation(val, i)
		# val in $f2
		# i in $t0
		jal operation

		# res[i] = temp
		s.d $f0, res($t1)
		
		# val = res[i]
		mov.d $f2, $f0
		s.d $f2, val($0)
		
		# print(res[i])
		li $v0, 3
		mov.d $f12, $f0
		syscall

		# print("\n")
		li $v0, 4
		la $a0, newline
		syscall

		# i++
		addi $t0, $t0, 1
		addi $t1, $t1, 4
		j for
	end_for:

	# terminate program
	li $v0, 10
	syscall

operation:
	# convert int to double
	mtc1.d $t0, $f4
	cvt.d.w $f4, $f4
	# $f4 contains i
	
	# res = value*i + i
	mul.d $f0, $f2, $f4
	add.d $f0, $f0, $f4
	
	# return value in $f0
	jr $ra
	
