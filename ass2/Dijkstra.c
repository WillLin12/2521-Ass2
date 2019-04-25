// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

static void Relaxation(ShortestPaths *s, int v, int w, int weight);
static ItemPQ *makeItem(ShortestPaths *s, Vertex v);

ShortestPaths dijkstra(Graph g, Vertex v) {
	//initialise shortestpath
	ShortestPaths *new = malloc(sizeof(ShortestPaths));
	new->src = v;
	new->noNodes = numVerticies(g);
	new->pred = malloc(new->noNodes*sizeof(PredNode *));
	new->dist = malloc(new->noNodes*sizeof(int));

	//initalise dist and preds
	int i = 0;
	while (i < new->noNodes) {
		new->dist[i] = INT_MAX;
		new->pred[i] = NULL;
		//new->pred[i] = malloc(sizeof(PredNode));
		//new->pred[i]->v = -1;
		//new->pred[i]->next = NULL;
		i ++;
	}
	//make a PQ and add src to PQ
	new->dist[new->src] = 0;
	PQ pq = newPQ();
	ItemPQ *source = makeItem(new, v);
	addPQ(pq, *source);


	// actual Dijkstras stuff
	while (!PQEmpty(pq)){
		//take smallest distance vertex from queue
		ItemPQ curr = dequeuePQ(pq);

		//loop through all vertices adjacent to curr adj = adjacent vertex
		AdjList adj = outIncident(g, curr.key);
		while (adj != NULL) {
			//relax
			// Next debug step: set a new if statement if node == 3 and trying to relaxation
			if (new->dist[adj->w] >= new->dist[curr.key] + adj->weight) {
				// IF (node == 3) print something / break in GDB
				Relaxation(new, curr.key, adj->w, adj->weight);
				//add adj to queue
				ItemPQ *insert = makeItem(new, adj->w);
				addPQ(pq, *insert);
				//ItemPQ *update = makeItem(new, adj->w);
				//updatePQ(pq, *update);

				//update PQ
			}
			adj = adj->next;
		}
	}




	int j = 0;
	while (j < new->noNodes) {
		if (new->dist[j] == INT_MAX) {
			new->dist[j] = 0;
		}
		j ++;
	}
	/*for (int i = 0; i < new->noNodes; i++) {
		printf("Vertex %d: %d\n", i ,new->dist[i]);
	} */
	//set pred to NULL properly


/*
	i = 0;
	while (i < new->noNodes) {
		if (new->pred[i]->v == -1){
			new->pred[i] = NULL;
		}
		i ++;
	}
*/
	return *new;


}

//helper function to malloc prednode

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

static void Relaxation(ShortestPaths *s, int v, int w, int weight) {
	//if (s->dist[v] + weight < s->dist[w]) {
		int old = s->dist[w];
		s->dist[w] = s->dist[v] + weight;

		if (s->pred[w] == NULL) {
			s->pred[w] = malloc(sizeof(PredNode));
			s->pred[w]->v = v;
			s->pred[w]->next = NULL;
		}
		else if (s->dist[w] < old) {
			PredNode *curr = s->pred[w];				
			while (curr != NULL) {
				PredNode *tmp = curr;
				curr = curr->next;
				free(tmp);
			}
			s->pred[w] = malloc(sizeof(PredNode));
			s->pred[w]->v = v;
			s->pred[w]->next= NULL;
		} else if (s->dist[w] == old && s->pred[w]->v != v) {
				PredNode *curr = s->pred[w];
				while (curr->next != NULL) {
					curr = curr->next;
				}
				curr->next = malloc(sizeof(PredNode));
				curr->next->v = v;
		} else if (s->pred[w] == NULL) {
			s->pred[w] = malloc(sizeof(PredNode));
			s->pred[w]->v = v;
			s->pred[w]->next = NULL;
		} else {
			s->pred[w] = malloc(sizeof(PredNode));
			s->pred[w]->v = v;
			s->pred[w]->next = NULL;
		}
 
		/*if (s->dist[w] < old) {
				if (s->pred[w] == NULL) {
					s->pred[w] = malloc(sizeof(PredNode));
					s->pred[w]->v = v;
					s->pred[w]->next = NULL;	
				} else {
					PredNode *curr = s->pred[w];				
					while (curr != NULL) {
						PredNode *tmp = curr;
						curr = curr->next;
						free(tmp);
					}
				}

		} else if (s->dist[w] == old) {
			if (s->pred[w]== NULL) {
				s->pred[w] = malloc(sizeof(PredNode));
				s->pred[w]->v = v;
				s->pred[w]->next = NULL;
			} else {
				PredNode *curr = s->pred[w];
				while (curr->next != NULL) {
					curr = curr->next;
				}
				curr->next = malloc(sizeof(PredNode));
				curr->next->v = v;
			}
		}
		*/
}
static ItemPQ *makeItem(ShortestPaths *s, Vertex v) {
	ItemPQ *item = malloc(sizeof(ItemPQ));
	item->key = v;
	item->value = s->dist[v];
	return item;
}
