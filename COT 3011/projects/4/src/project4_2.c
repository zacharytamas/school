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
#include <math.h>

#define NUM_STUDENTS	10
#define NUM_TESTS		3

int main(void) {

	int _student = 0;
	int _id, _test=0;
	int i, j; // iterators
	double _score;
	char letter;

	typedef struct {
		int id;
		double scores[NUM_TESTS];
		double average;
	} student;

	student students[NUM_STUDENTS];
	student current_student;

	float testAvgs[NUM_TESTS];
	float overallAvg = 0;
	memset(testAvgs, 0, sizeof(testAvgs));

	// Phase 1: Data Collection
	while(_student < NUM_STUDENTS) {
		printf("\n");
		printf("Enter the student ID - (negative to stop) -- ");
		scanf("%d", &_id);

		if(_id < 0)
			break;

		students[_student].id = _id; // store the student ID
		students[_student].average = 0; // clear what might already be there

		for(_test = 0; _test < NUM_TESTS; _test++) {
			while(1) {
				printf("Enter the score for student %d for exam %d  -- ", _id, (_test + 1) );
				scanf("%lf", &_score);

				if(_score >= 0.0 && _score <= 100.00) {
					//  store the test score and also increment the average, which is just
					//  used as an accumulator right now
					students[_student].average += _score;
					students[_student].scores[_test] = _score;
					testAvgs[_test] += _score;
					break;
				}

				printf("  Score entered was invalid. Please enter a score between 0 and 100.\n");
			}
		}

		// divide the accumulated scores by the number of tests to get the average
		students[_student].average = students[_student].average / NUM_TESTS;


		_student++;
	}

	for(i=0; i < NUM_TESTS; i++)
	{ testAvgs[i] = testAvgs[i] / NUM_TESTS; overallAvg += testAvgs[i]; }
	overallAvg = overallAvg / NUM_TESTS;

	// Phase 2: The Big Fat Sort... bom bom bommmm

	// Opting for an insertion sort, would do mergesort but not allowed to have functions in this
	// which are necessary for recursion and gotos are evil. Had to be modified to sort
	// my struct based on properties inside them.
	for(i=1; i < _student ; i++) {
		j = i;
		while(j > 0 && students[j-1].average < students[j].average) {
			current_student = students[j];
			students[j] = students[j-1];
			students[j-1] = current_student;
			j--;
		}
	}


	// Phase 3: Display
	printf("\n%4s   ", "ID");
	for(i=0; i<NUM_TESTS; i++) printf("Exam %d   ", i+1);
	printf("Average   Grade\n");
	for(i=0; i < (4 + 10*NUM_TESTS + 17); i++) printf("-");
	printf("\n");

	for(i=0; i < _student; i++) {
		printf("%4d", students[i].id);
		for(j=0; j < NUM_TESTS; j++) printf("%9.2lf", students[i].scores[j]);
		printf("   %7.2lf", students[i].average);

		_score = rintf(students[i].average);

		if(_score >= 90) {
			letter = 'A';
		} else if(_score >= 80) {
			letter = 'B';
		} else if(_score >= 70) {
			letter = 'C';
		} else if(_score >= 60) {
			letter = 'D';
		} else {
			letter = 'F';
		}

		printf("     %c", letter);

		printf("\n");
	}

	printf("\n\n");
	printf("S U M M A R Y  R E P O R T\n");
	printf("---------------------------\n");
	for(i=0; i < NUM_TESTS; i++) printf("Exam %2d average  %6.2lf\n", i+1, testAvgs[i]);
	printf("Overall Average  %6.2f\n", overallAvg);

	float classGPA = 0;
	if(overallAvg >= 90) {
		classGPA = 4;
	} else if(overallAvg >= 80) {
		classGPA = 3;
	} else if(overallAvg >= 70) {
		classGPA = 2;
	} else if(overallAvg >= 60) {
		classGPA = 1;
	} else {
		classGPA = 0;
	}

	printf("Class GPA        %6.2f\n", classGPA);


	return 1;

}
