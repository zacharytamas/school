#
#  CDA 3101, University of West Florida
#  Project 6
#
#  @author Zachary Jones <zacharytamas@gmail.com>
#  @version 1.0
#  @releasedate April 8th, 2011
#

.text
.globl main

    main:
        li $v0, 4
        la $a0, welcome
        syscall
        
        
        jal readIntAnyBase
        
        li $v0, 4
        la $a0, readReturn
        syscall
        
        li $v0, 1
        move $a0, $v1
        syscall
        
        
        li $v0, 4
        la $a0, printPrompt
        syscall
        
        li $v0, 5
        syscall
        move $a1, $v0
        
        li $v0, 4
        la $a0, printBasePrompt
        syscall
        
        li $v0, 5
        syscall
        move $a2, $v0
        
        jal printIntAnyBase

        
        li $v0, 10
        syscall
    
    
    #
    #  Reads in an integer as a string in any base from 2-36
    #
    #  @param $a1 The base to interpret the number as
    #  @return in $v1
    #
    readIntAnyBase:
        # our output will be in $v1, we're initializing it
        move $v1, $zero
        move $a2, $zero		# pointer index
        
        li $v0, 4		# print prompt to ask for string
        la $a0, readPrompt
        syscall
        
        li $v0, 8		# grab the input string
        la $a0, strBuffer
        li $a1, 32
        syscall
        
        li $v0, 4		# print prompt to ask for base
        la $a0, readBasePrompt
        syscall
        
        li $v0, 5		# read integer base
        syscall
        
        move $a1, $v0		# move that integer into $a1 register
        
        
        readLoop:
            lb $a3, strBuffer($a2)
            beq $a3, 10, readOut  # jump out if we reach the point where they hit enter
            
            mult $v1, $a1	# multiply our current value by the base
            mflo $v1		# store the mult result back into the value var
            
            bgt $a3, 122, isInvalid
            bgt $a3, 96, isLowercase
            bgt $a3, 90, isInvalid
            bgt $a3, 64, isUppercase
            bgt $a3, 57, isInvalid
            bgt $a3, 47, isDigit
            j isInvalid		# if it hasn't matched yet, it's invalid
            
            isUppercase:
            subi $a3, $a3, 55
            j continue
            
            isLowercase:
            subi $a3, $a3, 87
            j continue
            
            isDigit:
            subi $a3, $a3, 48
            j continue
                        
            isInvalid:
            move $a3, $zero
            j continue
            
            continue:
            add $v1, $v1, $a3		# add the value we calculated from this character
            addi $a2, $a2, 1		# increment pointer to the next character
            j readLoop
            
        readOut:
            jr $ra		# return, we're done.
   
   
    #
    #  Prints a string representing an integer in any base from 2-36
    #
    #  @param $a0 The integer to be printed
    #  @param $a2 The base
    #
    printIntAnyBase:
    
    	addi $v1, $zero, 1	# set the initial value to one
    	move $t0, $zero
    	
    	lengthLoop:
    	    bgt $v1, $a1, lengthDetermined
    	    mult $v1, $a2	# multiply value by the base
    	    mflo $v1		# store result in the value's place
    	    addi $t0, $t0, 1	# increment the length
    	    j lengthLoop
    	
    	lengthDetermined:    
    	    move $t1, $a1 # move the number we're converting to the quotient variable
    	    sb $zero, strBuffer($t0) # set a null terminator
    	    j decrementPointer
    	    
    	conversionLoop:
    	    beqz $t1, conversionFinished
    	    div $t1, $a2	# divide by the base, quotient is in LO, remainder in HI
    	    mflo $t1
    	    mfhi $t2
    	    bgt $t2, 9, charIsLetter
    	    # if the remainder is less than 10 it will just continue on to the block after this
    	
    	charIsDigit:
    	    addi $t3, $t2, 48
    	    j writeChar
    	
    	charIsLetter:
    	    addi $t3, $t2, 87
    	
    	writeChar:
    	    sb $t3, strBuffer($t0)  # stores the ascii character we generated in its place in the buffer
    	
    	decrementPointer:
    	    subi $t0, $t0, 1
    	    j conversionLoop

        conversionFinished:
            j printOut
                        
        printOut:
	    li $v0, 4        
            la $a0, printReturn
            syscall
            
            la $a0, strBuffer
            syscall
            jr $ra


# --------------------------------------------------------
.data
    welcome:		.asciiz	"Welcome to my glorious MIPS application.\n\n"
    readPrompt:		.asciiz "Please supply a number: "
    readBasePrompt:	.asciiz "What base is that number? "
    readReturn:		.asciiz "That number was converted to: "
    
    printPrompt:	.asciiz "\n\nPlease supply a decimal number: "
    printBasePrompt:	.asciiz "What base do you want? "
    printReturn:	.asciiz "That number was converted to: "
    strBuffer:		.space 33
    #strBuffer:		.asciiz "2f                             "
