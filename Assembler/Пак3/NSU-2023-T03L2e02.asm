	asect 	0x00
	# WRITE YOUR CODE HERE

	ldi r0, s
	jsr toUpper

	# at this point 'res' has the answer
	ldi   r0,res
	halt
inputs>
res:
s:	dc	"abcdefghij",0 	# replace ... by some text for testing
	      # reserve more space in case the string from tester is longer than ours
endinputs>

toUpper:
	while
		ldi r2, 32
		ld r0, r1
		tst r1
	stays nz
		sub r1, r2
		st r0, r2
		inc r0
	wend
	rts
	end
