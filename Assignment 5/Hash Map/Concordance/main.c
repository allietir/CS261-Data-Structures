/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Alexander Tir
 * Date: 3/8/2018
 */

#define _CRT_SECURE_NO_WARNINGS
#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

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
//Fix me: Do the necessary change to make the implementation //case-insensitive  
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
            // .............
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
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    // Be sure to free the word after you are done with it here.

    FILE *fileptr;

    //"r" opens a file for reading
    fileptr = fopen(fileName, "r");

    if(fileptr == NULL)
    {
        printf("File not found.\n");
    }

    char *word = nextWord(fileptr);
    int occurrence;

    while (word != NULL)
    {
        //if the hash map already contains the word at least once
        if(hashMapContainsKey(map, word))
        {
            //hashMapGet returns pointer to value of key, must be dereferenced *
            occurrence = *(hashMapGet(map, word));
            occurrence++;
            hashMapPut(map, word, occurrence);
        }
        //if the hash map does not contain the word yet
        else
        {
            hashMapPut(map, word, 1);
        }

        free(word);
        word = nextWord(fileptr);
    }

    fclose(fileptr);

    int i;

    for(i = 0; i < map->capacity; i++)
    {
        HashLink* printLink = map->table[i];
        if(printLink != NULL)
        {
            while(printLink != NULL)
            {
                printf(" %s:  %d\n", printLink->key, printLink->value);
                printLink = printLink->next;
            }
        }
    } 

    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}