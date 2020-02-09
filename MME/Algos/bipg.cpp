/* CODE IS NOT MINE, TAKEN FROM THEW FOLLOWING LINK
https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
ALONG THE CODE THERE ARE SOME CUSTOMIZATION */

#include<bits/stdc++.h> 
#include <stdlib.h>     /* srand, rand */
#include <typeinfo>

#include "bipg.h"

using namespace std; 

#define NIL 0 
#define INF INT_MAX 

// Returns size of maximum matching 
set<int> BipGraph::hopcroftKarp() 
{ 
    pairU = new int[m+1]; 
    pairV = new int[n+1]; 
  
    dist = new int[m+1]; 
  
    set<int> matched_nodes_index;

    // Initialize NIL as pair of all vertices 
    for (int u=0; u<m; u++) 
        pairU[u] = NIL; // M = empty
    for (int v=0; v<n; v++) 
        pairV[v] = NIL; 
  
    // Initialize result 
    int result = 0; 
  
    // Keep updating the result while there is an augmenting path. 
    while (bfs()) 
    { 
        // Find a free vertex 
        for (int u=1; u<=m; u++) 
  
            // If current vertex is free and there is 
            // an augmenting path from current vertex 
            if (pairU[u]==NIL && dfs(u)){
                result++;
                matched_nodes_index.insert(u-1);
            } // 
                //result++; 
    } 

    return matched_nodes_index; 
} 
  
// Returns true if there is an augmenting path, else returns 
// false 
bool BipGraph::bfs() 
{ 
    queue<int> Q; //an integer queue 
  
    // First layer of vertices (set distance as 0) 
    for (int u=1; u<=m; u++) 
    { 
        // If this is a free vertex, add it to queue 
        if (pairU[u]==NIL) 
        {   dist[u] = 0; 
            Q.push(u); 
        } 
  
        // Else set distance as infinite so that this vertex 
        // is considered next time 
        else dist[u] = INF; 
    } 
  
    // Initialize distance to NIL as infinite 
    dist[NIL] = INF; 
  
    // Q is going to contain vertices of left side only.  
    while (!Q.empty()) 
    { 
        // Dequeue a vertex 
        int u = Q.front(); 
        Q.pop(); 
  
        // If this node is not NIL and can provide a shorter path to NIL 
        if (dist[u] < dist[NIL]) 
        { 
            // Get all adjacent vertices of the dequeued vertex u 
            list<int>::iterator i; 
            for (i=adj[u].begin(); i!=adj[u].end(); ++i) 
            { 
                int v = *i; 
  
                // If pair of v is not considered so far 
                // (v, pairV[V]) is not yet explored edge. 
                if (dist[pairV[v]] == INF) 
                { 
                    // Consider the pair and add it to queue 
                    dist[pairV[v]] = dist[u] + 1; 
                    Q.push(pairV[v]); 
                } 
            } 
        } 
    } 
  
    // If we could come back to NIL using alternating path of distinct 
    // vertices then there is an augmenting path 
    return (dist[NIL] != INF); 
} 

// se il nodo considerato non è NIL
 
// Returns true if there is an augmenting path beginning with free vertex u 
bool BipGraph::dfs(int u) 
{ 
    if (u != NIL) 
    { 
        list<int>::iterator i; 
        for (i=adj[u].begin(); i!=adj[u].end(); ++i) // itero su tutti i primi vicini del nodo
        { 
            // Adjacent to u 
            int v = *i; 
	    // cout <<" z "<< pairV[v] << " " << dist[u]+1 << "\n";
            // Follow the distances set by BFS 
            if (dist[pairV[v]] == dist[u]+1) 
            { 
                // If dfs for pair of v also returns 
                // true 
                if (dfs(pairV[v]) == true) 
                { 
                    pairV[v] = u; 
                    pairU[u] = v; 
                    return true; 
                } 
            } 
        } 
  
        // If there is no augmenting path beginning with u. 
        dist[u] = INF; 
        return false; 
    } 
    return true; 
} 

void BipGraph::print_adj()
{
for(int u=0; u<m; u++){
   for(auto p : adj[u] ){
	cout << p << " ";}
	cout << "\n"; }
}


// Constructor 
BipGraph::BipGraph(int m, int n) 
{ 
    this->m = m; 
    this->n = n; 
    adj = new list<int>[m+1]; 
} 

BipGraph::~BipGraph()
{
delete[] adj;
delete[] pairU;
delete[] pairV;
delete[] dist;
}

 
// To add edge from u to v and v to u 
void BipGraph::addEdge(int u, int v) 
{ 
    adj[u].push_back(v);
} 








