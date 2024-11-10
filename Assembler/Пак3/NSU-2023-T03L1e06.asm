asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	jsr zero
	jsr negative
	jsr positive

# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
    ldi r0, pos  # Loads the start address of your result into r0 for the robot
    halt         # Brings execution to a halt

# =================================
# DATA GOES BELOW
# We have set this up for you, but you will need to test your program by
# compiling and running it several times with different input data values
# (different arrays of numbers)
# ---------------------------------------------------------------------

INPUTS>
length:  dc 10          # the length of the array (between 1 and 10)
content: dc 2, 0, -3, 4, -9, 0, 7, 88, -92, 18
ENDINPUTS>
pos: ds 1 # 1 byte each for the three result values
neg: ds 1
zer: ds 1

zero:
	clr r3
	ldi r1, content
	ldi r2, length
	ld r2, r2
	while
		ld r1, r0
		dec r2
		inc r1
		tst r2
	stays pl
		if 
			tst r0
		is z
			inc r3
		fi
	wend
	ldi r1, zer
	st r1, r3
	rts
	
negative:
	clr r3
	ldi r1, content
	ldi r2, length
	ld r2, r2
	while
		ld r1, r0
		dec r2
		inc r1
		tst r2
	stays pl
		if 
			tst r0
		is mi
			inc r3
		fi
	wend
	ldi r1, neg
	st r1, r3
	rts
	
positive:
	ldi r0, length
	ldi r1, neg
	ldi r2, zer
	ld r0, r0
	ld r1, r1
	ld r2, r2
	sub r0, r1
	sub r1, r2
	ldi r0, pos
	st r0, r2
	rts
end

