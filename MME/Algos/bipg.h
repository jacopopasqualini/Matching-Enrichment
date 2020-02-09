/* CODE IS NOT MINE, TAKEN FROM THEW FOLLOWING LINK
https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
ALONG THE CODE THERE ARE SOME CUSTOMIZATION */

#include<bits/stdc++.h> 
#include <stdlib.h>     /* srand, rand */

using namespace std; 
#ifndef Cube_h
#define BipGraph_h
  
class BipGraph 
{ 

private:

    int m, n;
    list<int> *adj; 
    int *pairU, *pairV, *dist; 
  
public: 

    BipGraph(int m, int n); 
   ~BipGraph();
    void addEdge(int u, int v); 
    void print_adj();
    bool bfs(); // esiste un augpath?
    bool dfs(int u); // aggiunge un aug.path se ce n'è uno che inizia con u


    set<int> hopcroftKarp();
};

#endif
