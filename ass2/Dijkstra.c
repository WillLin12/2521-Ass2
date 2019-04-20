// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


ShortestPaths dijkstra(Graph g, Vertex v) {
	ShortestPaths *new = malloc(sizeof(ShortestPaths));
	new->src	 = v;
	new->noNodes = Graph->nV;
	new->dist[] = {9999999};
	new->dist[new.src] = 0;
	new->pred = malloc(new.noNodes*sizeof(PredNode));
	new->pred[] = {-1};

	return new;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

