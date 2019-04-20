// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static void Relaxation(ShortestPaths s, int v, int w, int weight);

ShortestPaths dijkstra(Graph g, Vertex v) {
	ShortestPaths new = malloc(sizeof(struct ShortestPaths));
	new.src	 = v;
	new.noNodes = Graph->nV;
	new.dist[] = {9999999};
	new.dist[new.src] = 0;
	new.pred = malloc(new.noNodes*sizeof(PredNode));
	new.pred[] = {-1};

	return new;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

static void Relaxation(ShortestPaths s, int v, int w, int weight) {
	if (s.dist[v] + weight < s.dist[w]) {
		s.dist[w] = s.dist[v] + weight;
		s.pred[w] = v;
		
	}

}