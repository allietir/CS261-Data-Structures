#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list){
	// FIXME: you must write this
	list->frontSentinel = malloc(sizeof(struct Link));
	list->backSentinel = malloc(sizeof(struct Link));
	
	assert(list->frontSentinel != 0);
	assert(list->backSentinel != 0);

	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = 0;

	list->backSentinel->prev = list->frontSentinel;
	list->backSentinel->next = 0;

	list->size = 0;
	
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	struct Link *addMe = malloc(sizeof(struct Link));
	assert(addMe != 0);

	//set new link's next to the given link, and prev to the given link's previous, and set value
	addMe->next = link;
	addMe->prev = link->prev;
	addMe->value = value;

	//First the link originally before the given link's next is set to the new link
	link->prev->next = addMe;
	//Then the link's prev is set to the new link (otherwise we will lose the pointer to link->prev->next)
	link->prev = addMe;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this

	//To remove the link, the link's next and prev will point to each other
	link->next->prev = link->prev;
	link->prev->next = link->next;

	//The link is then free'd and the size decremented
	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//There is no need to check that frontSentinel->next != 0 because if the list is empty, then it should be pointing
	//to the back sentinel
	addLinkBefore(list, list->frontSentinel->next, value);

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	//Simply call addLinkBefore and add the link before the back sentinel
	addLinkBefore(list, list->backSentinel, value);

}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	return list->frontSentinel->next->value;

}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->frontSentinel->next);
	
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	if (list->frontSentinel->next == list->backSentinel)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	struct Link *print = list->frontSentinel->next;

	printf("Front to back: ");

	while (print != list->backSentinel)
	{
		printf("%d -> ", print->value);
		print = print->next;
	}
	
	printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	linkedListAddBack(list, value);

}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));

	//create a Link to be the index for the loop
	struct Link *current;
	current = list->frontSentinel->next;

	//Loop until current reaches the backSentinel
	while (current != list->backSentinel)
	{
		//If the value is found, return 1
		if (EQ(current->value, value))
		{
			return 1;
		}
		//traverse to next in the linked list
		current = current->next;
	}

	//else return 0 if value is not found
	return 0;

}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));

	//create a link to be the index for loop
	struct Link *current;
	current = list->frontSentinel->next;

	//Loop until it reaches the end of the list
	while (current != list->backSentinel)
	{
		//When the first occurrence is found
		if (EQ(current->value, value))
		{
			removeLink(list, current);
			break;	//break here so that only the first value is removed
		}
		//traverse to next link
		current = current->next;
	}
}
