

/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name:	Alexander Tir	
 * Email:	tira@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* All by yourself */ 
#define TYPE int


struct link {
	TYPE value;
	struct link *next;
};


struct Stack {
	struct listQueue *q1;
	struct listQueue *q2;
	int size;
};

struct listQueue {
	struct link *firstLink;
	struct link *lastLink;
};

/*******FUNCTION PROTOTYPES*******/
struct Stack *createLinkedListStack();
void stackInit(struct Stack *list);
void stackFree(struct Stack *list);
void deleteStack(struct Stack *list);

int stackIsEmpty(struct Stack *list);
void stackPush(struct Stack *list, TYPE value);
TYPE stackTop(struct Stack *list);
void stackPop(struct Stack *list);

void listQueueInit(struct listQueue *q);
void listQueueAddBack(struct listQueue *q, TYPE value);
TYPE listQueueFront(struct listQueue *q);
void listQueueRemoveFront(struct listQueue *q);
int listQueueIsEmpty(struct listQueue *q);

void test(TYPE test, TYPE against);

/*******STACK FUNCTIONS*******/

/******************************************************************************
** Function:         struct Stack *createLinkedListStack()
** Description:      creates and initializes a Stack
** Parameters:       none
** Pre-Conditions:   none
** Post-Conditions:  returns pointer to newly created Stack
*****************************************************************************/
struct Stack *createLinkedListStack() {
	struct Stack *newList = malloc(sizeof(struct Stack));
	stackInit(newList);
	return newList;
}

/******************************************************************************
** Function:         void stackInit(struct Stack *list)
** Description:      initializes a Stack and and its listQueue members
** Parameters:       pointer to a Stack to be initialized
** Pre-Conditions:   Stack pointer is allocated
** Post-Conditions:  listQueue are initialized, and Stack's size is set to 0
*****************************************************************************/
void stackInit(struct Stack *list) {
	list->q1 = malloc(sizeof(struct listQueue));
	list->q2 = malloc(sizeof(struct listQueue));
	listQueueInit(list->q1);
	listQueueInit(list->q2);
	list->size = 0;
}

/******************************************************************************
** Function:         void stackFree(struct Stack *list)
** Description:      deletes all links but does not delete the stack
** Parameters:       the struct Stack
** Pre-Conditions:   the struct Stack is not null
** Post-Conditions:  deletes all links except the first so that the stack still exists and is initialized
*****************************************************************************/
void stackFree(struct Stack *list) {
	assert(list != 0);
	while (!stackIsEmpty(list))
	{
		stackPop(list);
	}
}

/******************************************************************************
** Function:         void deleteStack(struct Stack *list)
** Description:      entirely deletes the Stack
** Parameters:       the struct Stack
** Pre-Conditions:   the struct Stack is not null
** Post-Conditions:  memory allocated for Stack is freed and "Stack deleted" statement is printed
*****************************************************************************/
void deleteStack(struct Stack *list) {
	assert(list != 0);
	stackFree(list);
	free(list);
	printf("Stack deleted\n");
}

/******************************************************************************
** Function:         void stackPush(struct Stack *list, TYPE value)
** Description:      stackPush will add the value to q2, then everything from q1 is removed and added
					 to q2. The names of q1 and q2 are then swapped to avoid an additional movement of
					 all the elements. This ensures that the most newly entered element is always at
					 the front of q1. Essentially, q2 will always be empty at the end of every push
					 operation.
** Parameters:       struct Stack and value to be pushed on the stack
** Pre-Conditions:   struct stack is not null
** Post-Conditions:  listQueue q1's front element will be the element most recently pushed, and q2 will be empty
*****************************************************************************/
void stackPush(struct Stack *list, TYPE value)
{
	assert(list != 0);
	list->size++;
	listQueueAddBack(list->q2, value);
	while (!listQueueIsEmpty(list->q1))
	{
		listQueueAddBack(list->q2, listQueueFront(list->q1));
		listQueueRemoveFront(list->q1);
	}
	struct listQueue *swap = list->q1;
	list->q1 = list->q2;
	list->q2 = swap;
}

/******************************************************************************
** Function:         TYPE stackTop(struct Stack *list)
** Description:      returns the top value of the stack (front of the queue q1)
** Parameters:       the struct Stack
** Pre-Conditions:   the struct Stack's queue is not empty and is initialized
** Post-Conditions:  the top value of the stack is returned
*****************************************************************************/
TYPE stackTop(struct Stack *list) {
	assert(!listQueueIsEmpty(list->q1));
	
	return listQueueFront(list->q1);
}

/******************************************************************************
** Function:         void stackPop(struct Stack *list)
** Description:      remove the top value of the stack (front of the queue q1)
** Parameters:       the struct Stack
** Pre-Conditions:   the struct Stack's queue is not empty and is initialized
** Post-Conditions:  the top value of the stack is removed, size is decreased by 1
*****************************************************************************/
void stackPop(struct Stack *list) {
	assert(!listQueueIsEmpty(list->q1));

	listQueueRemoveFront(list->q1);
	list->size--;
}

/******************************************************************************
** Function:         int stackIsEmpty(struct Stack *list)
** Description:      checks if the Stack is empty (by checking the queue q1)
** Parameters:       the struct Stack
** Pre-Conditions:   the struct Stack is initialized
** Post-Conditions:  If the stack is empty, return 1. If not, return 0.
*****************************************************************************/
int stackIsEmpty(struct Stack *list) {
	if (listQueueIsEmpty(list->q1))
		return 1;
	else
		return 0;
}



/*******QUEUE FUNCTIONS*******/

/******************************************************************************
** Function:         void listQueueInit(struct listQueue *q)
** Description:      initializes listQueue by creating a sentinel
** Parameters:       struct listQueue
** Pre-Conditions:   struct listQueue is allocated and initialized
** Post-Conditions:  Sentinel is created and the listQueue's first and last link point to the sentinel
*****************************************************************************/
void listQueueInit(struct listQueue *q) {
	struct link *lnk = (struct link *)malloc(sizeof(struct link));
	assert(lnk != 0);
	lnk->next = 0;
	q->firstLink = lnk;
	q->lastLink = lnk;
}

/******************************************************************************
** Function:         void listQueueAddBack(struct listQueue *q, TYPE value)
** Description:      Adds a value to the back of the queue
** Parameters:       struct listQueue and a value to be added
** Pre-Conditions:   struct listQueue is initialized
** Post-Conditions:  A new link is allocated and initialized for the value. The lastLink is updated to
					 point to the new link and the previous last link's next points to the new link.
*****************************************************************************/
void listQueueAddBack(struct listQueue *q, TYPE value) {
	struct link *lnk = malloc(sizeof(struct link));
	assert(lnk != 0);
	lnk->value = value;
	lnk->next = 0;
	q->lastLink->next = lnk;
	q->lastLink = lnk;
}

/******************************************************************************
** Function:         TYPE listQueueFront(struct listQueue *q)
** Description:      returns the front value of the queue
** Parameters:       struct listQueue
** Pre-Conditions:   struct listQueue is initialized and not empty
** Post-Conditions:  The value in the front of the queue is returned
*****************************************************************************/
TYPE listQueueFront(struct listQueue *q) {
	assert(!listQueueIsEmpty(q));
	return q->firstLink->next->value;
}

/******************************************************************************
** Function:         void listQueueRemoveFront(struct listQueue *q)
** Description:      removes the front value of the queue
** Parameters:       struct listQueue
** Pre-Conditions:   struct listQueue is initialized and not empty
** Post-Conditions:  The link to be removed is disconnected by having the firstLink's next point to the link
					 after the link to be removed. The link to be removed is then free'd.
*****************************************************************************/
void listQueueRemoveFront(struct listQueue *q) {
	struct link *lnk = q->firstLink->next;
	assert(!listQueueIsEmpty(q));
	q->firstLink->next = lnk->next;
	if (q->firstLink->next == 0)
		q->lastLink = q->firstLink;
	free(lnk);
}

/******************************************************************************
** Function:         int listQueueIsEmpty(struct listQueue *q)
** Description:      checks if the queue is empty by checking if firstLink and lastLink point to the same link (the sentinel)
** Parameters:       struct listQueue
** Pre-Conditions:   struct listQueue is initialized
** Post-Conditions:  Returns 1 if empty, returns 0 if not empty
*****************************************************************************/
int listQueueIsEmpty(struct listQueue *q) {
	if (q->firstLink == q->lastLink)
		return 1;
	else
		return 0;
}

/******************************************************************************
** Function:         void test(TYPE test, TYPE against)
** Description:      simple test to check if two values are equal
** Parameters:       TYPE test and TYPE against
** Pre-Conditions:   parameters have a value
** Post-Conditions:  prints PASSED or FAILED depending on the result of the test
*****************************************************************************/
void test(TYPE test, TYPE against) {
	if (test == against)
	{
		printf("PASSED: %d == %d\n\n", test, against);
	}
	else
		printf("FAILED: %d != %d\n\n", test, against);
}

/******************************************************************************
** Function:         int main()
** Description:      main function, used for testing implementation of a stack using two queues
** Parameters:       none
** Pre-Conditions:   none
** Post-Conditions:  tests show that implementation is successful
*****************************************************************************/
int main() {
	struct Stack *queueStack = createLinkedListStack();
	
	if (stackIsEmpty(queueStack))
	{
		printf("Stack is empty.\n");
	}
	else
		printf("Stack is not empty.\n");

	printf("Pushing 2\n");
	stackPush(queueStack, 2);
	printf("Pushing 3\n");
	stackPush(queueStack, 3);
	printf("Pushing 4\n");
	stackPush(queueStack, 4);
	printf("Testing stackTop == 4\n");
	test(stackTop(queueStack), 4);

	printf("Testing stackTop == 3\n");
	test(stackTop(queueStack), 3);

	printf("Popping stack\n");
	stackPop(queueStack);

	printf("Testing stackTop == 3\n");
	test(stackTop(queueStack), 3);

	printf("Popping stack\n");
	stackPop(queueStack);

	printf("Testing stackTop == 2\n");
	test(stackTop(queueStack), 2);

	printf("Pushing 5\n");
	stackPush(queueStack, 5);
	printf("Pushing 6\n");
	stackPush(queueStack, 6);
	printf("Pushing 7\n");
	stackPush(queueStack, 7);
	
	printf("Testing stackTop == 7\n");
	test(stackTop(queueStack), 7);

	printf("Popping stack\n");
	stackPop(queueStack);
	printf("Popping stack\n");
	stackPop(queueStack);

	printf("Testing stackTop == 5\n");
	test(stackTop(queueStack), 5);

	if (stackIsEmpty(queueStack))
	{
		printf("Stack is empty.\n");
	}
	else
		printf("Stack is not empty.\n");

	printf("Now deleting stack...\n");
	deleteStack(queueStack);
	return 0;
}