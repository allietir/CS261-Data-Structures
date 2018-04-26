/* CS261- Assignment 1 - Q.4*/
/* Name: Alexander Tir
 * Date: 1/16/2018
 * Solution description: This program will randomly generate unique IDs and scores for an array of students
 * and sort them in ascending order based on their scores.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

/*********************************************************************
** Function:		void sort(struct student* students, int n)
** Description:		This function sorts the array of students passed to it using a bubble sort algorithm
** Parameters:		struct student* students, int n
** Pre-Conditions:	The array must be initialized and each student initialized with a unique ID and score
** Post-Conditions:	array will be sorted in ascending order by student score
*********************************************************************/
void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
	int i, j;				//index variables
	struct student temp;	//temporary variable to swap student
	int swap = 1;			//swap flag variable

	//bubble sort algorithm
	for (i = 0; i < n && swap != 0; i++)
	{
		swap = 0;
		for (j = 0; j < n; j++)
		{
			if (students[j].score > students[j + 1].score)
			{
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
				swap = 1;
			}
		}
	}

}

/*********************************************************************
** Function:		int main()
** Description:		main function, allocates memory for n students, generates IDs and scores,
					prints them, sorts them by calling the sort() fucntion, then prints them again.
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	A list of students sorted by scores will be printed
*********************************************************************/
int main(){
	//seed rand using time
	srand(time(NULL));

    /*Declare an integer n and assign it a value.*/
	int n = 10;			
	int unique = 0;		//unique identifer flag
	int i, j;			//index variables for loops

    /*Allocate memory for n students using malloc.*/
	struct student *st = malloc(n * sizeof(struct student));

    /*Generate random and unique IDs and random scores for the n students, using rand().*/
	//Using same method I wrote for Q1.c
	
	//generate first student's id and score
	st[0].id = (rand() % 10) + 1;
	st[0].score = (rand() % 100) + 1;

	for (i = 1; i < 10; i++)
	{
		while (unique == 0)
		{
			//generate id for students
			st[i].id = (rand() % 10) + 1;

			//algorithm to check for unique ID
			for (j = 0; j < i; j++)
			{
				if (st[i].id == st[j].id)
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
		st[i].score = (rand() % 100) + 1;

	}

    /*Print the contents of the array of n students.*/
	//I will use the same method I wrote for Q1.c
	printf("Student IDs and scores:\n");
	for (i = 0; i < 10; i++)
	{
		printf("ID: %d Score: %d\n", st[i].id, st[i].score);
	}

    /*Pass this array along with n to the sort() function*/
	sort(st, n);

    /*Print the contents of the array of n students.*/
	printf("Sorted by score:\n");
	for (i = 0; i < 10; i++)
	{
		printf("ID: %d Score: %d\n", st[i].id, st[i].score);
	}

    return 0;
}
