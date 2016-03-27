//
//  DetectCycleinDG.cpp
//  
//  Modified by 罗铮 on 03/13/14.
//
//  http://www.geeksforgeeks.org/bipartite-graph/
//  C++ program to find out whether a given graph is Bipartite or not
//  A typical graph coloring problem
/*
    Algorithm to check if a graph is Bipartite:
    One approach is to check whether the graph is 2-colorable or not using 
    backtracking algorithm m coloring problem.
    Following is a simple algorithm to find out whether a given graph 
    is Birpartite or not using Breadth First Search (BFS).
    1.  Assign RED color to the source vertex (putting into set U).
    2.  Color all the neighbors with BLUE color (putting into set V).
    3.  Color all neighbor’s neighbor with RED color (putting into set U).
    4.  This way, assign color to all vertices such that it satisfies all the 
        constraints of m way coloring problem where m = 2.
    5.  While assigning colors, if we find a neighbor which is 
        colored with same color 
        as current vertex, then the graph cannot be colored with 2 
        vertices (or graph is not Bipartite)
*/

#include <iostream>
#include <queue>

#define V 4

using namespace std;
 
// This function returns true if graph G[V][V] is Bipartite, else false
bool isBipartite(int G[][V], int src)
{
    // Create a color array to store colors assigned to all veritces. Vertex 
    // number is used as index in this array. The value '-1' of  colorArr[i] 
    // is used to indicate that no color is assigned to vertex 'i'.  The value 
    // 1 is used to indicate first color is assigned and value 0 indicates 
    // second color is assigned.
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;
 
    // Assign first color to source
    colorArr[src] = 1;
 
    // Create a queue (FIFO) of vertex numbers and enqueue source vertex
    // for BFS traversal
    queue <int> q;
    q.push(src);
 
    // Run while there are vertices in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
        int u = q.front();
        q.pop();
 
         // Find all non-colored adjacent vertices
        for (int v = 0; v < V; ++v)
        {
            // An edge from u to v exists and destination v is not colored
            if (G[u][v] && colorArr[v] == -1)
            {
                // Assign alternate color to this adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
 
            //  An edge from u to v exists and destination v is colored with
            // same color as u
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
 
    // If we reach here, then all adjacent vertices can be colored with 
    // alternate color
    return true;
}
 
// Driver program to test above function
int main()
{
    int G[][V] = {{0, 1, 0, 1},
                  {1, 0, 1, 0},
                  {0, 1, 0, 1},
                  {1, 0, 1, 0}};
 
    isBipartite(G, 0) ? cout << "Yes\n" : cout << "No\n";
    
    return 0;
}