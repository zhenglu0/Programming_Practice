//
//  TopologicalSort.cpp
//  
//  Created by 罗铮 on 2/10/13.
//  Copyright (c) 2013 罗铮. All rights reserved.

#include <iostream>
#include <vector>

using namespace std;

struct node {
    char id;
    vector <node*> adj;
    bool visited;
    node(char init_id):id(init_id),visited(false){};
};

// Do a postorder visit of the graph
void visitNode(node *root, vector<node*> &v)
{
    // base case
    if (root->adj.empty() && !root->visited) {
        v.push_back(root);
        root->visited = true;
        return;
    }
    for (size_t i = 0; i < root->adj.size(); i++) {
        // visit adj list node of root
        visitNode(root->adj[i],v);
    }
    // after finished every node in adj list, we visit root
    if (!root->visited) {
        root->visited = true;
        v.push_back(root);
    }
}

void toplogicalSort(node *root, vector<node*> &tsort)
{
    visitNode(root,tsort);
}

void reverseVector(vector<node*> &v)
{
    int i = 0, j = int(v.size() - 1);
    while (i < j) {
        node* temp = v[i];
        v[i++] = v[j];
        v[j--] = temp;
    }
}

int main(int argc, const char * argv[])
{
    // #1 test case
    // create graph
    node* A = new node('A');
    node* B = new node('B');
    node* C = new node('C');
    node* D = new node('D');
    node* E = new node('E');
    node* F = new node('F');
    
    A->adj.push_back(B);
    A->adj.push_back(C);
    B->adj.push_back(D);
    B->adj.push_back(E);
    C->adj.push_back(E);
    D->adj.push_back(F);
    E->adj.push_back(F);
    
    vector<node*> v1;
    // do the topsort
    toplogicalSort(A, v1);
    reverseVector(v1);
    for (size_t i = 0; i < v1.size(); i++)
        cout << v1[i]->id << " ";

    cout << endl;
    
    // #2 test case
    // create graph
    node* a = new node('a');
    node* b = new node('b');
    node* c = new node('c');
    node* d = new node('d');
    node* e = new node('e');
    node* f = new node('f');
    node* g = new node('g');
    
    a->adj.push_back(b);
    a->adj.push_back(e);
    d->adj.push_back(b);
    d->adj.push_back(c);
    d->adj.push_back(f);
    f->adj.push_back(g);
    e->adj.push_back(d);
    
    vector<node*> v2;
    // do the topsort
    toplogicalSort(a, v2);
    reverseVector(v2);
    
    for (size_t i = 0; i < v2.size(); i++)
        cout << v2[i]->id << " ";

    cout << endl;
    
    return 0;
}

