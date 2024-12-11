	asect	0x00
	# WRITE YOUR CODE HERE

	ldi r0, 0
	ldi r3, _p
	ld r3, r2
	
	jsr str


	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
s:		dc _s 	# do NOT use labels _s and _p above!
p:		dc _p	# do NOT use labels _s and _p above!

_s:	dc	"cats like milk",0 # replace that by some string for testing
_p:	dc	"e m",0			   # replace that by some pattern for testing

	ds	40     # reserve more space in case the string from tester is longer than ours
endinputs>
res:	ds	1

str:
	while 
		ldi r1, _s
		add r0, r1
		ld r1, r1
		tst r1
	stays nz
		if 
			cmp r1, r2
		is z
			push r0
			while 
				ld r3, r2
				ldi r1, _s
				add r0, r1
				ld r1, r1
				tst r2
			stays nz
				if
					cmp r1, r2
				is z
					inc r0
					inc r3	
				else 
					ldi r3, _p
					ld r3, r2
					ldi r1, -1
					break			
				fi
			wend
			if
				tst r1
			is pl
				ldi r3, res
				pop r0
				inc r0
				st r3, r0
				ldi r0, res
				halt
			fi	
		fi
		inc r0
	wend
	ldi r1, -1
	ldi r2, res
	st r2, r1
	rts
	end
