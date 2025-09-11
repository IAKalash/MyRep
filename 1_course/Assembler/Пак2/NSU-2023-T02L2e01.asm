asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	ldi r0, x
	ld r0, r0
	jsr sign
	
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
# (different bit-strings placed at address x)
# ---------------------------------------------------------------------

chet:
	if 
		shra r0
	is cc
		ldi r0, 2
	else 
		ldi r0, 1
	fi
	rts

sign:
	if 
		tst r0
	is z
		ldi r0, 99
	else
		if 
			tst r0
		is pl
			jsr chet
		else
			jsr chet
			neg r0
		fi	
	fi
	rts

INPUTS>
x:    dc  -120   # replace -18 by your choice of integers for testing
ENDINPUTS>

ans:  ds 1      # one byte reserved for the result
end


