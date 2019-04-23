// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

static NodeValues newNode() {
	NodeValues newNode = malloc(sizeof(NodeValues));
	newNode->noNodes = 0 ;
	newNode->values = 0;
	return newNode;
}

NodeValues outDegreeCentrality(Graph g){
	NodeValues myNode = newNode();
	myNode->noNodes = numVertices(g);
	myNode->values = malloc(noNode*sizeof (double);
	int i = 0;
	while (i < myNode->noNodes) {
		Adjlist myList = outIncident (g, i);
		while (myList != NULL ) {
			myNode->values[i]++;
			myList = myList->next;
		}	
		i++;
	}
	return myNode;
}

NodeValues inDegreeCentrality(Graph g) {
	NodeValues myNode = newNode();
	myNode->noNodes = numVertices(g);
	myNode->values = malloc(noNode*sizeof (double);
	int i = 0;
	while (i < myNode->noNodes) {
		Adjlist myList = inIncident (g, i);
		while (myList != NULL ) {
			myNode->values[i]++;
			myList = myList->next;
		}	
		i++;
	}
	return myNode;
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

}

void freeNodeValues(NodeValues values){

}
