// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

static NodeValues *newNode(Graph g);

static NodeValues *newNode(Graph g) {
	NodeValues *newNode = malloc(sizeof(NodeValues));
	newNode->noNodes = numVerticies(g);
	newNode->values = malloc(newNode->noNodes*sizeof (double));
	int i = 0;
	while (i < newNode->noNodes) {
		newNode->values[i] = 0;
		i ++;
	} 
	return newNode;
}

NodeValues outDegreeCentrality(Graph g) {
	NodeValues *myNode = newNode(g);
	int i = 0;
	while (i < myNode->noNodes) {
		AdjList myList = outIncident (g, i);
		while (myList != NULL ) {
			myNode->values[i] += 1;
			myList = myList->next;
		}	
		i++;
	}
	return *myNode;
}

NodeValues inDegreeCentrality(Graph g) {
	NodeValues *myNode = newNode(g);
	int i = 0;
	while (i < myNode->noNodes) {
		AdjList myList = inIncident (g, i);
		while (myList != NULL ) {
			myNode->values[i] += 1;
			myList = myList->next;
		}	
		i++;
	}
	return *myNode;
}

NodeValues degreeCentrality(Graph g) {
	NodeValues throwAway = {0};
	return throwAway;
	//return inDegreeCentrality(g) + outDegreeCentrality(g);
}

NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){
	for (int i = 0; i < values.noNodes; i++) {
		printf("%d: %lf\n", i, values.values[i]);
	} 
}

void freeNodeValues(NodeValues values){

}
