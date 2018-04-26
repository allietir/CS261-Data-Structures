/* CS261- Assignment 3*/
/* Name: Alexander Tir
* Date: 1/31/2018
* Solution description: This is the implementation file for the circular-doubly-linked list for Part 2 of Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);

	//allocate sentinel
	list->sentinel = (struct Link *)malloc(sizeof(struct Link));
	assert(list->sentinel != 0);

	//Sentinel's next and prev point to itself
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;

	//Size to 0
	list->size = 0;
	//Value to 0 since sentinel has no value
	list->sentinel->value = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
	struct Link *newLink = malloc(sizeof(struct Link));
	assert(newLink != 0);

	//next and prev pointers point to null
	newLink->next = 0;
	newLink->prev = 0;
	newLink->value = value;

	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	//Assert the preconditions!
	assert(list != 0);
	assert(link != 0);

	struct Link *addLink = createLink(value);

	//addLink is added after the given link, so addLink's next pointers to link's next and prev to the link
	addLink->next = link->next;
	addLink->prev = link;

	//update link's next to new addLink
	link->next = addLink;

	//the link after adddLink's prev should point to addLink
	addLink->next->prev = addLink;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	//To remove, the link's next and prev will point to each other
	link->prev->next = link->next;
	link->next->prev = link->prev;

	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
	//Sentinel's next will always point to a link until it points to itself
	//Each link is removed one by one
	while (!circularListIsEmpty(list))
	{
		removeLink(list, list->sentinel->next);
	}
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	//The front of the list is after the sentinel
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	//The back of the list is after the sentinel's prev
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);

	if (list->size == 0)
	{
		return 1;
	}
	return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	//Begin at the front of the list
	struct Link *printList = list->sentinel->next;

	//Traverse until the back of the list is reached
	printf("Printing circular list: sentinel-> ");
	while (printList != list->sentinel)
	{
		printf("%g->", printList->value);
		printList = printList->next;
	}

	printf(" sentinel\n");

}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	struct Link *current = list->sentinel;
	struct Link *next, *temp;

	do
	{
		next = current->next;
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = next;
	} while (current != list->sentinel);

}
