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
	NodeValues *myNode = newNode(g);
	int i = 0;
	while (i < myNode->noNodes) {
		AdjList myList = inIncident (g, i);
		AdjList myListTwo = outIncident(g, i);
		while (myList != NULL) {
			myNode->values[i]++;
			myList = myList->next;
		}
		while (myListTwo != NULL) {
			myNode->values[i]++;
			myListTwo = myListTwo->next;
		}
		i++;
	}
	return *myNode;
	//return inDegreeCentrality(g) + outDegreeCentrality(g);
}

NodeValues closenessCentrality(Graph g){
	NodeValues *myNode = newNode(g);
	int i = 0;

	while (i < myNode->noNodes) {
		int n = 0;
		AdjList myList = inIncident (g, i);
		AdjList myListTwo = outIncident(g, i);
		while (myList != NULL) {
			n++;
			myList = myList->next;
		}
		while (myListTwo != NULL) {
			n++;
			myListTwo = myListTwo->next;
		}
		ShortestPaths Distance = dijkstra(g, i);
		int shortestDistance = 0;
		int j = 0;

		while (j < Distance.noNodes) {
			shortestDistance = shortestDistance + Distance.dist[j];
			j++;
		}
		
		myNode->values[i] = ((n-1)/(numVerticies(g) - 1)) * ((n -1)/shortestDistance);
		i++;

	}
	return *myNode;
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
