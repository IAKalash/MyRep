asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	ldi r0, x
	ldi r1, y
	ld r0, r0
	ld r1, r1
	
	jsr div
	
	ldi r2, remain
	st r2, r0
	ldi r2, quot
	st r2, r1


# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
    ldi r0, quot  # Loads the address of your result into r0 for the robot
    halt          # Brings execution to a halt

# =================================
# DATA GOES BELOW
# We have set this up for you, but you will need to test your program by
# compiling and running it several times with different input data values
# (different unsigned numbers placed at addresses x and y)
# ---------------------------------------------------------------------

INPUTS>
x:      dc 22   # replace these with your choice
y:      dc 6    # of unsigned numbers for testing
ENDINPUTS>

quot:   ds 1    # one byte reserved for the quotient
remain: ds 1    # one byte reserved for the remainder

div:
	clr r3
	while
		move r1, r2
		tst r0
	stays pl
		sub r0, r2
		move r2, r0
		inc r3
	wend
	add r1, r0
	dec r3
	move r3, r1
	rts
end

