#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

struct hashLink {
   void* key; /*the key is what you use to look up a hashLink*/
   void* value; /*the value stored with the hashLink, a pointer to int in the case of concordance*/
   struct hashLink * next; /*notice how these are like linked list nodes*/
};
typedef struct hashLink hashLink;

struct hashMap {
    hashLink ** table; /*array of pointers to hashLinks*/
    int tableSize; /*number of buckets in the table*/
    int count; /*number of hashLinks in the table*/
};
typedef struct hashMap hashMap;



/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);  /* malloc_1 */
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap)); /* malloc_2 */
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
  Frees up all hashLinks.  Assumes user has already freed up the keys, values if necessary
 */
void _freeLinks (struct hashLink  **table, int tableSize ) /*  (struct hashMap * ht) */
{  /*write this*/
	int i;
	struct hashLink *temp;
	struct hashLink *temp2;
	for(i=0; i< tableSize; i++){
		temp=table[i];
		while(temp!=0){
			temp2=temp->next;
			free(temp); /* malloc_3, malloc_4*/
			temp=temp2;
		}
	}
 }


/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeLinks(ht->table, ht->tableSize);
        free(ht->table);  /* malloc _ 1 */
	/* free the hashMap struct */
	free(ht); /* malloc_2 */
}

/*
Resizes the hash table to be the size newTableSize
*/
void _setTableSize(struct hashMap * ht, int newTableSize, comparator keyCompare, hashFuncPtr hashFunc)
{
	/*write this?*/
	int i;
	struct hashLink *temp;
	hashLink ** oldTable;
	int oldTableSize;

	printf("========Resizing========\n");
	oldTable = ht->table;
	oldTableSize = ht->tableSize;

	/* reinitialize the hash map */
	_initMap(ht, newTableSize);

	for(i = 0; i < oldTableSize; i++){
		temp = oldTable[i];
		while(temp != 0){
			/* insert the link temp to the new table */
		  insertMap (ht, temp->key, temp->value, keyCompare, hashFunc);
			temp = temp->next;
		}
	}
	/* free up the memory occupied by the old table  - ie. all the links and the table itself...because above creates a new table AND all new links with insertMap*/
        /* Note:  In this case, user DOES NOT and SHOULD NOT even know about this, so they will not free up the keys, values, which is perfect since they are reused here in the new table! */
	_freeLinks(oldTable, oldTableSize);	/* malloc_2 */
        free(oldTable);  /* malloc_1 */
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace the value for that key.  As the developer, you DO NOT FREE UP THE MEMORY FOR THE VALUE.
 We have to leave that up to the user of the hashMap to take care of since they may or may not
 have allocated the space with malloc.


 Also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, void* k, void* v, comparator keyCompare, hashFuncPtr hashFunc)
{
	/*write this?*/
	int bucket;
	struct hashLink * newLink;
	struct hashLink *temp;

	/* Check to see if a resize is necessary */
	if(tableLoad(ht) >= LOAD_FACTOR_THRESHOLD) {
	  _setTableSize(ht, 2 * capacity(ht), keyCompare, hashFunc);
	}

	//	#if (HASHING_FUNCTION==1)
	//bucket = stringHash1(k)%ht->tableSize;
	//#else
	//bucket = stringHash2(k)%ht->tableSize;
	//#endif
	bucket = (*hashFunc)(k) % ht->tableSize;

	if(ht->table[bucket] == 0){
                newLink = (struct hashLink *) malloc(sizeof(struct hashLink)); /* malloc_3 */
                ht->table[bucket]=newLink;
                ht->table[bucket]->key=k;
                ht->table[bucket]->value=v;
		ht->table[bucket]->next=0;
		ht->count++;
	}else{
		temp=ht->table[bucket];
		while(temp!=0){
		  if((*keyCompare)(temp->key,k)==0){
  /* Note that we do not actually free up their value for this key.  User must do that.  We can't even just deref the value and put a copy of new value in it because we can't deref a void * */
                                temp->value = v;
				return;
			} else {
				temp=temp->next;
			}
                }
                /* if it wasn't already in there! */
		newLink = (struct hashLink *) malloc(sizeof(struct hashLink)); /* malloc_4 */

		newLink->key=k;
		newLink->value=v;
		/* add newLink to the front of the list */
		newLink->next=ht->table[bucket];
		ht->table[bucket]=newLink;
		ht->count++;
           }
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */

void* atMap (struct hashMap * ht, void* k, comparator keyCompare, hashFuncPtr hashFunc)
{ /*write this?*/
	int bucket;
	struct hashLink *cur;
	struct hashLink *prev;

	//	#if (HASHING_FUNCTION==1)
	//	bucket = stringHash1(k)%ht->tableSize;
	//#else
	//bucket = stringHash2(k)%ht->tableSize;
	//#endif

	bucket = (*hashFunc)(k) % ht->tableSize;

	if(ht->table[bucket] == 0){
		return 0;
	}else{
		cur=ht->table[bucket];
		prev=ht->table[bucket];
		while(cur!=0){
		  if((*keyCompare)(cur->key,k)==0){
				return cur->value;
			}else{
				prev=cur;
				cur=cur->next;
			}
		}
		return 0;
	}
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, void* k, comparator keyCompare, hashFuncPtr hashFunc)
{  /*write this*/
  if (atMap(ht,k, keyCompare, hashFunc) ==0){
		return 0;
	}else{
		return 1;
	}
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, void* k, comparator keyCompare, hashFuncPtr hashFunc)
{  /*write this?*/
	int bucket;
	struct hashLink *cur;
	struct hashLink *prev;

	//#if (HASHING_FUNCTION==1)
	//bucket = stringHash1(k)%ht->tableSize;
	//#else
	//bucket = stringHash2(k)%ht->tableSize;
	//#endif

	bucket = (*hashFunc)(k) % ht->tableSize;
	
	if(ht->table[bucket] == 0){
             return;
}else{
  cur = ht->table[bucket];
		prev = ht->table[bucket];
		while(cur != 0){
                    if((*keyCompare)(cur->key, k)==0){
				if(cur == ht->table[bucket]){
					ht->table[bucket]=cur->next;
				} else {
					prev->next=cur->next;
				}
				/* DO NOT FREE UP USER'S STUFF:  key, value, ONLY FREE THE hashLink */
				free(cur);
				ht->count--;
				return;
			} else {
				prev = cur;
				cur = cur->next;
			}
		}
	}
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  /*write this*/
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  /*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int runner = 0;
	int i;
	for(i=0; i < ht->tableSize; i++){
		if(ht->table[i]==0){
			runner++;
		}
	}
	return runner;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
	/*write this*/
	return (float)size(ht)/(float)capacity(ht);
}



/*void printValue(ValueType v) {
	printf("%d", *(int *)v);
}
*/

/* print the hashMap */
 void printMap (struct hashMap * ht, keyPrinter kp, valPrinter vp)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
                        printf("Key:");
                        (*kp)(temp->key);
                        printf("| Value: ");
                        (*vp)(temp->value);
			printf(" -> ");
			temp=temp->next;
		}
	}
}

/* print the keys/values ..in linear form, no buckets */
 void printKeyValues (struct hashMap * ht, keyPrinter kp, valPrinter vp)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		while(temp != 0){
                        (*kp)(temp->key);
			printf(":");
                        (*vp)(temp->value);
			printf("\n");
			temp=temp->next;
		}
	}
}


/* Iterator Interface */

struct mapItr {
  int count;
  struct hashLink *current;
  struct hashMap *map;
};


struct mapItr *createMapIterator(struct hashMap *ht)
{
  struct mapItr *myItr = malloc(sizeof(struct mapItr)); /* malloc_5 */
  initMapIterator(ht, myItr);
  return myItr;
}

void initMapIterator(struct hashMap *ht, struct mapItr *itr)
{
  itr->count = 0;
  itr->current = ht->table[itr->count];
  itr->map = ht;
}

int  hasNextMap(struct mapItr *itr)
{

  /* skip all the empty buckets */

  while(itr->map->table[itr->count] == 0)
    {
       itr->count++;
       itr->current = itr->map->table[itr->count];
    }

  if (itr->count >= itr->map->tableSize)
    return 0;


  return 1;

}

void*  nextMap(struct mapItr *itr)
{
  void* key;
  key = itr->current->key;

  /* set up for subsequent call to has Next */
  itr->current = itr->current->next;
  if(itr->current == 0) /* at end of the list*/
    {
   itr->count++; /*move on to the next bucket */
   itr->current = itr->map->table[itr->count];
}
  return(key);
}

void removeMap(struct mapItr *itr)
{
  printf("Not yet implemented \n");
  /* Actually only a convenience since I can iterate through, get keys, and then call removeKey */
  /* This is, in fact, how I wouldimplement it here...I would simply get the last returned key and call remove Key */
  /* A slighlty more efficient solution would include double links and allow a remove iwthout calling removeKey...but it's not worth the effort here! */

}
