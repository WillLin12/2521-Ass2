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
		new->pred[i] = malloc(sizeof(PredNode));
		new->pred[i]->v = -1;
		new->pred[i]->next = NULL;
		i ++;
	}
	//make a PQ and add src to PQ
	PQ pq = newPQ();
	new->dist[new->src] = 0;
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
			if (new->dist[adj->w] > new->dist[curr.key] + adj->weight) {
				Relaxation(new, curr.key, adj->w, adj->weight);
				//add adj to queue
				ItemPQ *insert = makeItem(new, adj->w);
				addPQ(pq, *insert);
			}
			adj = adj->next;
		}

		//loop through all adjacent vertex of curr and relax + add to queue
		/* Vertex adj = 0;
		while (adj <= new->noNodes) {
			if (adjacent(g, curr.key, adj)) {
				if (new->dist[adj] > new->dist[curr.key] + curr.value) {
					//relaxation 
					Relaxation (new, curr.key, adj, curr.value);
					//add vertex to queue
					ItemPQ *insert = makeItem(new, adj);
					addPQ(pq, *insert);
				}
			}
				adj ++;	
		} */
	}
	//set pred to NULL properly
	i = 0;
	while (i < new->noNodes) {
		if (new->pred[i]->v == -1){
			new->pred[i] = NULL;
		}
		i ++;
	}

	return *new;


}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

static void Relaxation(ShortestPaths *s, int v, int w, int weight) {
	//if (s->dist[v] + weight < s->dist[w]) {
		s->dist[w] = s->dist[v] + weight;
		s->pred[w]->v = v;
		
	//}

}
static ItemPQ *makeItem(ShortestPaths *s, Vertex v) {
	ItemPQ *item = malloc(sizeof(ItemPQ));
	item->key = v;
	item->value = s->dist[v];
	return item;
}
