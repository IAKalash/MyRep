	asect	0x00
	# WRITE YOUR CODE HERE

	ldi r3, S
	st r3, r0
	inc r3
	
	jsr interprete
	
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
