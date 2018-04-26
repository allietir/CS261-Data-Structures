/* CS261- Assignment 1 - Q.3*/
/* Name: Alexander Tir
 * Date: 1/16/2018
 * Solution description: This program contains a function that sorts a given array in ascending order using a bubble
 * sort algorithm. The array will be printed before and after the call to sort function.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

/*********************************************************************
** Function:		void sort(int* number, int n)
** Description:		This function sorts the array passed to it using a bubble sort algorithm
** Parameters:		int* number, int n
** Pre-Conditions:	The array must be initialized and filled with n numbers
** Post-Conditions:	array will be sorted in ascending order
*********************************************************************/
void sort(int* number, int n){
     /*Sort the given array number , of length n*/     
	int i, j, temp;
	int flag = 1;

	//A simple bubble sort algorithm
	for (i = 0; i < n && flag != 0; i++)
	{
		flag = 0;
		for (j = 0; j < n; j++)
		{
			if (number[j] > number[j + 1])
			{
				temp = number[j];
				number[j] = number[j + 1];
				number[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

/*********************************************************************
** Function:		int main()
** Description:		Main function. we allocate an array, fill it with random numbers, print the array, call sort, then print it again.
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	the array will be printed in ascending order
*********************************************************************/
int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;

	int i;  //loop index variable
    
    /*Allocate memory for an array of n integers using malloc.*/
	int *array = malloc(n * sizeof(int));

    /*Fill this array with random numbers, using rand().*/
	
	//seed rand using time
	srand(time(NULL));

	for (i = 0; i < n; i++)
	{
		array[i] = (rand() % 100) + 1;
	}

    /*Print the contents of the array.*/
	printf("Unsorted Array: \n");
	for (i = 0; i < n; i++)
	{
		printf("%d\n", array[i]);
	}

    /*Pass this array along with n to the sort() function of part a.*/
	sort(array, n);

    /*Print the contents of the array.*/
	printf("Sorted Array: \n");
	for (i = 0; i < n; i++)
	{
		printf("%d\n", array[i]);
	}

    return 0;
}
