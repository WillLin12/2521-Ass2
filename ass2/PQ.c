/*// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


//typedef struct ItemNode ItemNode;

typedef struct ItemNode {
	ItemPQ Item;
	struct ItemNode *next;
} ItemNode;


	
//struct ItemNode *ItemNodePointer;

//typedef struct ItemNode ItemNode;
//typedef struct ItemNode *ItemNodePointer;


typedef struct PQRep {
	int nItems;
	//ItemPQ *items;
	//int nslots;
	ItemNode *first;
	ItemNode *last; //smallest
} PQRep;

static ItemNode *makeItemNode (ItemPQ item);

PQ newPQ() {
	PQ myPQ = malloc(sizeof (PQRep));

	//ItemPQ **items;
	//items = malloc(sizeof (ItemPQ *));

	//myPQ->items = items;
	myPQ->nItems = 0;
	myPQ->first = NULL;
	myPQ->last = NULL;

	//myPQ->nslots = 0;
	

	return myPQ;
}

int PQEmpty(PQ p) {
	if (p->nItems == 0) {
		return 1;
	} else {
		return 0;
	}
}
void addPQ(PQ pq, ItemPQ element) {
	assert (pq != NULL);

	// if PQ is empty
	if (pq->nItems == 0) {
		ItemNode *newNode = makeItemNode(element);		
		pq->first = newNode;
		pq->last = newNode;
		pq->nItems++;

	
	} else if (pq->first->Item.value > element.value) {
		ItemNode *newNode = makeItemNode(element);
		newNode->next = pq->first;
		pq->first = newNode;
		pq->nItems++;
    } else if (pq->last->Item.value == element.value) {
		pq->last->Item.value = element.value;
	} else if (pq->last->Item.value < element.value) {
		ItemNode *newNode = makeItemNode(element);
		newNode->next = NULL;
		pq->last->next = newNode;
		pq->nItems++;
	} else {
		ItemNode *currP = pq->first;
		while (currP->next != NULL) {
			if (currP->Item.key == element.key) {
				currP->Item.value = element.value;
				break;
			} else if (currP->Item.value < element.value && currP->next->Item.value > element.value) {
				ItemNode *newNode = makeItemNode(element);
				newNode->next = currP->next;
				currP->next = newNode;
				pq->nItems++;
				break;
			}
			currP = currP->next;
		}
	}
}

void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	if (pq->nItems == 0) {
		ItemNode *newNode = makeItemNode(element);
		pq->first = newNode;
		pq->last = newNode;
		pq->nItems++;
	} else {
		ItemNode *currP = pq->first;
		if (element.key <= currP->Item.key) { //key is less than first item's key
			ItemNode *newNode = makeItemNode(element);
			newNode->next = currP;
			pq->first = newNode;
			pq->nItems++;		
		} else {
			ItemNode *prevP = pq->first;
			while (currP->next != NULL) {
				if (element.key == currP->Item.key) {
					currP->Item.value = element.value;
					break;
				} else if (element.key > currP->Item.key && element.key < currP->next->Item.key) {
					ItemNode *newNode = makeItemNode(element);
					newNode->next = currP->next;
					currP->next = newNode;
					pq->nItems++;
					break;
				}	
				prevP = currP;
				currP = currP->next;
			}
			if (element.key < currP->Item.key) {
				ItemNode *newNode = makeItemNode(element);
				newNode->next = currP;
				prevP->next = newNode;
				pq->nItems++;
			} else if (element.key == currP->Item.key) {
				currP->Item.value = element.value;
				break;
			} else {
				ItemNode *newNode = makeItemNode(element);
				newNode->next = NULL;
				currP->next = newNode;
				pq->nItems++;
				pq->last = newNode;
			}

		}
	}

}

ItemPQ dequeuePQ(PQ pq) {
	assert(PQEmpty(pq) != 1);

	ItemPQ myItem = pq->first->Item;
	ItemNode *currP = pq->first;
	pq->first = currP->next;
	currP->next = NULL;
	pq->nItems = pq->nItems - 1;
 	free(currP);
	return myItem;
}

void updatePQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	ItemNode *currP = pq->first;
	ItemNode *prevP = pq->first;
	while (currP != NULL) {
		if (currP->Item.key == element.key) {
			currP->Item.value = element.value;
			ItemNode *ItemP = currP;
			if (currP == prevP) {
				pq->first = currP->next;
				currP->next = NULL;
			} else if (currP->next != NULL) {
				prevP->next = currP->next;
				currP->next = NULL;
			} else {
				pq->last = prevP;
				prevP->next = NULL;
			}
			addPQ(pq, ItemP->Item);
			free(currP);
		}
		prevP = currP;
		currP = currP->next;
	}
	
}

static ItemNode *makeItemNode(ItemPQ item) { //problems with static
	ItemNode *myItem = malloc(sizeof (ItemNode));
	myItem->Item = item;
	myItem->next = NULL;
	return myItem;
}
void  showPQ(PQ pq) {

}

void  freePQ(PQ pq) {	

}
*/
#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include "PQ.h"

//binary heap has O(log n) time complexity.
//MIN BINARY HEAP PRIORITY QUEUE.

//typedef struct Node{
//      ItemPQ item;
//      Node *next;
//}Node;

typedef struct PQRep *PQ;

typedef struct PQRep{
        int size;
        ItemPQ *array;
}PQRep;

/*The key would be the number of the node you will be moving to in Dijkstra's
while the value would be the distance from the start to get there.
*/
static void fixUp(PQ head, int index) {
	int i = index;
	int j = (i-1)/2;
	while (i > 0 && head->array[j].value > head->array[i].value) {
		
		ItemPQ temp = head->array[j];
		head->array[j] = head->array[i];
		head->array[i] = temp;
		
		i = j;
		j = (i-1)/2;
	}
}

static void fixDown(PQ head, int i, int size) {
	while (2*i + 1 <= size -1) {
		int j = 2*i + 1;
		//choose lesser of children
		if (j < size-1 && head->array[j].value > head->array[j+1].value) j++;
		//if child not smaller than head heap is fixed
		if (!(head->array[i].value > head->array[j].value)) break;
		
		ItemPQ temp = head->array[j];
		head->array[j] = head->array[i];
		head->array[i] = temp;
		
		i = j;
	}
}

/* Creates new priority queue, that can store items of type ItemPQ.
*/
PQ newPQ(void){
	PQ new = malloc(sizeof(PQRep));
	new->size =0;
	new->array = NULL;
	return new;
}

/* Adds item (ItemPQ) to the priority queue.
   If an item with 'key' exists, it's 'value' is updated.
*/
void addPQ(PQ head, ItemPQ item){
	//check for value in array
	for (int i = 0; i < head->size-1; i++) {
		if (head->array[i].key == item.key) {
			head->array[i].value = item.value;
			fixUp(head, i);
		}
	}
	
	//otherwise add it
	head->size++;
	head->array = realloc(head->array, (head->size) * sizeof(ItemPQ));
	head->array[head->size -1] = item;
	
	fixUp(head, head->size - 1);
}

/* Removes and returns the item (ItemPQ) with smallest 'value'.
   For items with equal 'value', observes FIFO.
   Returns null if this queue is empty.
*/
ItemPQ dequeuePQ(PQ head){
	if (head->size == 0) exit(-1);
	
	ItemPQ popped = head->array[0];
	head->array[0] = head->array[head->size-1];
	head->size--;
	
	fixDown(head, 0, head->size);
	
	return popped;
}

/* Updates item with a given 'key' value, by updating that item's value to the given 'value'.
   If item with 'key' does not exist in the queue, no action is taken
*/
void updatePQ(PQ head, ItemPQ item){
	int i;
	for (i = 0; i < head->size; i++){
		if (head->array[i].key == item.key){
			head->array[i].value = item.value;
			break;
		}
	}
	fixUp(head,i);
}


int PQEmpty(PQ head){
	//return true if empty
	return (head->size == 0) ? 1 : 0;
}

void showPQ(PQ head){
	printf("Data in priority queue:\n");	
	for (int i = 0; i < head->size; i++) printf("%d ", head->array[i].key);
	printf("\n");
	
	printf("Priority of the data:\n");
	for (int i = 0; i < head->size; i++) printf("%d ", head->array[i].value);
	printf("\n");

}

void freePQ(PQ head){
	if(head != NULL){
		free(head->array);
		free(head);
	}
}
