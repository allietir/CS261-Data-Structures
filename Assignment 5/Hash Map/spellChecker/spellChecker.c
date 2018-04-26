/*
* CS 261 Data Structures
* Assignment 5
* Name: Alexander Tir
* Date: 3/8/2018
*/

#define _CRT_SECURE_NO_WARNINGS
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Suggest
{
	char *minWord;
	int dist;
};


/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement

    char *word = nextWord(file);

    while (word!= NULL)
    {
        //if the word is in the dictionary, do nothing
        if(hashMapContainsKey(map, word)){}

        else
        {
            //add the word
            hashMapPut(map, word, 0);
        }
    free(word);
    word = nextWord(file);
    }

}

/**
* Since this was not covered in lecture, this levenshetin distance algorithm was taken
* from wikibooks:  https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C 
* This was done to focus on the implementation of the assignment and less on the Levenshtein algorithm itself.
*/

int levenshtein(char *s1, char *s2) {
	unsigned int s1len, s2len, x, y, lastdiag, olddiag;
	s1len = strlen(s1);
	s2len = strlen(s2);
	unsigned int *column;
	column = malloc((s1len + 1) * sizeof(unsigned int));
	//unsigned int column[s1len + 1];
	for (y = 1; y <= s1len; y++)
		column[y] = y;
	for (x = 1; x <= s2len; x++) {
		column[0] = x;
		for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
			olddiag = column[y];
			column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y - 1] == s2[x - 1] ? 0 : 1));
			lastdiag = olddiag;
		}
	}
	int levendist = column[s1len];
	free(column);
	return levendist;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..

        //convert the letters to lowercase
        int i = 0;
        while(inputBuffer[i] != '\0')
        {
            inputBuffer[i] = tolower(inputBuffer[i]);
            i++;
        }


        if(hashMapContainsKey(map, inputBuffer)) 
        {
        printf("Word: %s is spelled correctly!\n", inputBuffer);
        }

        else 
        {
            printf("Word: %s is mispelled.\n", inputBuffer);

			//iterators
			int i;
			int k;

			//levenshtein distance
			int LD;

			struct Suggest suggest[5];
			for (i = 0; i < 5; i++)
			{
				suggest[i].dist = 256;
				suggest[i].minWord = 0;
			}

			for (int i = 0; i < map->capacity; i++)
			{
				//current is used to traverse the hash map
				HashLink *current = map->table[i];
				while (current != NULL)
				{
					LD = levenshtein(current->key, inputBuffer);
					if (LD > 0)
					{
						int swap = 0;
						int j = 0;
						//using a flag swap variable
						while (j < 5 && swap == 0)
						{
							if (LD < suggest[j].dist)
							{
								for (k = 4; k > j; k--)
								{
									suggest[k].dist = suggest[k - 1].dist;
									suggest[k].minWord = suggest[k - 1].minWord;
								}
								suggest[j].dist = LD;
								suggest[j].minWord = current->key;
								swap = 1;
							}
							j++;
						}
					}
					current = current->next;
				}
			}

			for (i = 0; i < 5; i++)
			{
				if (suggest[i].minWord != 0) 
				{
					printf("Did you mean %s?\n", suggest[i].minWord);
				}
			}

        }
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}

