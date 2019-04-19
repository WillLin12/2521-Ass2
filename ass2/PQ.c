// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
static typedef struct LListrep {
	ItemPQ *item;
	newLList *next;
} LListrep;

static typedef LListrep *List;

static List makeLList () {
	assert(list != NULL);
	List L = malloc(sizeof (LListrep));
	L->next = NULL;
	L->item = NULL;
	return L;
}
*/




typedef struct ItemNode ItemNode;
typedef struct ItemNode *ItemNodePointer;

static struct ItemNode {
	ItemPQ *Item;
	struct ItemNode *next;
}

//typedef struct ItemNode ItemNode;
//typedef struct ItemNode *ItemNodePointer;


typedef struct PQRep {
	int nItems;
	//ItemPQ *items;
	//int nslots;
	ItemNodePointer first;
	ItemNodePointer last; //smallest
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
	assert(pq != NULL);
	if (pq->nItems == 0) {
		ItemNode *newNode = makeItemNode(element);
		pq->first = newNode;
		pq->last = newNode;
		pq->nItems++;
		
	} else {
		ItemNodePointer currP = pq->first;
		ItemNodePointer prevP = pq->first;
		if (element.key <= currP->Item->key) { //key is less than first item's key
			ItemNode *newNode = makeItemNode(element);
			newNode->next = currP;
			pq->first = newNode;
			pq->nItems++;
			
		} else {
			while (currP->next != NULL) {
				if (element.key == currP->Item->key) {
					currP->Item->value = element.value;
					break;
				} else if (element.key < currP->Item->key && element.key > currP->next->Item->key) {
					ItemNode *newNode = makeItemNode(element);
					newNode->next = currP->next;
					currP->next = newNode;
					pq->nItems++;
					break;
				}	
				prevP = currP;
				currP = currP->next;
			}
			if (element.key < currP->Item->key || element.key == currP->Item->key) {
				ItemNode *newNode = makeItemNode(element);
				newNode->next = currP;
				prevP->next = newNode;
				pq->nItems++;
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
	
	ItemPQ item = pq->last->Item;
	ItemNodePointer lastP = pq->last;
	ItemNodePointer currP = pq->first;

	while (currP->next->next != NULL) {
		currP = currP->next;
	}
 	currP->next = NULL;
 	free(lastP);
	return item;
}

void updatePQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	ItemNodePointer currP = pq->first;
	while (currP != NULL) {
		if (currP->Item->key = element.key) {
			currP->Item->value = element.value;
			break;
		}
		currP = currP->next;
	}
}

ItemNodePointer makeItemNode(ItemPQ item) { //problems with static
	ItemNode *myItem = malloc(sizeof (ItemNode));
	myItem->Item = item;
	myItem->next = NULL;
	return myItem;
}
void  showPQ(PQ pq) {

}

void  freePQ(PQ pq) {	

}
