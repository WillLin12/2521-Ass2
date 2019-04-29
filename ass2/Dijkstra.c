// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

static void Relaxation(ShortestPaths *s, int v, int w, int weight);
static ItemPQ *makeItem(ShortestPaths *s, Vertex v);
static void freeLL(PredNode *L);

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
			//if distance of current Node + weight to w is less that distance w relax: update Distance and pred and add to queue 
			if (new->dist[adj->w] >= new->dist[curr.key] + adj->weight) {

				if (new->dist[adj->w] > new->dist[curr.key] + adj->weight) {
					Relaxation(new, curr.key, adj->w, adj->weight);
					ItemPQ *insert = makeItem(new, adj->w);
					addPQ(pq, *insert);

			// if same distance just relax ie just update Pred
				} else {
					Relaxation(new, curr.key, adj->w, adj->weight);	
				}

			}
			adj = adj->next;
		}
	}

	//Set unreachable nodes to distance 0
	int j = 0;
	while (j < new->noNodes) {
		if (new->dist[j] == INT_MAX) {
			new->dist[j] = 0;
		}
		j ++;
	}

	return *new;
}

//show shortest paths from testDijkstra file
void showShortestPaths(ShortestPaths paths) {
int i = 0;
	printf("Node %d\n",paths.src);
	printf("  Distance\n");
	for (i = 0; i < paths.noNodes; i++) {
			if(i == paths.src)
	    	printf("    %d : X\n",i);
			else
				printf("    %d : %d\n",i,paths.dist[i]);
	}
	printf("  Preds\n");
	for (i = 0; i < paths.noNodes; i++) {
		int numPreds = 0;
		int preds[paths.noNodes];
		printf("    %d : ",i);
		PredNode *curr = paths.pred[i];
		while (curr != NULL && numPreds < paths.noNodes) {
			preds[numPreds++] = curr->v;
			curr = curr->next;
		}
		
		// Insertion sort
		for (int j = 1; j < numPreds; j++) {
			int temp = preds[j];
			int k = j;
			while (preds[k - 1] > temp && k > 0) {
				preds[k] = preds[k - 1];
				k--;
			}
			preds[k] = temp;
		}
		
		for (int j = 0; j < numPreds; j++) {
			printf("[%d]->", preds[j]);
		}
		printf("NULL\n");
	}
}


void  freeShortestPaths(ShortestPaths paths) {
	free(paths.dist);
	int i;
	for (i = 0; i < paths.noNodes; i ++){
		freeLL(paths.pred[i]);
	}
	free(paths.pred);
}

//helper function to do relaxation
static void Relaxation(ShortestPaths *s, int v, int w, int weight) {
	//if (s->dist[v] + weight < s->dist[w])
		int old = s->dist[w];
		s->dist[w] = s->dist[v] + weight;

		// if pred is empty set pred to v
		if (s->pred[w] == NULL) {
			s->pred[w] = malloc(sizeof(PredNode));
			s->pred[w]->v = v;
			s->pred[w]->next = NULL;
		}
		//if a new shortest path is found free all of the old pred and make a new pred 
		if (s->dist[w] < old) {
			PredNode *curr = s->pred[w];				
			while (curr != NULL) {
				PredNode *tmp = curr;
				curr = curr->next;
				free(tmp);
			}
			s->pred[w] = malloc(sizeof(PredNode));
			s->pred[w]->v = v;
			s->pred[w]->next= NULL;
		//if path of same distance as shortest is found append to pred
		} else if (s->dist[w] == old && s->pred[w]->v != v) {
				int test = -100;
				PredNode *curr = s->pred[w];
				while (curr->next != NULL) {
					if (curr->next->v == v) {
						test = 100;
					}
					curr = curr->next;
				}
				if (test != 100) {
				curr->next = malloc(sizeof(PredNode));
				curr->next->v = v;
				curr->next->next = NULL;
				}
		}

}
//helper function to make item for PQ
static ItemPQ *makeItem(ShortestPaths *s, Vertex v) {
	ItemPQ *item = malloc(sizeof(ItemPQ));
	item->key = v;
	item->value = s->dist[v];
	return item;
}

static void freeLL(PredNode *L) {
   if (L != NULL) {
      freeLL(L->next);
      free(L);
   }
}