	asect 	0x00
	# WRITE YOUR CODE HERE

	ldi r1, s
	
	ldi r3, res
	
	jsr split

	# at this point 'res' has the answer
	ldi   r0,res
	halt
res:	ds	9	# pointers to at most 8 words and the null
inputs>
s:	dc	"cats like milk",0 # replace ... by some text for testing
	ds      57      # reserve more space in case the string from tester is longer than ours
endinputs>
	
split:
	st r3, r1
	inc r3
	ldi r2, 32
	while
		ld r1, r0
		tst r0
	stays nz
		if 
			cmp r0, r2
		is z
			inc r1
			st r3, r1
			inc r3
		else
			inc r1 
		fi
	wend
	rts
	end
