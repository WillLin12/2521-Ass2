#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include "PQ.h"
#include <assert.h>

typedef struct PQRep *PQ;


typedef struct PQRep{
        int size;
        ItemPQ *item; //array of ItemPQ's
}PQRep;


static void MaxHeap(PQ pq, int index) {
	int i = index;
	int j = (i-1)/2;
	while (i > 0 && pq->item[j].value > pq->item[i].value) {
		
		ItemPQ tmp = pq->item[j];
		pq->item[j] = pq->item[i];
		pq->item[i] = tmp;
		
		i = j;
		j = (i-1)/2;
	}
}

static void MinHeap(PQ pq, int i, int size) {
	while (2*i + 1 <= size -1) {
		int j = 2*i + 1;
		//choose the smaller child
		if (j < size-1 && pq->item[j].value > pq->item[j+1].value) j++;
		//if child isnt smaller fix head heap
		if (!(pq->item[i].value > pq->item[j].value)) {
			break;
		}
		ItemPQ temp = pq->item[j];
		pq->item[j] = pq->item[i];
		pq->item[i] = temp;
		
		i = j;
	}
}

/* Creates new priority queue, that can store items of type ItemPQ.
*/
PQ newPQ(void){
	PQ queue = malloc(sizeof(PQRep));
	queue->size =0;
	queue->item = NULL;
	return queue;
}

/* Adds item (ItemPQ) to the priority queue.
   If an item with 'key' exists, it's 'value' is updated.
*/
void addPQ(PQ pq, ItemPQ item){
	//check for value in array if its in the array update the value and fix the order
	int i = 0;
	while (i < pq->size - 1) {
		if (pq->item[i].key == item.key) {
			pq->item[i].value = item.value;
			MaxHeap(pq, i);
		}
		i ++;
	}

	
	//if its not in the array add it to the PQ and fix the order
	pq->size++;
	pq->item = realloc(pq->item, (pq->size) * sizeof(ItemPQ));
	pq->item[pq->size -1] = item;
	
	MaxHeap(pq, pq->size - 1);
}

//Removes and returns the item with highest priority from the PQ
//If items all have equal priority act like a normal queue ie FIFO
//Cannot be called if PQ is empty

ItemPQ dequeuePQ(PQ pq){
	assert (pq->size > 0);
	
	ItemPQ lowest = pq->item[0];
	pq->item[0] = pq->item[pq->size-1];
	pq->size--;
	
	MinHeap(pq, 0, pq->size);
	
	return lowest;
}

/* Updates item with a given 'key' value, by updating that item's value to the given 'value'.
   If item with 'key' does not exist in the queue, no action is taken
*/
void updatePQ(PQ pq, ItemPQ item){
	int i = 0;
	while (i < pq->size) {
		if (pq->item[i].key == item.key) {
			pq->item[i].value = item.value;
		}
		i ++;
	}

	MaxHeap(pq,i);
}

// if PQ empty return 1 else return 0
int PQEmpty(PQ pq){
	if (pq->size == 0) {
		return 1;
	} else {
		return 0;
	}
}

void showPQ(PQ pq){
	int i = 0;
	printf("Key in PQ:\n");	
	for (i = 0; i < pq->size; i++) {
		printf("%d ", pq->item[i].key);
	}
	printf("\n");
	
	printf("Value in PQ\n");
	for (i = 0; i < pq->size; i++) {
		printf("%d ", pq->item[i].value);
	}
	printf("\n");

}

void freePQ(PQ pq){
	if(pq != NULL){
		free(pq->item);
		free(pq);
	}
}
