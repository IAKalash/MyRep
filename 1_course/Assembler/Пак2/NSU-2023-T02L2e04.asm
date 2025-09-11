asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	ldi r0, x
	ld r0, r0
	
	ldi r3, 0b00000010
	
	move r0, r1
	and r3, r1
	ldi r3, 0b00001000
	
	move r0, r2
	and r3, r2
	
	jsr test
	
	ldi r3, 0b00100000
	move r0, r2
	not r2
	and r3, r2
	shr r2
	shr r2
	
	jsr test
	
	if 
		tst r1
	is z
		ldi r3, 0b00000010
		or r3, r0
	else
		ldi r3, 0b11111101
		and r3, r0
	fi
	
	ldi r3, 0b00100000
	move r0, r1
	and r3, r1
	
	if 
		tst r1
	is z
		ldi r3, 0b00100000
		or r3, r0
	else
		ldi r3, 0b11011111
		and r3, r0
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
# (different bit-strings placed at addresses a, x, y and z)
# ---------------------------------------------------------------------

INPUTS>
x:    dc 0b01001011
ENDINPUTS>

ans:  ds 1     # one byte reserved for the result

test:
	if 
		shr r2
		shr r2
		cmp r2, r1
	is nz
		ldi r1, ans
		st r0, r1
		ldi r0, ans
		halt
	fi
	rts
end

