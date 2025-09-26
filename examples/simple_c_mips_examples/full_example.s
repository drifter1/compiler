.data
# variables
  i:	 .word	 0   # int i
val:	 .space	 8   # double val in $f2
  p:	 .word   0   # double *p
res:	 .space	 48	 # array with 6 doubles
  c:     .byte  'c'  # char c = 'c'
# messages
   newline: .asciiz "\n"
      nbsp: .asciiz " "
iteration3: .asciiz "iteration: 3\n"

.text
main:

	# val = 2.5
	li.d $f2, 2.5
	s.d $f2, val
	
	# p = &res
	la $s0, res
	sw $s0, p($0)

	# for loop
	li $t0, 0	# i = 0
	li $t1, 0	# address counter
	for: bge $t0, 10, end_for	# i < 10
		# if(i > 5) break for loop
		# break
		if1: bgt $t0, 5, end_for
		
		elseif: bne $t0, 5, else1
			# i = 2 * i
			mul $t0, $t0, 2
			
			# val = func1()
			jal func1
			mtc1.d $v0, $f2
			cvt.d.w $f2, $f2
			
			# *p = add(val, i)
			mov.d $f0, $f2
			move $a0, $t0
			jal add_func
			s.d  $f12, 0($s0)
			
			# print(res[i])
			l.d $f12, res($t1)
			li $v0, 3
			syscall
			
			# print("\n")
			li $v0, 4
			la $a0, newline
			syscall
			
			# continue (with next iteration)
			j incr_for
		
		else1:
			# *p = add(val, i)		
			mov.d $f0, $f2
			move $a0, $t0
			jal add_func
			s.d  $f12, 0($s0)
			
			# val = res[i]
			l.d $f4, res($t1)
			mov.d $f2, $f4
			s.d $f2, val
			
			# print(res[i))
			l.d $f12, res($t1)
			li $v0, 3
			syscall
			
			# print("\n")
			li $v0, 4
			la $a0, newline
			syscall
			
			# p = p + 1
			addi $s0, $s0, 8
			sw $s0, p($0)

		# if(i == 2 && val == 4.5){ print("iteration: 3\n")}
		if2: 
			# i == 2
			bne $t0, 2, incr_for
			# val == 4.5
			li.d $f6, 4.5
			c.eq.d $f2, $f6
			# branch if false (and so not equal)
			bc1f incr_for
			
			# print("iteration: 3\n")
			li $v0, 4
			la $a0, iteration3
			syscall
			
		incr_for:
		# i++
		addi $t0, $t0, 1
		addi $t1, $t1, 8
		j for
	end_for:
	
	# while(i < 12){ ... }
	while: bge $t0, 12, end_while
		# print(i)
		li $v0, 1
		move $a0, $t0
		syscall
		
		# print(" ")
		li $v0, 4
		la $a0, nbsp
		syscall
		
		# func2(c)
		lb $a0, c($0)
		jal func2
	
		# i++
		addi $t0, $t0, 1
	
	end_while:

	# print("\n");
	li $v0, 4
	la $a0, newline
	syscall	
	
	# terminate program
	li $v0, 10
	syscall

func1:
	# return 5
	li $v0, 5
	jr $ra

func2:
	# print(c) 
	li $v0, 11
	# parameter already in $a0
	syscall
	
	jr $ra

add_func:
	# parameter a in $f0
	# parameter b in $a0
	
	# convert int b to double
	mtc1.d $a0, $f6
	cvt.d.w $f6, $f6
	
	# res = a + b + (-5)
	
	# temp = a + b
	add.d $f12, $f0, $f6
	
	# res = temp + (-5)
	li.d $f8, -5.0
	add.d $f12, $f12, $f8
	
	# result in $f12
	jr $ra
