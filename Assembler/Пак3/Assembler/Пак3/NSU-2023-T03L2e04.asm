	asect 	0x00
	# WRITE YOUR CODE HERE
	
	jsr pushpop

	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
array:	dc	 5,-1,-3,7,4,2,2,-8 # choose some numbers for testing
endinputs>
res:	ds	8

pushpop:
	ldi r0, array
	ldi r3, 8
	while 
		tst r3
	stays nz
		ld r0, r1
		if
			tst r1
		is mi
			push r1
		fi
		dec r3
		inc r0
	wend
	
	ldi r0, array
	ldi r3, 8
	
	while 
		tst r3
	stays nz
		ld r0, r1
		if
			tst r1
		is pl
			push r1
		fi
		dec r3
		inc r0
	wend
	
	ldi r0, res
	ldi r3, 8
	add r0,r3
	ldi r3, 8
	
	while 
		tst r3
	stays nz
		pop r1
		st r0, r1
		dec r3
		dec r0
	wend
	rts
	end
