/* CS261- Assignment 1 - Q.2*/
/* Name: Alexander Tir
 * Date: 1/16/2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
** Function:		int foo(int* a, int* b, int c)
** Description:		foo doubles the value of a and halves the value of b. These two parameters
					are passed by reference. c is passed by value so the original parameter
					will not be changed.
** Parameters:		int* a, int* b, int c
** Pre-Conditions:	The three parameters must be initialized
** Post-Conditions:	Returns c
*********************************************************************/
int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = 2 * (*a);
    /*Set b to half its original value*/
	*b = (*b) / 2;
    /*Assign a+b to c*/
	c = (*a) + (*b);
    /*Return c*/
	return c;
}

/*********************************************************************
** Function:		int main()
** Description:		main function that calls the other functions. It prints the values of x, y, and z.
					It then calls foo and passes x, y, and z as parameters and prints the output of foo()
					as well as the values of x, y, and z.
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	none
*********************************************************************/
int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;
    
    /*Print the values of x, y and z*/
	printf("x: %d, y: %d, z: %d\n", x, y, z);
	    
    /*Call foo() appropriately, passing x,y,z as parameters*/
	int w;
	w = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
	printf("foo() returns the value: %d\n", w);

    /*Print the values of x, y and z again*/
	printf("x: %d, y: %d, z: %d\n", x, y, z);

    /*Is the return value different than the value of z?  Why?*/
	/*Yes, the return value is different than the value of z. The return value is the sum of twice the original value of x and half the original value of y.
	x and y have different values after foo() was called because they were passed by reference; however, z was passed by value, so the original value of z remains,
	while the return value from foo() is different.
	*/

    return 0;
}
    
    
