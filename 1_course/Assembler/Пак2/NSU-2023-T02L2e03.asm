asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	ldi r0, x
	ld r0, r0
	
	ldi r3, 0b10000000
	
	jsr test
	jsr test
	jsr test
	jsr test
	
	ldi r0, ans
	ldi r1, 1
	st r0, r1


# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
    
    halt         # Brings execution to a halt

# =================================
# DATA GOES BELOW
# We have set this up for you, but you will need to test your program by
# compiling and running it several times with different input data values
# (different bit-strings placed at addresses a, x, y and z)
# ---------------------------------------------------------------------

INPUTS>
x:    dc 0b11001111
ENDINPUTS>

ans:  ds 1     # one byte reserved for the result

test: 
	if 
		move r0, r1
		move r0, r2
		and r3, r1
		shr r3
		and r3, r2
		shr r3
		shla r2
		cmp r2, r1
	is nz
		ldi r1, 0
		ldi r0, ans
		st r0, r1
		halt
	fi
	rts
end

