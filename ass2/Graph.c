// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

struct _adjListNode* createNode(Vertex v);
List insertLL(List, int);
List deleteLL(List, int);
bool inLL(List, int);
void freeLL(List);
void showLL(List);

typedef struct GraphRep *Graph{
	_adjListNode *AdjList;
	int nV;
	int nE;
} GraphRep;


struct _adjListNode *createNode(Vertex v) {

   struct _adjListNode *new = malloc(sizeof(struct _adjListNode));
   new->w = v;
	new->weight = 0;
   new->next = NULL;
   return new;
}

List insertLL(List L, int n) {
   if (inLL(L, n))
      return L;

   // add new node at the beginning
   Node *new = makeNode(n);
   new->next = L;
   return new;
}

List deleteLL(List L, int n) {
   if (L == NULL)
      return L;
   if (L->v == n)
      return L->next;

   L->next = deleteLL(L->next, n);
   return L;

}

bool inLL(List L, int n) {
   if (L == NULL)
      return false;
   if (L->v == n)
     return true;

   return inLL(L->next, n);
}

void showLL(List L) {
   if (L == NULL)
      putchar('\n');
   else {
      printf("%d ", L->v);
      showLL(L->next);
   }
}

void freeLL(List L) {
   if (L != NULL) {
      freeLL(L->next);
      free(L);
   }
}

Graph newGraph(int noNodes) {
	
	struct Graph g = malloc(sizeof(GraphRep)); 
	g->nV = noNodes;

	g->edges = malloc(noNodes * sizeof(_adjListNode *));
	int i;
   	for (i = 0; i < noNodes; i++)
      g->edges[i] = NULL;

	return g;
}

int numVerticies(Graph g) {
    
	return nV;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	//create edge from src to dest
    struct _adjListNode *new = createNode(dest);
	new->weight;
    new->next = g->edges[src];
    graph->edges[src] = newNode;
	g->nV++;

	
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
	if (inLL(g->edges[src], dest)) {
		g->edges[src] = deleteLL(g->edges[src], dest;
	}
 
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
   assert (g != NULL);
   return inLL(g->edges[src], dest);
}

AdjList outIncident(Graph g, Vertex v) {
	return NULL;
}

AdjList inIncident(Graph g, Vertex v) {
	return NULL;
}

void  showGraph(Graph g) {
	assert(g != NULL);
    int i;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++) {
       printf("%d - ", i);
       showLL(g->edges[i]);	
    }

}

void  freeGraph(Graph g) {
	assert(g != NULL);
   	int i;

   	for (i = 0; i < g->nV; i++)
      freeLL(g->edges[i]);

   	free(g);
}
