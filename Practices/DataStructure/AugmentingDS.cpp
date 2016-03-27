//
//  AugmentingDataStructures.cpp
//  
//  Created by 罗铮 on 10/22/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <queue>

using namespace std;

enum node_color
{
    RED = 0,
    BLACK = 1
};

// define a tree node
typedef struct nodeT
{
    struct nodeT *left; // left child
    struct nodeT *right; // right child
    struct nodeT *p; // parent
    int key; // the value of the node
    node_color color; // the color of the node
    int size; // the size of the subtree, including it self
} node;


// declare global varible
node *nil = new node;

// 1. BFS level order search
//
void LevelOrderTraversal(node *x)
{
    int current = 1; // value to store # of current nodes in the queue
    int next = 0; // value to store # of next level nodes in the queue
	queue<node*> q;
	q.push(x);
	while(!q.empty())
	{
		node *currentNode = q.front();
		q.pop();
		cout << currentNode->key << "(" 
             << (currentNode->color == RED? "R":"B") << ")"
        << "(" << currentNode->size << ") ";
		if (currentNode->left != nil)
		{
			q.push(currentNode->left);
            next++;
		}
		if(currentNode->right != nil)
		{
			q.push(currentNode->right);
            next++;
		}
        if (current == 1)
        {
            current = next;
            next = 0;
            cout << endl;
        }
        else
        {
            current--;
        }
	}
}


// 2. Tree Search
//
node* Tree_Search(node *x, int k)
{
    while (x != nil && x->key != k)
    {
        if (k < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return x;

}


// 3. Minimum
//
node* Tree_Minimum(node *x)
{
    while (x->left != nil)
    {
        x = x->left;
    }
    return x;
}


// 4. Transplant the binary search tree
//
void RB_Transplant(node* &root, node* &u, node* &v)
{
    if (u->p == nil)
    {
        root = v;
    }
    else if (u == u->p->left)
    {
        u->p->left = v;
    }
    else
    {
        u->p->right = v;
    }
    if (v != nil)
    {
        v->p = u->p;
    }
}


//
// 5. Left_Rotate for a binary tree
void Left_Rotate(node* &root , node *x)
{
    node *y = x->right;
    x->right = y->left;
    if (y->left != nil)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == nil)
    {
        root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}


//
// 6. Right_Rotate for a binary tree
void Right_Rotate(node* &root , node *y)
{
    node *x = y->left;
    y->left = x->right;
    if (x->right != nil)
    {
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == nil)
    {
        root = x;
    }
    else if (y == y->p->left)
    {
        y->p->left = x;
    }
    else
    {
        y->p->right = x;
    }
    x->right = y;
    y->p = x;
    x->size = y->size;
    y->size = y->left->size + y->right->size + 1;
}


// 7. RB_Insert_Fixup
//
void RB_Insert_Fixup(node* &root, node *z)
{

    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            node *y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;        // case 1
                y->color = BLACK;           // case 1
                z->p->p->color = RED;       // case 1
                z = z->p->p;                // case 1
            }
            else if (z == z->p->right)
            {
                z = z->p;                   // case 2
                Left_Rotate(root, z);       // case 2
            }
            else if (z->p != nil && z->p->p != nil)
            {
                z->p->color = BLACK;        // case 3
                z->p->p->color = RED;       // case 3
                Right_Rotate(root, z->p->p);// case 3
            }
        }
        else
        {
            node *y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;        // case 4
                y->color = BLACK;           // case 4
                z->p->p->color = RED;       // case 4
                z = z->p->p;                // case 4
            }
            else if (z == z->p->left)
            {
                z = z->p;                   // case 5
                Right_Rotate(root, z);      // case 5
            }
            else if (z->p != nil && z->p->p != nil)
            {
                z->p->color = BLACK;        // case 6
                z->p->p->color = RED;       // case 6
                Left_Rotate(root, z->p->p); // case 6
            }
        }

    }
    root->color = BLACK;
}


// 8. Size_Fixup
void Size_Fixup(node* &root, node *z)
{
    while (z->p != nil)
    {
        z->p->size = z->p->size + 1;
        z = z->p;
    }
}


//
// 9. Insertion a node to the tree
void RB_Insert(node* &root, node *z)
{
    node *y = nil;
    node *x = root;
    while (x != nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->p = y;
    if (y == nil)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    z->size = 1;
    RB_Insert_Fixup(root,z);
    Size_Fixup(root, z);

}


// 10. Manually create a Binary Search Tree
//
void Create_RB_tree(node* &root)
{
    node *node1 = new node();
    node1->key = 26;
    RB_Insert(root, node1);

    node *node2 = new node();
    node2->key = 17;
    RB_Insert(root, node2);
    node *node3 = new node();
    node3->key = 41;
    RB_Insert(root, node3);

    node *node4 = new node();
    node4->key = 14;
    RB_Insert(root, node4);
    node *node5 = new node();
    node5->key = 21;
    RB_Insert(root, node5);
    node *node6 = new node();
    node6->key = 30;
    RB_Insert(root, node6);
    node *node7 = new node();
    node7->key = 47;
    RB_Insert(root, node7);

    node *node8 = new node();
    node8->key = 10;
    RB_Insert(root, node8);
    node *node9 = new node();
    node9->key = 16;
    RB_Insert(root, node9);
    node *node10 = new node();
    node10->key = 19;
    RB_Insert(root, node10);
    node *node11 = new node();
    node11->key = 21;
    RB_Insert(root, node11);
    node *node12 = new node();
    node12->key = 28;
    RB_Insert(root, node12);
    node *node13 = new node();
    node13->key = 38;
    RB_Insert(root, node13);

    node *node14 = new node();
    node14->key = 7;
    RB_Insert(root, node14);
    node *node15 = new node();
    node15->key = 12;
    RB_Insert(root, node15);
    node *node16 = new node();
    node16->key = 14;
    RB_Insert(root, node16);
    node *node17 = new node();
    node17->key = 20;
    RB_Insert(root, node17);
    node *node18 = new node();
    node18->key = 35;
    RB_Insert(root, node18);
    node *node19 = new node();
    node19->key = 39;
    RB_Insert(root, node19);

    node *node20 = new node();
    node20->key = 3;
    RB_Insert(root, node20);
}


// 11. Retrieving an element with an given rank
//
node* OS_Select(node *x, int i)
{
    int r = x->left->size + 1;
    if (i == r)
    {
        return x;
    }
    else if(i < r)
    {
        return OS_Select(x->left, i);
    }
    else
    {
        return OS_Select(x->right, i - r);
    }
}


// 12. Determining the rank of an element
//
int OS_Rank(node *root, node *x)
{
    int r = x->left->size + 1;
    node *y = x;
    while (y != root)
    {
        if ( y == y->p->right)
        {
            r = r + y->p->left->size + 1;
        }
        y = y->p;
    }
    return r;
}


// Program entrance
//
int main(int argc, char* argv[])
{
    // Intinalize global varible
    nil->color = BLACK;
    // Create the binary search tree
    node *root = nil;
    Create_RB_tree(root);
    LevelOrderTraversal(root);

    cout << endl <<"Test OS_Select" << endl;
    int k1 = 17;
    node *n1 = OS_Select(root, k1);
    cout << "The element rank " << k1 
         << " is " << n1->key << endl;

    cout << endl <<"Test OS_Rank" << endl;
    int k2 = 38;
    node *n2 = Tree_Search(root, k2);
    int r = OS_Rank(root, n2);
    cout << "The element " << k2 
         << " is ranking " << r;

    return 0;
}





