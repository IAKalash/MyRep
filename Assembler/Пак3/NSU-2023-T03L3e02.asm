	asect 	0x00
	# WRITE YOUR CODE HERE

	ldi r0, x
	ldi r1, y
	ldi r3, sum



	jsr sumnums
	jsr sumnums
	jsr sumnums
	jsr sumnums
	jsr sumnums
	jsr sumnums
	jsr sumnums
	jsr sumnums
	
	# at this point 'res' has the answer
	ldi   r0,sum
	halt
inputs>
x:	dc	0x07,0xab,0x07,0xab,0x07,0xab,0x07,0xab # choose your data
y:	dc	0x07,0xab,0x07,0xab,0x07,0xab,0x07,0xab # choose your data
endinputs>
sum:	ds	8
sumnums:
	push r3
	ld r1, r3
	add r2, r3
	ld r0, r2
	add r3, r2
	pop r3
	st r3, r2
	if
	is cs
		ldi r2, 1
	else 
		ldi r2, 0
	fi
	inc r0
	inc r1
	inc r3
	rts
	end
