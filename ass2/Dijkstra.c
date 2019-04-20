// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
static void Relaxation(ShortestPaths *s, int v, int w, int weight) ;

ShortestPaths dijkstra(Graph g, Vertex v) {
	ShortestPaths *new = malloc(sizeof(ShortestPaths));
	new->src = v;
	new->noNodes = numVerticies(g);
	new->pred = malloc(new->noNodes*sizeof(PredNode));
	for(int i = 0; i < new->noNodes; i++) {
		new->dist[i] = INT_MAX;
		new->pred[i]->v= -1;
	}
	PQ pq = newPQ();
	addPQ(pq, new->src); //figure out how to add src vertex to PQ
	new->dist[new->src] = 0;

	while (!PQEmpty(pq)){

	}
	return *new;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

static void Relaxation(ShortestPaths *s, int v, int w, int weight) {
	if (s->dist[v] + weight < s->dist[w]) {
		s->dist[w] = s->dist[v] + weight;
		s->pred[w]->v = v;
		
	}

}