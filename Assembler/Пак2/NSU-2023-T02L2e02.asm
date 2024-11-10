asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	ldi r0, a
	ld r0, r0
	
	move r0, r1
	
	ldi r2, 0b11110000
	and r2, r0
	rol r0
	rol r0
	rol r0
	rol r0
	
	ldi r2, 0b00001111
	and r2, r1
	
	jsr translate
	
	ldi r2, res
	st r2, r0
	
	move r1, r0
	
	jsr translate
	
	ldi r2, res
	inc r2
	st r2, r0

# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
    ldi r0, res  # Loads the address of your result into r0 for the robot
    halt         # Brings execution to a halt

# =================================
# DATA GOES BELOW
# We have set this up for you, but you will need to test your program by
# compiling and running it several times with different input data values
# (different bit-strings placed at address a)
# ---------------------------------------------------------------------

translate:
	if 
		ldi r2, 9
		cmp r0, r2
	is ls
		ldi r2, 48
		add r2, r0
	else
		ldi r2, 55
		add r2, r0
	fi
	rts

INPUTS>
a:    dc  0b11001001   # The output for this bit-string should be "E7"
ENDINPUTS>

res:  ds 2             # Two bytes reserved for the result
end


