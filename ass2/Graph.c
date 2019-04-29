// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

struct GraphRep {
    adjListNode** edges;
    int nV;
   	int nE;
};

static AdjList newAdjListNode(Vertex v, int weight);
static void showLL(adjListNode *L);
static void freeLL(adjListNode *L);
static bool inLL(adjListNode *L, Vertex n);
static AdjList deleteLL(adjListNode *L, int n);

Graph newGraph(int noNodes) {
    assert(noNodes != 0);

    //create empty graph
    Graph g = malloc(sizeof(struct GraphRep));
    g->nV = noNodes;
    g->nE = 0;

    g->edges = malloc(noNodes *sizeof(adjListNode *));

    // set all edges to empty
    int i = 0;
    while (i < noNodes) {
        g->edges[i] = NULL;
        i++;
    }

    return g;
}

int numVerticies(Graph g) {
    return g->nV;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
    assert(g != NULL);
        //if edge isnt in graph make a new edge
        if (!inLL(g->edges[src], dest)) {
            AdjList newNode = newAdjListNode(dest, weight);
            newNode->weight = weight;
            newNode->next = g->edges[src];
            g->edges[src] = newNode;
            //incremenet 
            g->nE++;
        }
}
    
void  removeEdge(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);

	if (inLL(g->edges[src], dest)) {   // edge e in graph
      g->edges[src] = deleteLL(g->edges[src], dest); // remove edge
      g->nE--; //decrese nE
   }
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);
    // if there is an edge return true else return false
    return inLL(g->edges[src], dest);
}

AdjList outIncident(Graph g, Vertex v) {
    assert(g != NULL);
    //if no edge return null
    if (g->edges[v] == NULL) {
        return NULL;
    }
    //if edge return all adjacent
    else  {
        AdjList currP = g->edges[v];
        return currP;
    }

}

AdjList inIncident(Graph g, Vertex v) {
    assert(g != NULL);

    AdjList n = NULL;
    int i = 0;
    while (i < g->nV) { //loop through all edges
        if (inLL(g->edges[i], v)) { // if vertex is in an edge list
            if (n == NULL) { // if empty make new head of List i
                n = newAdjListNode(i, 0);
            } else { //append to list 
                AdjList curr = n;
                while (curr->next != NULL) {
                    curr = curr->next;
                }
                curr->next = newAdjListNode(i,0);
            }
        }
        i ++;
    }
    return n; 
}
//function to show graph
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

//function to free graph
void  freeGraph(Graph g) {
    assert(g != NULL);
    int i;

    for (i = 0; i < g->nV; i++)
      freeLL(g->edges[i]);

    free(g);
}

//helper function to make an AdjList node
static AdjList newAdjListNode(Vertex v, int weight) {
    AdjList n = malloc(sizeof (adjListNode));
    n->w = v;
    n->weight = weight;
    n->next = NULL;
    return n;
}


//All functions below are helper functions from lectures
static void showLL(adjListNode *L) {
   if (L == NULL)
      putchar('\n');
   else {
      printf("%d ", L->w);
      showLL(L->next);
   }
}

static void freeLL(adjListNode *L) {
   if (L != NULL) {
      freeLL(L->next);
      free(L);
   }
}

static bool inLL(adjListNode *L, Vertex n) {
   if (L == NULL)
      return false;
   if (L->w == n)
     return true;
     
   return inLL(L->next, n);
}

static AdjList deleteLL(adjListNode *L, int n) {
   if (L == NULL)
      return L;
   if (L->w == n)
      return L->next;

   L->next = deleteLL(L->next, n);
   return L;

}
