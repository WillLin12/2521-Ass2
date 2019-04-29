#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

static NodeValues *newNode(Graph g);

static NodeValues *newNode(Graph g) {
	NodeValues *newNode = malloc(sizeof (NodeValues));
	newNode->noNodes = numVerticies(g);
	newNode->values = malloc(newNode->noNodes*(sizeof (double)));
	int i = 0;
	while (i < newNode->noNodes) {
		newNode->values[i] = 0;
		i++;
	} 
	return newNode;
}
static int pathFinder(Graph g, int src, int last, int currPred, int predListNo,
 ShortestPaths shortestPath, NodeValues *myNode);

NodeValues outDegreeCentrality(Graph g) {
	NodeValues *myNode = newNode(g);
	int i = 0;
	while (i < myNode->noNodes) { 
		AdjList myList = outIncident (g, i); //create list of outincidents
		while (myList != NULL ) {
			myNode->values[i] += 1; //increment the values in NodeValues
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
			myNode->values[i] += 1; //increment in NodeValues
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
		AdjList myList = inIncident (g, i); //create two lists of Incidents
		AdjList myListTwo = outIncident (g, i);
		while (myList != NULL) {
			myNode->values[i]++; //increment as above
			myList = myList->next;
		}
		while (myListTwo != NULL) {
			myNode->values[i]++;
			myListTwo = myListTwo->next;
		}
		i++;
	}
	return *myNode;
}

NodeValues closenessCentrality(Graph g) {	
	NodeValues *myNode = newNode (g);
	int i = 0;

	while (i < myNode->noNodes) {
		int n = 0;
		AdjList myList = inIncident (g, i); //create two lists of incidents
		AdjList myListTwo = outIncident (g, i);
		
		while (myList != NULL) {//increment n as no of nodes that can be reached
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

		while (j < Distance.noNodes) {	//increment shortest distance for every node
			shortestDistance = shortestDistance + Distance.dist[j]; 
			j++;
		}
		myNode->values[i] = ((n - 1)/(numVerticies(g) - 1)) * 
		((n -1)/shortestDistance); //apply formula
		i++;
	}
	return *myNode;
}

NodeValues betweennessCentrality(Graph g) { //warning does not work
	double sum = 0;
	NodeValues *myNode = newNode(g);
	int i = 0;
	int predCount = 0;
	while (i < myNode->noNodes) {
		ShortestPaths new = dijkstra(g, i); //makes sure all vertices are covered
		predCount = 0;
		while (predCount < new.noNodes) { //makes sure all shortest paths of a vertex are covered				
			if (new.pred[predCount] != NULL) {
				sum = pathFinder (g, i, predCount, predCount, 
				new.pred[predCount]->v, new, myNode); //calculate sum of all shortest paths
			}
			predCount++;
		}
		i++;
	}
	i = 0;
	while(i < myNode->noNodes) {
		myNode->values[i] = ((myNode->values[i])/sum); //apply formula
		i++;
	}
	return *myNode;
}
NodeValues betweennessCentralityNormalised(Graph g) { 
	NodeValues *myNode = newNode(g);
	int i = 0;

	while (i < myNode->noNodes) {
		int n = 0;
		AdjList myList = inIncident (g, i); //create two lists of incidents
		AdjList myListTwo = outIncident(g, i);
		
		while (myList != NULL) {//increment n as no of nodes that can be reached
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

		while (j < Distance.noNodes) { //increment shortest distance for every node
			shortestDistance = shortestDistance + Distance.dist[j]; 
			j++;
		}			//apply formula
		myNode->values[i] = (1/((n-1)*(n-2)) * betweennessCentrality(g).values[i]);
		i++;
	}
	return *myNode;
}
static int pathFinder(Graph g, int src, int last, 
int currPred, int predListNo, ShortestPaths shortestPath, NodeValues *myNode) {
	//if the path isnt the first vertice or last vertice in path
	if (predListNo != src && predListNo != last) { 
		myNode->values[shortestPath.pred[predListNo]->v]++; //adds to the double* array
	}
	if (shortestPath.pred[currPred]->next != NULL) { //if there are more pred
		return pathFinder(g, src, last, currPred, shortestPath.pred[currPred]
		->next->v ,shortestPath, myNode); //return pred->next
	} else if (shortestPath.pred[currPred] != NULL && 
	shortestPath.pred[currPred]->next == NULL && shortestPath.pred[predListNo] 
	== NULL) { //if no more predecessor in current array and the pred of current int is NULL
		return 1;
	} else if (shortestPath.pred[currPred] != NULL && 
	shortestPath.pred[currPred]->next == NULL && shortestPath.pred[predListNo]
	 != NULL) {//if no more predecessor in current array and the pred of current int is not NULL
		return pathFinder(g, src, last, predListNo, 
		shortestPath.pred[predListNo]->v, shortestPath, myNode); //go to pred of current int
	} 
	if (shortestPath.pred[currPred]->next != NULL && 
	shortestPath.pred[predListNo] == NULL) {//after recursion to backtrack 
		return 1;
		
	} else if (shortestPath.pred[currPred]->next != NULL && 
	shortestPath.pred[predListNo] != NULL) {//after recursion backtrack predecessor
		return pathFinder(g, src, last, predListNo, 
		shortestPath.pred[predListNo]->v, shortestPath, myNode);
	}
	if (shortestPath.pred[currPred] == NULL) {
		return 1;
	}	
	return 1;
}

void showNodeValues(NodeValues values) {
	for (int i = 0; i < values.noNodes; i++) {
		printf("%d: %lf\n", i, values.values[i]);
	}
}

void freeNodeValues(NodeValues values) {
	free(values.values);
}
