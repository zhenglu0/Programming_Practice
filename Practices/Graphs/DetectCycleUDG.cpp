//
//  DetectCycleinDG.cpp
//  
//  Modified by 罗铮 on 03/13/14.
// 
//  http://www.geeksforgeeks.org/detect-cycle-undirected-graph/
//  
//  A C++ Program to detect cycle in an undirected graph

#include <iostream>
#include <list>
#include <climits>

using namespace std;
 
// Class for an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    bool isCyclicUtil(int v, bool visited[], int parent);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    bool isCyclic();   // returns true if there is a cycle
    bool isCyclic_count(); // returns true if there is a cycle
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Add v to w’s list.
}

// #1 The first method is use the DFS, mark the vertex visited 
// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
bool Graph::isCyclicUtil(int v, bool visited[], int parent)
{
    // Mark the current node as visited
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        // If an adjacent is not visited, then recur for that adjacent
        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, v))
              return true;
        }
        // If an adjacent is visited and not parent of current vertex,
        // then there is a cycle.
        else if (*i != parent)
           return true;
    }
    return false;
}
 
// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion stack
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for (int u = 0; u < V; u++)
        if (!visited[u] && isCyclicUtil(u, visited, -1))
            return true;

    delete [] visited;
    return false;
}

// #2
// The second one is a trick for a undirected graph
// we get the number of nodes <= number of edges in the graph
// There will be cycles in the graph
bool Graph::isCyclic_count()
{
	int totalEdges = 0;
	for (int i = 0; i < V; i++)
		totalEdges += adj[i].size();

	totalEdges /= 2; // each edge is counted twice
	
	//cout << "total edge = " 
	//	 << totalEdges << endl;

	if (V <= totalEdges)
		return true;
	else
		return false;
}


// Driver program to test above functions
int main()
{
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 0);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.isCyclic()? cout << "g1 contains cycle\n":
                   cout << "g1 doesn't contain cycle\n";
    g1.isCyclic_count()? cout << "g1 contains cycle\n":
                   		 cout << "g1 doesn't contain cycle\n";

    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.isCyclic()? cout << "g2 contains cycle\n":
                   cout << "g2 doesn't contain cycle\n";
    g2.isCyclic_count()? cout << "g2 contains cycle\n":
                   		 cout << "g2 doesn't contain cycle\n";
    return 0;
}