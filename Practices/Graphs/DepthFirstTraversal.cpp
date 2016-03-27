//
//  DepthFirstTraversal.cpp
//
//  Modified by 罗铮 on 03/16/14.
//  http://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/
//  
//  C++ program for depth first graph traversal

/*
    Note that the above code traverses only the vertices reachable from
    a given source vertex. All the vertices may not be reachable from a
    given vertex (example Disconnected graph). To do complete DFS traversal
    of such graphs, we must call DFSUtil() for every vertex. 
	Also, before calling DFSUtil(), we should check if it is already 
	printed by some other call of DFSUtil(). 
	Following implementation does the complete graph traversal even 
	if the nodes are unreachable. 
	The differences from the above code are highlighted in the below code.
*/

#include <iostream>
#include <list>

using namespace std;
 
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    void DFSUtil(int v, bool visited[]);  // A function used by DFS
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void DFS(int v);    // prints DFS traversal of the complete graph
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited);
}
 
// The function to do DFS traversal. It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
 	// Call the recursive helper function to print DFS traversal
    DFSUtil(v, visited);

    // Call the recursive helper function to print DFS traversal
    // starting from all vertices one by one
    // This solves the disconnected graph problem
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            DFSUtil(i, visited);
}
 
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Depth First Traversal (starting from vertex 2) \n";
    g.DFS(2);
 	cout << endl;

    return 0;
}