asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	ldi r1, x
	ld r1, r2
	ld r1, r1
	
	shla r1
	add r2, r1
	neg r1
	
	ldi r0, y
	ld r0, r3
	ld r0, r0
	shla r0
	
	if
		cmp r0, r1
	is mi
		add r2, r3
		move r3, r0
	else
		ldi r0, z
		ld r0, r0
		sub r3, r0
	fi
	
	ldi r1, ans
	st r1, r0


# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
    ldi r0, ans  # Loads the address of your result into r0 for the robot
    halt         # Brings execution to a halt

# =================================
# DATA GOES BELOW
# We have set this up for you, but you will need to test your program by
# compiling and running it several times with different input data values
# (different bit-strings placed at addresses x and y)
# ---------------------------------------------------------------------

INPUTS>
x:    dc -3    # replace these numbers by your choice
y:    dc 5     # of integers for testing purposes
z:    dc 3
ENDINPUTS>

ans:  ds 1     # one byte reserved for the result
end

