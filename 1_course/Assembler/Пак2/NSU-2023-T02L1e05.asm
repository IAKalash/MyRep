asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	if
		ldi r0, x
		ld r0, r0
		ldi r1, 5
		add r1, r0
		ldi r1, y
		ld r1, r1
		
		cmp r0, r1
	is pl
		ldi r0, x
		ld r0, r1
		ld r0, r0
	
		shla r0
		add r1, r0
	else
		ldi r1, z
		ld r1, r1
		ldi r0, 7
		
		add r0, r1
		
		ldi r0, y
		ld r0, r0
		shla r0
		
		sub r1, r0
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
# (different bit-strings placed at addresses x, y and z)
# ---------------------------------------------------------------------

INPUTS>
x:    dc -6    # replace these three numbers
y:    dc 5     # by your choice of integers
z:    dc 3     #  for testing purposes
ENDINPUTS>

ans:  ds 1     # one byte reserved for the result
end

