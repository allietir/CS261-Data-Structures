/* CS261- Assignment 1 - Q.5*/
/* Name: Alexander Tir
 * Date: 1/17/2018
 * Solution description: This program asks a user to enter a word and stores the string as an array of characters.
 * It then converts the word into sticky caps and prints it back to the user. It uses helper functions provided to convert
 * letters to uppercase and lowercase.
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
	//check ASCII value of ch to be uppercase
	if (ch >= 'A' && ch <= 'Z')
	{
		//return ch if already uppercase 
		return ch;
	}
	//if not upper case then convert to uppercase
	else
	{
		return ch - 'a' + 'A';
	}
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
	//check ASCII value of ch to be lowercase
	if (ch >= 'a' && ch <= 'z')
	{
		//return ch if already lowercase
		return ch;
	}
	//if not lowercase then convert to uppercase
	else
	{
		return ch - 'A' + 'a';
	}
}

/*********************************************************************
** Function:		void sticky(char* word)
** Description:		This function converts an array of characters into sticky caps
** Parameters:		char* word
** Pre-Conditions:	The word must be initialized by the user
** Post-Conditions:	String will be converted to sticky caps
*********************************************************************/
void sticky(char* word){
     /*Convert to sticky caps*/
	int i;		//index variable for loop

	for (i = 0; i < 51; i++)
	{
		//stop at the end of the string by checking for the null-terminator
		if (word[i] == '\0')
		{
			//exit loop at end of string
			return;
		}
		//Beginning with the first letter and every odd letter is uppercase
		//Remember that index starts from 0, so even indexes are odd letters!
		if (i % 2 == 0)
		{
			word[i] = toUpperCase(word[i]);
		}
		else if (i % 2 == 1)
		{
			word[i] = toLowerCase(word[i]);
		}
	}

}

/*********************************************************************
** Function:		int main()
** Description:		main function reads in word from user using scanf then converts it to sticky caps and prints it
** Parameters:		none
** Pre-Conditions:	none
** Post-Conditions:	prints word in sticky caps
*********************************************************************/
int main(){
    /*Read word from the keyboard using scanf*/

	//51 is chosen because it is disputed what is actually the longest possible word in English.
	//Some words are technical or merely coined but not in the English dictionary.
	char word[51];

	printf("Please enter a word (limit 50 letters): ");
	scanf("%s", word);
	
	/*Call sticky*/
	sticky(word);

    /*Print the new word*/
	printf("Your sticky word is: %s\n", word);
    
    return 0;
}
