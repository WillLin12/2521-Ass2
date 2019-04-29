/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#include <limits.h>
#define numVertices numVerticies

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {

    int N = numVertices(g);
    
    //initialise NxN matrix
    double Dist[N][N];
    int i;
    for (i = 0; i < N; i ++) {
      int j;
      for (j = 0; j < N; j ++) {
        Dist[i][j] = INT_MAX;
      }
    }

    //set values of NxN matrix for out incident
    int currV1;
    for (currV1 = 0; currV1 < N; currV1 ++) {
      AdjList out = outIncident(g, currV1);
      while (out != NULL) {
        Dist[currV1][out->w] = (1 / out->weight);
        out = out->next;
      }
    }

    //set values of NxN matrix for in incident, also if the weight of inincident is greater set that as new dist
    int currV2;
    for (currV2 = 0; currV2 < N; currV2 ++) {
      AdjList in = inIncident(g, currV2);
      while (in != NULL) {
        if (Dist[currV2][in->w] > (1 / in->weight)) {
          Dist[currV2][in->w] = (1 / in->weight);
        }
        in = in->next;
      }
    }

    //printf ("%lf", Dist[N][N]);
    DNode **dendA = malloc(sizeof(DNode) * N);
    int j;
    for (j = 0; j < N; j ++) {
      dendA[i]->vertex = j;
    }

  int h;
  int smallest = INT_MAX;
  int clusteri = 0;
  int clusterj = 0;
  for (h = 0; h < (N - 1); h ++) {
    //find closest clusters
    for (i = 0; i < N; i ++) {
      for (j = 0; j < N; j ++) {
        if (smallest > Dist[i][j]) {
          smallest = Dist[i][j];
          clusteri = i;
          clusterj = j;
        }
      }
    }
    Dendrogram new =  malloc(sizeof(DNode));
    new->left->vertex = clusteri;
    new->right->vertex = clusterj;
    dendA[clusteri] = NULL;
    dendA[clusterj] = NULL;
    dendA[clusteri] = new;

    if (method == 1) {
      int k;
      for (k = 0; k < N; k ++) {
        Dist[clusteri][k] = (1/2 * Dist[clusteri][k]) + (1/2 * Dist[clusterj][k]) - (1/2 * abs(Dist[clusteri][k] - Dist[clusterj][k]));
        Dist[clusterj][k] = INT_MAX;
      }
    }
    if (method == 2) {
      int k;
      for (k = 0; k < N; k ++) {
        Dist[clusteri][k] = (1/2 * Dist[clusteri][k]) + (1/2 * Dist[clusterj][k]) + (1/2 * abs(Dist[clusteri][k] - Dist[clusterj][k]));
        Dist[clusterj][k] = INT_MAX;
      }
    }


  }
  Dendrogram dend = NULL;
  for (i = 0; i < N; i ++) {
    if (dendA[i] != NULL) {
      dend = dendA[i];
    }
  }

    return dend;
}



void freeDendrogram(Dendrogram d) {
  if (d->left == NULL && d->right == NULL) {
    free(d);
  }
  freeDendrogram(d->left);
  freeDendrogram(d->right);
}



