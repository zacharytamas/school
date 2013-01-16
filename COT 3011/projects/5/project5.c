/**
 * COT 3011, University of West Florida
 * Project 5
 *
 * @author Zachary Jones <zacharytamas@gmail.com>
 * @version 1.0
 * @releasedate March 10, 2011
 */

#include <stdio.h>
#include <string.h>
#define NUM_STUDENTS	10
#define	NUM_TESTS		3


/**
 * Struct describing a student.
 */
typedef struct {
	int id;
	double scores[NUM_TESTS];
	double average;
} Student;


/**
 * Prototypes
 */
void	collectData(Student [], double [], int *, double *);
int		getStudentID(void);
double	getScore(int);
void	sort(Student [], int);
void	printSummary(Student [], double [], int, double);
void	printStudentDetail(Student);
void	println(char *);
char	letterGradeOf(float);
double	classGPA(Student [], int);


int main (int argc, const char * argv[]) 
{	
	// setting up
	Student students[NUM_STUDENTS];
	double testAvgs[NUM_TESTS];
	double overallAvg = 0.0;
	memset(testAvgs, 0.0, sizeof(testAvgs));
	int num_of_students = 0;
	
	collectData(students, testAvgs, &num_of_students, &overallAvg);
	sort(students, num_of_students);
	printSummary(students, testAvgs, num_of_students, overallAvg);
	
	return 0;
}


/**
 * Handles the collection of data from the user by acting as
 * a controller and coordinating the input of students and 
 * their test scores.
 *
 * @param students. A reference to the array of Students defined in main()
 * @return void
 */
void collectData(Student students[], double testAvgs[NUM_TESTS], int *num_of_students, double *overallAvg)
{
	int _student = 0, _id = 0, _test;
	double _score;
	
	while (_student < NUM_STUDENTS) {
		
		_id = getStudentID();
		
		if (_id < 0)
			break;
		
		students[_student].id = _id;
		students[_student].average = 0;
		
		for (_test = 0; _test < NUM_TESTS; _test++) {
			_score = getScore(_test + 1);
			students[_student].scores[_test] = _score;
			students[_student].average += _score;
			testAvgs[_test] += _score;
		}
		
		students[_student].average = students[_student].average / NUM_TESTS;
		
		_student++;
	}
	
	// inform main how many students we ended up with
	*num_of_students = _student;
	
	// calculate the averages
	for (int i=0; i < NUM_TESTS; i++) {
		testAvgs[i] = testAvgs[i] / (_student + 1);
		*overallAvg += testAvgs[i];
	}
	*overallAvg = *overallAvg / NUM_TESTS;
	
}


/**
 * Asks the user for a Student ID number.
 *
 * @return int. Student ID.
 */
int getStudentID()
{
	int _id;
	printf("Enter the student ID - (negative to stop) -- ");
	scanf("%d", &_id);
	return _id;
}


/**
 * Asks the user for a score, validates it, and returns if valid.
 * If score not valid, it loops until the user inputs proper data.
 *
 * @param int. The test number.
 * @return double. The score.
 */
double getScore(int testNo)
{
	double _score;
	
	while (1) {
		printf("  Enter the score for exam %d -- ", testNo);
		scanf("%lf", &_score);
		
		if (_score >= 0.0 && _score <= 100.0) {
			break;
		}
		
		printf("  Invalid score, please enter a score between 0 and 100.\n");
		
	}
	
	return _score;
}


/**
 * Uses an insertion sort to sort the students descending by their test average.
 *
 * @param students[] Array of students
 * @param num_of_students Number of students, 0-indexed.
 */
void sort(Student students[], int num_of_students)
{
	Student current;
	int i, j;
	
	for (i=0; i < num_of_students; i++) {
		j = i;
		while (j > 0 && students[j-1].average < students[j].average) {
			current = students[j];
			students[j] = students[j-1];
			students[j-1] = current;
			j--;
		}
	}
}


/**
 * Prints summary information.
 *
 * @param students[] Array of students.
 * @param testAvgs[] Array of test averages.
 * @param num_of_students Integer representing total number of students, 0-indexed.
 * @param overallAvg Double of the overall class average.
 */
void printSummary(Student students[], double testAvgs[], int num_of_students, double overallAvg)
{
	int i;
	
	// this is all hideous, I guess I need to write a library for building these kinds
	// of tables since we seem to have to do it so often
	
	printf("\n%4s   ", "ID");
	for (i=0; i<NUM_TESTS; i++) printf("Exam %d   ", i+1);
	println("Average   Grade");
	for (i=0; i < (4 + 10*NUM_TESTS + 17); i++) printf("-");
	printf("\n");
	
	for (i=0; i < num_of_students; i++)
		printStudentDetail(students[i]);
	
	printf("\n\n");
	println("S U M M A R Y   R E P O R T");
	println("===========================");
	
	for (i=0; i< NUM_TESTS; i++) {
		printf("Exam %2d average  %6.2lf\n", i+1, testAvgs[i]);
	}
	printf("Overall Average  %6.2lf\n", overallAvg);
	printf("Class GPA        %6.2lf\n", classGPA(students, num_of_students));
	
}


/**
 * Accepts a string and prints it with a new-line automatically appended.
 *
 * @param *str Pointer to a char array (string)
 */
void println(char *str)
{
	while(*str) { // when str reaches the null-terminator this is false
		printf("%c", *str); str++;
	}
	printf("\n");
}


/**
 * Prints a single detail line about a student.
 *
 * @param student Student to be shown details of.
 */
void printStudentDetail(Student student)
{
	int i;
	
	printf("%4d", student.id);
	for (i=0; i<NUM_TESTS; i++) printf("%9.2lf", student.scores[i]);
	printf("   %7.2lf", student.average);
	printf("     %c", letterGradeOf(student.average));
	printf("\n");
}


/**
 * Returns the letter grade given a score.
 *
 * @param grade. Grade to find letter grade of.
 */
char letterGradeOf(float grade) {
	grade = (int) (grade + 0.5);
	
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


/**
 * Returns the class GPA as a double.
 *
 * @param students[] Array of Students.
 * @param num_of_students Number of students, 0-index.
 */
double classGPA(Student students[], int num_of_students)
{
	double gpa = 0.0;
	double grade;
	
	for (int i=0; i < num_of_students; i++) {
		grade = (int) (students[i].average + 0.5);
		if (grade >= 90) {
			gpa += 4.0;
		} else if (grade >= 80) {
			gpa += 3.0;
		} else if (grade >= 70) {
			gpa += 2.0;
		} else if (grade >= 60) {
			gpa += 1.0;	
		}
	}
	
	return gpa / (float) (num_of_students+1);
}