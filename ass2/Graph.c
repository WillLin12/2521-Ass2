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
//static AdjList newLList(void);
static void showLL(adjListNode *L);
static void freeLL(adjListNode *L);
static bool inLL(adjListNode *L, Vertex n);

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
        //if edge isnt in graph
        if (!inLL(g->edges[src], dest)) {
            AdjList newNode = newAdjListNode(dest, weight);
            newNode->weight = weight;
            newNode->next = g->edges[src];
            g->edges[src] = newNode;
        
            g->nE++;
        }
}
    
void  removeEdge(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);

    AdjList currPointer = g->edges[src];
    if (currPointer->w == dest) { //case if first node 
        free(currPointer);
    } else {
        AdjList prevPointer = g->edges[src]; 
        while (currPointer->w != dest) {
            prevPointer = currPointer;
            currPointer = currPointer->next;
        }
        if (currPointer->next != NULL) {
            prevPointer->next = currPointer->next;
        } else {
            prevPointer->next = NULL;
        }
        free(currPointer);
    }
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);
    /*AdjList currPointer = g->edges[src];
    while (currPointer != NULL) {
        if (currPointer->w) {
            return true;
        }
        currPointer = currPointer->next;
    }
        
    return false;*/
    return inLL(g->edges[src], dest);
}

AdjList outIncident(Graph g, Vertex v) {
    assert(g != NULL);
    if (g->edges[v] == NULL) {
        return NULL;
    }
    else /*(g->edges[v] != NULL)*/ {
        AdjList currP = g->edges[v];
        return currP;
    }

}

AdjList inIncident(Graph g, Vertex v) {
    assert(g != NULL);

    //AdjList headP = NULL;
    if (v == 0) {return NULL;}
    AdjList n = NULL;
    int i = 0;
    while (i < g->nV) {
        if (inLL(g->edges[i], v)) {
            if (n == NULL) {
                n = newAdjListNode(i, 0);
            } else {
                n->next = newAdjListNode(i,0);
            }
        }
        i ++;
    }
    return n; 
    
    /*AdjList headP = NULL;
    AdjList currP = g->edges[0];
	AdjList listP = NULL;

    int i = 0;
    while (i < g->nV) {
        currP = g->edges[i];
        while (currP != NULL) {
            if (currP->w == v) {
                AdjList newNode = newAdjListNode(v, currP->weight);  
                if (headP == NULL) {
                    headP = newNode;
                    listP = newNode;
                } else {
                    listP->next = newNode;
                }
            }
            currP = currP->next;
        }
        i++;
    }
    free(currP);
    return headP;
    */
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

static AdjList newAdjListNode(Vertex v, int weight) {
    AdjList n = malloc(sizeof (AdjList));
    n->w = v;
    n->weight = weight;
    n->next = NULL;
    return n;
}
/*
static AdjList newLList(void) {
    AdjList n = malloc(sizeof (AdjList));
    n->w = 0;
    n->weight = 0;
    n->next = NULL;
    return n;
}
*/
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

