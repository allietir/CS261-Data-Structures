/* CS261- Assignment 1 - Q. 0*/
/* Name: Alexander Tir
 * Date: 1/16/2018
 * Solution description: Q0.c prints the address of a variable x, passes the address of x to a function that 
 * takes a pointer as its argument. The function fooA prints the value pointed to by the pointer, prints the address pointed to,
 * and prints the address of the pointer. It then print the value of x in main.
 */
 
#include <stdio.h>
#include <stdlib.h>

 /******************************************************************************
 ** Function:         void fooA(int* iptr)
 ** Description:      prints the value pointed to by iptr, the address pointed to by iptr, and the address of iptr
 ** Parameters:       int* iptr
 ** Pre-Conditions:   the integer parameter is initialized
 ** Post-Conditions:  prints the information listed in the description
 *****************************************************************************/
void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("Value pointed to by iptr: %d\n", *iptr);
     /*Print the address pointed to by iptr*/
	printf("Address poitned to by iptr: %p\n", iptr);
     /*Print the address of iptr itself*/
	printf("Address of iptr: %p\n", &iptr);
}

/*********************************************************************
** Function:		int main()
** Description:		main function that calls foo, prints the address of x and the value
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int main(){
    
    /*declare an integer x*/

	//I will also initialize x in order to properly run and test the program
	int x = 504;
    
    /*print the address of x*/
	printf("Address of x: %p\n", &x);

    /*Call fooA() with the address of x*/
	fooA(&x);

    /*print the value of x*/
	printf("Value of x: %d\n", x);

    return 0;
}
