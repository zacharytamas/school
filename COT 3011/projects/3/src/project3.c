/*
 ============================================================================
 Name        : project3.c
 Author      : Zachary Jones
 Version     : 1.0
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


/**
 * Clears whatever is left in the input buffer.
 */
void clearRestOfBuffer(void) {
	char ch = getchar();

	while( ch != '\n' )
		ch = getchar();
}


int main(void) {

	int wantsToPlay = 1, guessing=1;
	int num, guess, attempts = 0;
	int gamesPlayed = 0, totalGuesses = 0;
	char control;


	// Seed the random number generator so it's not always
	// the same numbers. "True" random numbers are hard to generate.
	srand((unsigned) time(NULL));

	while(wantsToPlay) {
		num = rand() % 100 +1;

		// statistics
		gamesPlayed++;
		totalGuesses+=attempts;

		attempts = 0; // reset for this game
		guessing = 1;

		printf("\nYou are guessing a number between 1 and 100\n");

		while(guessing) {
			printf("Please enter your guess now -- ");
			scanf("%d", &guess);
			clearRestOfBuffer();

			if(guess < num) {
				printf("Too low, please guess higher.\n");
			} else if(guess > num) {
				printf("Too high, please guess lower.\n");
			} else if(guess == num) {
				printf("Wow, that's it!\n");
				guessing=0; // we're done
			} else {
				printf("Something went terribly wrong. Try again.");
			}

			attempts++;
		}

		printf("\nYou needed %d guesses to get the correct answer, ", attempts);

		if(attempts <= 3)
			printf("very good! Are you sure you're not a pseudo-random number generator?\n");
		else if(attempts <= 6)
			printf("you're pretty good.\nYou could be better though, just saying.\n");
		else
			printf("that's plain awful.\nMaybe you should rethink your life. Or just your algorithm.\n");

		// I know I should encapsulate this in a loop so that it can validate
		// user input to make sure they enter a valid response. But that is
		// beyond the scope of the class currently -- I'm not supposed to know that.

		printf("Do you want to play again? y/n -- ");
		scanf("%c", &control);
		clearRestOfBuffer();

		if( ( (int) control == 110) || ((int) control == 78) )
			wantsToPlay = 0;

	}

	printf("\nYou played %d times with an average guess-count of %.2f\n", gamesPlayed, (float) totalGuesses/gamesPlayed);

	return 1;
}
