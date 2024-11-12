	asect	0x00
	# WRITE YOUR CODE HERE

	ldi r0, s
	ldi r1, n
	ld r1, r1
	jsr find

	ldi r1, res
	st r1, r2
	
	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
n:	dc	15 		# replace 0 by your choice of n for testing
s:	dc	"abcdefghij",0 	# replace ... by some text for testing
	ds	18 	# reserve more space in case the string from tester is longer than ours
endinputs>
res:	ds	1

find:
	while
		tst r1
	stays nz
		if 
			ld r0, r2
			tst r2
		is z
			ldi r2, 63
			rts
		else
			inc r0
			dec r1
		fi
	wend
	rts
	end
