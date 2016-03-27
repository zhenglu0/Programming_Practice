//
//  GraphCopy.cpp
//  
//  Modified by 罗铮 on 03/16/14.
//
//  http://leetcode.com/2012/05/clone-graph-part-i.html
//  
//  A C++ Program to graph copy

#include <iostream>
#include <list>
#include <unordered_map> // hashtable
#include <algorithm>     // std::find
#include <vector>
#include <queue>

using namespace std;
 
// Class for an undirected graph
class Graph
{
    int V;    // No. of vertices
    int **edge_value;
    list<int> *adj; // Pointer to an array containing adjacency lists
    unordered_map<int,int> m; // Stores the value of the node

public:
    Graph(int _V);   // Constructor
    Graph(const Graph &g);        // Copy Constructor
    ~Graph();   // Destructor
    void addEdge(int v, int w, int d);   // To add an edge to graph
    void addValue(int v, int data); // To add value to a node
    void printMatrix();  // Print the Adjcent Matrix
    void printNodeValue();  // Print each nodes value
    void printEdgeValueMatrix(); // Print the Edge value
};
 
Graph::Graph(int _V)
{
    V = _V;
    adj = new list<int> [V];
    
    edge_value = new int* [V];
    for (int i = 0; i < V; ++i)
        edge_value[i] = new int [V];
    
    for (int i = 0; i < V; ++i) 
        for (int j = 0; j < V; ++j)
            edge_value[i][j] = 0;
    
}

Graph::Graph(const Graph &g)
{
    V = g.V;
    adj = new list<int> [V];
    // copy each adjcent list
    for (int i = 0; i < V; ++i)
        adj[i] = g.adj[i];
    // copy the map
    m = g.m;
    // copy the graph value
    edge_value = new int* [V];
    for (int i = 0; i < V; ++i)
        edge_value[i] = new int [V];
    
    for (int i = 0; i < V; ++i) 
        for (int j = 0; j < V; ++j)
            edge_value[i][j] = g.edge_value[i][j];
}
 
Graph::~Graph()
{
    delete [] adj;

    for (int i = 0; i < V; ++i)
        delete [] edge_value[i];
    
    delete [] edge_value;
}

void Graph::addEdge(int v, int w, int d)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Add v to w’s list.
    edge_value[v][w] = d;
    edge_value[w][v] = d;
}

void Graph::addValue(int v, int data)
{
    pair<int,int> p (v,data);
    m.insert (move(p));
}

void Graph::printMatrix()
{
    list<int>::iterator iter;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            iter = find( adj[i].begin(), adj[i].end(),j);
            if (iter != adj[i].end())
                cout << "1" << " ";
            else
                cout << "0" << " ";
        }
        cout << endl;
    } 
}

void Graph::printNodeValue()
{
    for (int i = 0; i < V; ++i)
        cout << m.find(i)->second << " ";
    cout << endl;
}

void Graph::printEdgeValueMatrix()
{
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) 
            cout << edge_value[i][j] << " ";
        cout << endl;
    }
}

// The leetcode implementation of Graph copy
struct Node {
    vector <Node*> neighbors;
};

// This method is very like the method in the binary search
Node *clone(Node *graph)
{
    if (!graph) 
        return NULL;
 
    unordered_map<Node *, Node *> map;
    queue<Node *> q;
    q.push(graph);
 
    Node *graphCopy = new Node();
    // We can also use this notation to insert the
    // Key value pairs
    map[graph] = graphCopy;
 
    while (!q.empty()) {
        Node *node = q.front();
        q.pop();
        int n = node->neighbors.size();
        for (int i = 0; i < n; i++) {
            Node *neighbor = node->neighbors[i];
            // no copy exists
            if (map.find(neighbor) == map.end()) {
                Node *p = new Node();
                map[node]->neighbors.push_back(p);
                map[neighbor] = p;
                q.push(neighbor);
            } else { 
                // a copy already exists
                map[node]->neighbors.push_back(map[neighbor]);
            }
        }
    }
 
    return graphCopy;
}

// Driver program to test above functions
int main()
{
    Graph *g1 = new Graph(5);
    g1->addEdge(1, 0, 1);
    g1->addEdge(0, 2, 2);
    g1->addEdge(0, 3, 3);
    g1->addEdge(3, 4, 4);
    g1->addValue(0,0);
    g1->addValue(1,10);
    g1->addValue(2,20);
    g1->addValue(3,300);
    g1->addValue(4,4);
    cout << "Graph 1 Matrix" << endl;
    g1->printMatrix();
    cout << "Graph 1 Node Value array" << endl;
    g1->printNodeValue();
    cout << "Graph 1 edge Value Matrix" << endl;
    g1->printEdgeValueMatrix();


    Graph g2(*g1);
    delete g1;
    cout << endl << "Graph 2 Matrix" << endl;
    g2.printMatrix();
    cout << "Graph 2 Node Value array" << endl;
    g2.printNodeValue();   
    cout << "Graph 2 edge Value Matrix" << endl;
    g2.printEdgeValueMatrix();

    return 0;
}