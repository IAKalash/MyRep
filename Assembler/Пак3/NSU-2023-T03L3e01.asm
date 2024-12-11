	asect	0x00
	# WRITE YOUR CODE HERE
	
	jsr check1

	ldi r3, S
	inc r3
	
	jsr interprete
	
	jsr check2
	
	ldi r3, S
	inc r3
	jsr main


    # at this point 'result' has the answer
    ldi   r0, result
    halt
inputs>
S:	dc	"{f,a,z,q}",0 	# replace by your choice of S for testing
	ds	40	# reserve more space in case the string from tester is longer than ours
endinputs>
result: ds	4

fail:
	ldi r3, result
	ldi r0, 3
	add r0, r3
	ldi r0, 0b00111111
	st r3, r0
	rts

check1:
	ldi r3, S
	ldi r0, 123
	if 
		ld r3, r1
		cmp r1, r0
	is nz
		jsr fail
		halt
	fi
	clr r1
	clr r0
	rts
	
check2:
	ldi r3, S
	inc r3
	ldi r0, 44
	ldi r1, 27
	ld r3, r2
	if 
		cmp r2, r1
	is pl
		jsr fail
		halt
	fi
	inc r3
	while
		ld r3, r2
		tst r2
	stays nz
		if 
			cmp r2, r0
		is nz
			jsr fail
			halt
		fi
		inc r3
		ld r3, r2
		if 
			cmp r2, r1
		is pl
			jsr fail
			halt
		fi
		inc r3
	wend
	rts

interprete:
	while 
		ldi r2, 96
		ld r3, r0
		tst r0
	stays nz
		sub r0, r2
		if 
		is pl
			st r3, r2
		fi
		inc r3		
	wend
	dec r3
	if
		ldi r1, 125
		ld r3, r0
		add r2, r0
		cmp r1, r0
	is nz
		jsr fail
		halt
	fi
	clr r1
	st r3, r1
	rts
	
main:
	while
		ldi r1, 0b10000000
		ldi r2, result
		ld r3, r0
		tst r0
	stays nz
		jsr sdvig
		ld r2, r0
		or r0, r1
		st r2, r1
		inc r3
		inc r3
	wend
	rts
	
sdvig:
	dec r0
	while
		tst r0
	stays nz
		if 
			dec r0
			shr r1
		is cs
			inc r2
			ldi r1, 0b10000000
		fi
	wend
	rts
        end
