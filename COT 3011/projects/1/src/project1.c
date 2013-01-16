/*
 ============================================================================
 Name        : project1.c
 Author      : Zachary Jones
 Course      : COT 3011
 Project     : 1
 Description : Demonstrating input and output of data along with basic math
               using varying types of number data types.
 ============================================================================
 */

#include <stdio.h>


// Variable definitions
char myChar = 'a';
int int1, int2, asciiTemp;
float float1, float2;
_Bool foundValidChar = 0;
_Bool triedValidChar = 0;


/**
 * Clears whatever is left in the input buffer.
 */
void clearRestOfBuffer(void) {
	char ch = getchar();

	while( ch != '\n' )
		ch = getchar();
}


int main() {

	// Data collection

	// Loop until the user inputs a valid character.
	// By the project spec only uppercase alphabetical letters are allowed.
	while(foundValidChar == 0) {
		if( (int) myChar > 64 && (int) myChar < 91) {
			foundValidChar=1;
		} else {
			if(triedValidChar == 0) {
				printf("Please supply an uppercase character: ");
				triedValidChar = 1;
			} else {
				printf("Please supply an UPPERCASE character: ");
			}

			scanf("%c", &myChar);
			clearRestOfBuffer();
		}
	}

	printf("Now an integer, please: ");
	scanf("%d", &int1);
	clearRestOfBuffer();

	printf("And how about another integer? ");
	scanf("%d", &int2);
	clearRestOfBuffer();

	printf("Now I need a floating-point number: ");
	scanf("%f", &float1);
	clearRestOfBuffer();

	printf("And another float, please: ");
	scanf("%f", &float2);
	clearRestOfBuffer();

	printf("\n");


	// Data presentation
	printf("Your character: %c\n", myChar);
	printf("ASCII code of your character: %d\n", myChar);
	printf("Your character plus 32 ASCII: %c\n", (myChar + 32));
	printf("\n");

	printf("Your two integers were: %d and %d\n", int1, int2);
	printf("The average of your integers, with int math: %d\n", ((int1 + int2)/2) );
	printf("The average of your integers, with float math: %f\n", (( (float) int1 + int2)/2) );
	printf("\n");

	printf("Your two floats were: %f and %f\n", float1, float2);
	printf("The average of your floats, with int math: %d\n", (((int) float1 + (int) float2)/2));
	printf("The average of your floats, with float math: %f", ((float1 + float2)/2));
	printf("\n");

	printf("The average of all four numbers: %8.2f", ((( int1 + int2 + float1 + float2)/4)));
	printf("\n");

	return 0;

}
