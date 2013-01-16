/*
 ============================================================================
 Name        : Project4.c
 Author      : Zachary Jones
 Version     :
 Copyright   : 2011
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STUDENTS	10
#define NUM_TESTS		3

int main(void) {

	// I want so badly to build a struct for this but I know I'm not
	// supposed to know that yet.....

	int ids[NUM_STUDENTS];
	double scores[NUM_STUDENTS][NUM_TESTS];
	double averages[NUM_STUDENTS];
	// kept getting distracting values that were previously in memory
	memset(scores, 0, sizeof(scores));
	memset(averages, 0, sizeof(averages)); // so I can plus-equal it later

	int _student = 0;
	int _id, _test, i=0, j=0;
	double _score;


	// Phase 1 - Data collection
	while(_student < NUM_STUDENTS) {
		printf("Enter the student ID - (negative to stop) -- ");
		scanf("%d", &_id);

		if(_id < 0) // we're done with data collection
			break;
		else
			ids[_student] = _id;

		for(_test = 0; _test < NUM_TESTS; _test++) {
			while(1) {
				printf("Enter the score for student %d for exam %d  -- ", _id, (_test + 1) );
				scanf("%lf", &_score);

				if(_score >= 0.0 && _score <= 100.00) {
					scores[_student][_test] = _score;
					averages[_student] += _score;
					break;
				}

				printf("  Score entered was invalid. Please enter a score between 0 and 100.\n");
			}
		}

		// While we were adding in tests I stored a running-total of points
		// in the averages array, even though it's not really the average yet.
		// This saves some memory by not having a separate disposable double
		// sitting around to act as a register.

		// Here I divide it by the number of tests to make it the actual average.
		averages[_student] = averages[_student] / (double) NUM_TESTS; // C needs =/

		_student++;
	}


	// Phase 2 - Calculations

	// Phase 3 - Sorting

	// Phase 4 - Display

	printf("\n%4s   ", "ID");
	for(i=0; i<NUM_TESTS; i++)
		printf("Exam %d   ", i+1);
	printf("Average   Grade\n");
	for(i=0; i < (4 + 10*NUM_TESTS + 17); i++)
		printf("-");
	printf("\n");

	for(i=0; i < _student; i++) {
		printf("%4d   ", ids[i]);
		for(j=0; j < NUM_TESTS; j++)
			printf("%7.2lf   ", scores[i][j]);
		printf("\n");
	}

	return 1;

}
