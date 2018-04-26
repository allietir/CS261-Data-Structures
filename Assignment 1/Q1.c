/* CS261- Assignment 1 - Q.1*/
/* Name: Alexander Tir
 * Date: 1/16/2018
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <assert.h>

struct student{
	int id;
	int score;
};

/******************************************************************************
** Function:         struct student* allocate()
** Description:      allocates memory for an array of struct student
** Parameters:       none
** Pre-Conditions:   none
** Post-Conditions:  returns pointer to array after allocating memory for 10 students
*****************************************************************************/
struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student *s = malloc(10 * sizeof(struct student));
     /*return the pointer*/
	return s;
}

/*********************************************************************
** Function:		void generate(struct student* students)
** Description:		Generates random and unique IDs and scores for ten students.
** Parameters:		Pointer to struct student
** Pre-Conditions:	10 students are allocated and initialized
** Post-Conditions:	array of students will have unique IDs and scores
*********************************************************************/
void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	
	int i, j;		//index variables for loops
	int unique = 0; //unique is a flag variable used for determining unique IDs

	//seed rand using time
	srand(time(NULL));

	//generate first student's id and score
	students[0].id = (rand() % 10) + 1;
	students[0].score = (rand() % 100) + 1;

	for (i = 1; i < 10; i++)
	{
		while (unique == 0)
		{
			//generate id for students
			students[i].id = (rand() % 10) + 1;
			
			//algorithm to check for unique ID
			for (j = 0; j < i; j++)
			{
				if (students[i].id == students[j].id)
				{
					//if a duplicate is found, then the loop exits and continues at the while loop, generating a new ID
					unique = 0;
					break;
				}
				else
				{
					//if no duplicate is found, then the flag is set to 1 and exits the while loop
					unique = 1;
				}
			}
		
		}
		//reset flag variable to 0
		unique = 0;
		//generate score for student (DOES NOT HAVE TO BE UNIQUE)
		students[i].score = (rand() % 100) + 1;

	}
}

/*********************************************************************
** Function:		void output(struct student* students)
** Description:		Outputs the ID and scores for ten students
** Parameters:		Pointer to struct student
** Pre-Conditions:	students must have IDs and scores
** Post-Conditions:	List of student IDs and scores will be printed
*********************************************************************/
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	int i;	//index variable for loop
	
	for (i = 0; i < 10; i++)
	{
		printf("ID: %d Score: %d\n", students[i].id, students[i].score);
	}
}

/*********************************************************************
** Function:		void summary(struct student* students)
** Description:		Computes and prints the mininum, maximum, and average scores for 10 students
** Parameters:		Pointer to struct student
** Pre-Conditions:	students must have IDs and scores
** Post-Conditions:	Minimum, maximum, and average scores will be computed and printed
*********************************************************************/
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int min, max;	//min and max variables
	int sum = 0;	//sum variable to calculate average
	double average;	//average score variable

	int i;			//index variable for loops

	//set the first min and max scores to use for comparison in the loop
	min = students[0].score;
	max = students[0].score;

	
	for (i = 0; i < 10; i++)
	{
		//if a score is lower than the current min, then the min is set equal to the score
		if (students[i].score < min)
		{
			min = students[i].score;
		}
		
		//if a score is higher than the current max, then the max is set equal to the score
		if (students[i].score > max)
		{
			max = students[i].score;
		}

		//add to total sum
		sum = sum + students[i].score;
	}

	//calculate average for 10 students
	average = sum / 10.0;

	//print information
	printf("The minimum score is: %d\n", min);
	printf("The maximum score is: %d\n", max);
	printf("The average score is: %f\n", average);
}

/*********************************************************************
** Function:		void deallocate(struct student* stud)
** Description:		Deallocates memory from the pointer to students
** Parameters:		Pointer to struct student
** Pre-Conditions:	Students must be initialized
** Post-Conditions:	Memory is deallocated from students
*********************************************************************/
void deallocate(struct student* stud){
     /*Deallocate memory from stud*/

	//safety check to avoid segmentation fault before freeing memory
	assert(stud != NULL);
	//deallocate memory from stud
	free(stud);
}

/*********************************************************************
** Function:		int main()
** Description:		main function that calls the other functions
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int main(){
    //struct student* stud = NULL;
	//The Assignment 1 Instructions PDF gave this line:
	struct student *st = 0;

    /*call allocate*/
	st = allocate();
    /*call generate*/
	generate(st);
    /*call output*/
	output(st);
    /*call summary*/
	summary(st);
    /*call deallocate*/
	deallocate(st);

    return 0;
}
