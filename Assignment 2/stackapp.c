/*	stack.c: Stack application. */
/* CS261- Assignment 2*/
/* Name: Alexander Tir
* Date: 1/24/2018
* Solution description: This file contains a function isBalanced that checks whether or not a
* string of parenthesis/brackets/braces is balanced.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	assert(s != NULL);
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	
	/* FIXME: You will write this function */		
	
	/*The solution idea is that the string will be processed from left to right.
	 *If an opening parenthesis is encountered then it is pushed onto the stack.
	 *If a closing parenthesis is encountered, then we pop the stack. As long as
	 *there is ia matching symbol when the stack is popped, then the parenthesis
	 *will be balanced.*/

	printf("Testing string if balanced: %s\n", s);

	if (s == NULL)		//An empty string is technically balanced because an empty string is a string of balanced parentheses
	{
		return 0;
	}

	//Define the first character
	char ch = nextChar(s);

	//First we must define a stack to use
	DynArr *stack = newDynArr(4);

	//Execute the loop until we reach the end of the string '\0'
	while (ch != '\0')
	{
		if (ch == '(' || ch == '[' || ch == '{')
		{
			pushDynArr(stack, ch);
			//Leaving this commented out here to show my testing procedure
			//printf("push\n");
		}


		if (ch == ')' && topDynArr(stack) == '(')
		{
			popDynArr(stack);
			//Leaving this commented out here to show my testing procedure
			//printf("pop\n");
		}
		if (ch == ']' && topDynArr(stack) == '[')
		{
			popDynArr(stack);
			//Leaving this commented out here to show my testing procedure
			//printf("pop\n");
		}
		if (ch == '}' && topDynArr(stack) == '{')
		{
			popDynArr(stack);
			//Leaving this commented out here to show my testing procedure
			//printf("pop\n");
		}

		ch = nextChar(s);

	}

	//If the stack is empty after the end of the string has been reached, then it must be balanced
	if (isEmptyDynArr(stack))
	{
		deleteDynArr(stack);
		stack = NULL;
		return 1;
	}
	//If the stack is not empty, the string is not balanced because not every char was popped
	//Char are popped only when there is a corresponding parenthesis/bracket.
	else
	{
		deleteDynArr(stack);
		stack = NULL;
		return 0;
	}
		
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

