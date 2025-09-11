asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

	ldi r0, a
	inc r0
	ld r0, r0
	ldi r1, b
	inc r1
	ld r1, r1
	
	if
	cmp r0, r1
	is lt
		ldi r1, a
		ld r1, r1
		ldi r2, b
		ld r2, r2
		add r2, r1
		ldi r0, ans
		st r0, r1
		ldi r3, 0
		addc r3, r3
		inc r0
		ldi r1, a
		inc r1
		ld r1, r1
		ldi r2, b
		inc r2
		ld r2, r2
		add r2, r3
		add r1, r3
		st r0, r3
			
		ldi r0, ans
		halt
	fi
	
	if
	cmp r0, r1
	is gt
		ldi r0, a
		move r0, r2
		ld r0, r0
		ldi r1, b
		ld r1, r1
		inc r2
		ld r2, r2
		if 
		cmp r1, r0
		is hi
			dec r2
			ldi r3, 255
			sub r3, r1
			add r0, r1
			inc r1
		else
			sub r0, r1
		fi
		ldi r3, b
		inc r3
		ld r3, r3
		sub r2, r3
		ldi r0, ans
		st r0, r1
		inc r0
		st r0, r3
		
		ldi r0, ans
		halt
	fi
	
	if
	cmp r0, r1
	is eq
		ldi r0, a
		ld r0, r0
		ldi r1, b
		ld r1, r1
		if
		cmp r1, r0
		is ls
			ldi r0, a
			move r0, r2
			ld r0, r0
			ldi r1, b
			ld r1, r1
			inc r2
			ld r2, r2
			if 
			cmp r1, r0
			is hi
				dec r2
				ldi r3, 255
				sub r3, r1
				add r0, r1
				inc r1
			else
				sub r0, r1
			fi
			ldi r3, b
			inc r3
			ld r3, r3
			sub r2, r3 
			ldi r0, ans
			st r0, r1
			inc r0
			st r0, r3
			
			ldi r0, ans
			halt
		else
			ldi r1, a
			ld r1, r1
			ldi r2, b
			ld r2, r2
			add r2, r1
			ldi r0, ans
			st r0, r1
			ldi r3, 0
			addc r3, r3
			inc r0
			ldi r1, a
			inc r1
			ld r1, r1
			ldi r2, b
			inc r2
			ld r2, r2
			add r2, r3
			add r1, r3
			st r0, r3
			
			ldi r0, ans
			halt
		fi
	fi
	
	

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

INPUTS>
a:    dc  0x23,0x07   # replace two bytes by your choice of bit-srings for testing
b:    dc  0xf3,0x07   # replace two bytes by your choice of bit-srings for testing

ENDINPUTS>

ans:  ds 2      # two byte reserved for the result
end
