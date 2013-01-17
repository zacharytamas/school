# ------------------------------------------------------
#
# project5.s
#
# CDA 3101
# Zachary Jones
#
# Accepts a string and loops through calculating 
# statistical information.
#
# ------------------------------------------------------

.text
.globl main
   
   main:
       li 	$v0, 4			# print string
       la 	$a0, prompt		# load the prompt string
       syscall
       
       li 	$v0, 8			# read_string
       li 	$a1, 40			# max length 40
       la 	$a0, string		# store in string
       syscall
       
       move	$t0, $zero		# my pointer
       move	$t1, $zero		# digits count
       move	$t2, $zero		# uppercase count
       move	$t3, $zero		# lowercase count
       move	$t4, $zero		# spaces count
       move	$t5, $zero		# other count
       
       
   loop:
       lb	$a0, string($t0)	# load the character we're dealing with into $a0
       beq	$a0, 10, stats		# if we've reached the end, jump to the stats
       addi	$t0, $t0, 1		# increment the pointer
       
       blt	$a0, 32, increment_other
       beq	$a0, 32, increment_spaces
       blt	$a0, 48, increment_other
       blt	$a0, 58, increment_digits
       blt	$a0, 65, increment_other
       blt	$a0, 91, increment_uppercase
       blt	$a0, 97, increment_other
       blt	$a0, 123, increment_lowercase
       
       j	increment_other		# we don't know what this is, so it's classified as other
       
   
   increment_digits:
       addi	$t1, $t1, 1
       j	loop
   
   increment_uppercase:
       addi	$t2, $t2, 1
       j	loop
   
   increment_lowercase:
       addi	$t3, $t3, 1
       j	loop
   
   increment_spaces:
       addi	$t4, $t4, 1
       j	loop
   
   increment_other:
       addi	$t5, $t5, 1
       j	loop
       
   stats:
       jal	newLine
       
       li 	$v0, 4			# print string
       la 	$a0, total_chars_entered
       syscall
       la	$a0, ($t0)
       li	$v0, 1
       syscall
       jal	newLine
       
       # we don't have to keep putting 4 into $v0 to print a string because newLine does it
       la	$a0, string_digits
       syscall
       la	$a0, ($t1)
       li	$v0, 1
       syscall
       jal	newLine
       
       la	$a0, string_uppercase
       syscall
       la	$a0, ($t2)
       li	$v0, 1
       syscall
       jal	newLine
       
       la	$a0, string_lowercase
       syscall
       la	$a0, ($t3)
       li	$v0, 1
       syscall
       jal	newLine
       
       la	$a0, string_spaces
       syscall
       la	$a0, ($t4)
       li	$v0, 1
       syscall
       jal	newLine
       
       la	$a0, string_other
       syscall
       la	$a0, ($t5)
       li	$v0, 1
       syscall
       jal	newLine
       
       la	$a0, string_original
       syscall
       la	$a0, string
       syscall
       jal	newLine
       
       j	end
   
   end:
       li 	$v0, 10			# exit the program
       syscall

########################################################
## Prints a new line character #########################
########################################################
newLine:
    li	$v0, 4
    la	$a0, newline
    syscall
    jr	$ra

# ------------------------------------------------------

.data
    prompt: 		.asciiz "Please enter up to 40 characters: \n"
    string:		.asciiz "                                        "
    newline:		.asciiz "\n"
    total_chars_entered:.asciiz "Total characters entered : "
    string_digits:	.asciiz "Digits                   : "
    string_uppercase:	.asciiz "Uppercase Letters        : "
    string_lowercase:	.asciiz "Lowercase Letters        : "
    string_spaces:	.asciiz "Spaces                   : "
    string_other:	.asciiz "Other Characters         : "
    string_original:	.asciiz "Original string          : "
    
    num_digits: 	.word 0
    num_uppercase:	.word 0
    num_lowercase:	.word 0
    num_spaces:		.word 0
    num_other:		.word 0
