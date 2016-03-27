//
//  IntervalTree.cpp
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
struct node
{
    struct node *left; // left child
    struct node *right; // right child
    struct node *p; // parent
    node_color color; // the color of the node
    int max; // the max between subtree max and high
    int low; // the key of the node
    int high;
};


// declare global varible
node *nil = new node;


// 0. Find Max among tree value
//
int FindMax(int a ,int b, int c)
{
    int max = 0;
    max = (a>b? a:b);
    max = (max>c? max:c);
    return max;
}


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
		cout << "[" << currentNode->low << "," 
             << currentNode->high << "]" << currentNode->max 
             << "(" << (currentNode->color == RED? "R":"B") << ") ";
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
    while (x != nil && x->low != k)
    {
        if (k < x->low)
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
void IT_Transplant(node* &root, node* &u, node* &v)
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
    y->max = x->max;
    x->max = FindMax(x->max, x->left->max, x->right->max);
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
    x->max = y->max;
    y->max = FindMax(y->max, y->left->max, y->right->max);
}


// 7. IT_Insert_Fixup
//
void IT_Insert_Fixup(node* &root, node *z)
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


// 8. Max_Fixup
void Max_Fixup(node* &root, node *z)
{
    while (z->p != nil && z->max > z->p->max )
    {
        z->p->max = (z->max > z->p->max ? z->max:z->p->max);
        z = z->p;
    }
}


//
// 9. Insertion a node to the tree
void IT_Insert(node* &root, node *z)
{
    node *y = nil;
    node *x = root;
    while (x != nil)
    {
        y = x;
        if (z->low < x->low)
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
    else if (z->low < y->low)
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
    z->max = z->high;
    IT_Insert_Fixup(root,z);
    Max_Fixup(root, z);
    
}


// 10. Manually create a Binary Search Tree
//
void Create_IT_tree(node* &root)
{
    node *node1 = new node();
    node1->low = 16;
    node1->high = 21;
    IT_Insert(root, node1);
    
    node *node2 = new node();
    node2->low = 8;
    node2->high = 9;
    IT_Insert(root, node2);
    node *node3 = new node();
    node3->low = 25;
    node3->high = 30;
    IT_Insert(root, node3);
    
    node *node4 = new node();
    node4->low = 5;
    node4->high = 8;
    IT_Insert(root, node4);
    node *node5 = new node();
    node5->low = 15;
    node5->high = 23;
    IT_Insert(root, node5);
    node *node6 = new node();
    node6->low = 17;
    node6->high = 19;
    IT_Insert(root, node6);
    node *node7 = new node();
    node7->low = 26;
    node7->high = 26;
    IT_Insert(root, node7);
    
    node *node8 = new node();
    node8->low = 0;
    node8->high = 3;
    IT_Insert(root, node8);
    node *node9 = new node();
    node9->low = 6;
    node9->high = 10;
    IT_Insert(root, node9);
    node *node10 = new node();
    node10->low = 19;
    node10->high = 20;
    IT_Insert(root, node10);
    
}


// 11. Interval_Search
//
node* Interveral_Search(node *root, node *i)
{
    node *x = root;
    while (x != nil && (i->low >= x->high || i->high <= x->low))
    {
        if (x->left != nil && x->left->max >= i->low)
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



// Program entrance
//
int main(int argc, char* argv[])
{
    // Intinalize global varible
    nil->color = BLACK;
    // Create the binary search tree
    node *root = nil;
    Create_IT_tree(root);
    LevelOrderTraversal(root);

    cout << endl << "Test the Iterval Search" << endl;
    
    node *n1 = new node();
    n1->low = 22;
    n1->high = 25;
    node *f1 = Interveral_Search(root, n1);
    if (f1 != nil)
    {
        cout << "[" << f1->low << "," << f1->high << "]" 
             << f1->max << "(" << (f1->color == RED? "R":"B") 
             << ") " << endl;
    }
    else
    {
        cout << "[" << n1->low << "," << n1->high << "]" 
             << " is not found";
    }
    
    node *n2 = new node();
    n2->low = 11;
    n2->high = 14;
    node *f2 = Interveral_Search(root, n2);
    if (f2 != nil)
    {
        cout << "[" << f2->low << "," << f2->high << "]" 
             << f2->max << "(" << (f2->color == RED? "R":"B") 
             << ") " << endl;
    }
    else
    {
        cout << "[" << n2->low << "," << n2->high << "]" 
             << " is not found";
    }
    
    return 0;
}







