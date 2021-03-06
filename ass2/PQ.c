// PQ ADT interface for Ass2 (COMP2521)
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
/*
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
*/
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
	ItemNode *myItem = malloc(sizeof (ItemNode *));
	myItem->Item = item;
	myItem->next = NULL;
	return myItem;
}
void  showPQ(PQ pq) {

}

void  freePQ(PQ pq) {	

}
