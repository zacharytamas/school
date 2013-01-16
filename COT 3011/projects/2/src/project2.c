/*
 ============================================================================
 Name        : Project2.c
 Author      : Zachary Jones
 Version     : 1.0
 Copyright   : 2010
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/**
 * Clears whatever is left in the input buffer.
 */
void clearRestOfBuffer(void) {
	char ch = getchar();

	while( ch != '\n' )
		ch = getchar();
}


char determineLetterGrade(float grade) {
	grade = rintf(grade);

	if(grade >= 90) {
		return 'A';
	} else if(grade >= 80) {
		return 'B';
	} else if(grade >= 70) {
		return 'C';
	} else if(grade >= 60) {
		return 'D';
	} else {
		return 'F';
	}

}


int roundFloat(float num) {
	return (int) (num+0.5);
}


float GPA(int totals[5]) {
	int i, grades = 0;
	float gpa = 0.0;
	for(i=0; i<5; i++) {
		gpa += (4-i) * totals[i];
		grades+=totals[i];
	}
	return (float) gpa / grades;
}


int main(void) {

	int moreNumbers = 1;
	float considering;
	float total = 0.0;
	int grades = 0, maxGrade = 0, minGrade=100;
	int totals[5];
	char letter;

	printf("\n"); // just to make it clean
	while(moreNumbers) {
		printf("Enter next score (negative to stop) -- ");
		scanf("%f", &considering);
		clearRestOfBuffer();

		if(considering < 0) { // spec only requires that -1 work but why not all negative
			moreNumbers = 0; break;
		} else if (considering > 100) {
			printf("Invalid score, please try again.\n");
		} else {

			total = total + considering;
			grades++;
			letter = determineLetterGrade(round(considering));
			totals[(letter - 65 == 5) ? (letter - 66) : (letter - 65)]++;

			if(considering > maxGrade)
				maxGrade = considering;

			if(considering < minGrade)
				minGrade = considering;

			printf("Score = %6.2f  Grade = %c\n", considering, letter);
		}

	}

	// Reports section

	printf("\n--------------------------\n");
	printf("  Number of scores %5d\n", grades);

	int i, offset;
	for(i=0; i < 5; i++) {
		offset = (i==4) ? 1:0;
		printf("  Number of %c's    %5d\n", (char) (i + 65 + offset), totals[i] );
	}

	printf("  High score      %6.2f\n", (float) maxGrade);
	printf("  Low score       %6.2f\n", (float) minGrade);
	printf("  Average score   %6.2f\n", total/grades);
	printf("  Exam GPA        %6.2f\n", GPA(totals));

	printf("--------------------------\n\n");

	return 0;
}
