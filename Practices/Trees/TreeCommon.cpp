//
//  TreeConstruction.cpp
//  
//  Created  by 罗铮 on 10/30/12.
//  Modified by 罗铮 on 04/01/14.
//  Copyright (c) 2012-2014 罗铮. All rights reserved.

#include "TreeCommon.h"
#include <iostream>

using namespace std;

bstree::bstree()
{
    times = 0;
    root = NULL;
}

bstree::~bstree()
{
    destroy_tree();
}

void bstree::destroy_tree(node *leaf)
{
    if(leaf!=NULL)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void bstree::insert(int key, node *leaf)
{
    if(key < leaf->value)
    {
        if(leaf->left != NULL)
            insert(key, leaf->left);

        else
        {
            leaf->left = new node();
            leaf->left->value=key;  
        }
    }
    else if(key >= leaf->value)
    {
        if(leaf->right != NULL)
            insert(key, leaf->right);

        else
        {
            leaf->right = new node();
            leaf->right->value=key;
        }
    }
}

node *bstree::search(int key, node *leaf)
{
    ++times;
    if(leaf != NULL)
    {
        if(key == leaf->value)
            return leaf;
        
        if(key < leaf->value)
            return search(key, leaf->left);
        
        else
            return search(key, leaf->right);
    }
    else
        return NULL;
}

void bstree::insert(int key)
{
    if(root!=NULL)
        insert(key, root);

    else
    {
        root = new node();
        root->value = key;
        root->left = NULL;
        root->right = NULL;
    }
}

node *bstree::search(int key)
{
    return search(key, root);
}

void bstree::destroy_tree()
{
    destroy_tree(root);
}

void bstree::pre_oder_traversal()
{
    if(!root)
        return;

    cout << root->value << " ";
    pre_oder_traversal(root->left);
    pre_oder_traversal(root->right);
}

void bstree::in_oder_traversal()
{
    if(!root)
        return;

    in_oder_traversal(root->left);
    cout << root->value << " ";
    in_oder_traversal(root->right);
}

void bstree::post_oder_traversal()
{
    if(!root)
        return;

    post_oder_traversal(root->left);
    post_oder_traversal(root->right);
    cout << root->value << " ";
}

void bstree::pre_oder_traversal(node *leaf)
{
    if(!leaf)
        return;
    
    cout << leaf->value << " ";
    pre_oder_traversal(leaf->left);
    pre_oder_traversal(leaf->right);
}

void bstree::in_oder_traversal(node *leaf)
{
    if(!leaf)
        return;
    
    in_oder_traversal(leaf->left);
    cout << leaf->value << " ";
    in_oder_traversal(leaf->right);
}

void bstree::post_oder_traversal(node *leaf)
{
    if(!leaf)
        return;
    
    post_oder_traversal(leaf->left);
    cout << leaf->value << " ";
    post_oder_traversal(leaf->right);
}

int bstree::find_lowest_common_ancestor(int value1, int value2)
{
    node *curNode = root;
    while(1)
    {
        if(curNode->value > value1 && 
           curNode->value > value2)
            curNode = curNode->left;
        else if(curNode->value < value1 && 
                curNode->value < value2)
            curNode = curNode->right;
        else
            return curNode->value;
    }
}

// Functions
void InsertBST(node* &root, node* node)
{
    if (root == NULL)
        root = node;
    else
    {
        if (root->value > node->value)
            InsertBST(root->left, node);
        else
            InsertBST(root->right, node);
    }
}

node* SearchNode(node* root, int _value)
{
    if (root && root->value == _value)
        return root;
    
    node *found = NULL;
    
    if (root && root->left)
        found = SearchNode(root->left,_value);
    
    if (!found && root && root->right)
        found = SearchNode(root->right, _value);
    
    return found;
}

int maxValue(node *root)
{
    node *currentNode = root;
    node *parent = NULL;
    while (currentNode)
    {
        parent = currentNode;
        currentNode = currentNode->right;
    }
    return parent->value;
}

int minValue(node *root)
{
    node *currentNode = root;
    node *parent = NULL;
    while (currentNode)
    {
        parent = currentNode;
        currentNode = currentNode->left;
    }
    return parent->value;
}

void CreateBST1(node* &root)
{
    node* node1 = new node();
    node1->value = 10;
    node* node2 = new node();
    node2->value = 5;
    node* node3 = new node();
    node3->value = 15;
    node* node4 = new node();
    node4->value = 3;
    node* node5 = new node();
    node5->value = 7;
    
    InsertBST(root, node1);
    InsertBST(root, node2);
    InsertBST(root, node3);
    InsertBST(root, node4);
    InsertBST(root, node5);
}


void CreateBST2(node* &root)
{
    node* node1 = new node();
    node1->value = 10;
    node* node2 = new node();
    node2->value = 5;
    node* node3 = new node();
    node3->value = 15;
    node* node4 = new node();
    node4->value = 3;
    node* node5 = new node();
    node5->value = 7;
    node* node6 = new node();
    node6->value = 1;
    
    InsertBST(root, node1);
    InsertBST(root, node2);
    InsertBST(root, node3);
    InsertBST(root, node4);
    InsertBST(root, node5);
    InsertBST(root, node6);
}


void CreateBST3(node* &root)
{
    node* node1 = new node();
    node1->value = 5;
    node* node2 = new node();
    node2->value = 3;
    node* node3 = new node();
    node3->value = 7;
    
    InsertBST(root, node1);
    InsertBST(root, node2);
    InsertBST(root, node3);
}


void CreateBST4(node* &root)
{
    node* node1 = new node();
    node1->value = 10;
    node* node2 = new node();
    node2->value = 5;
    node* node3 = new node();
    node3->value = 12;
    node* node4 = new node();
    node4->value = 4;
    node* node5 = new node();
    node5->value = 7;
    
    InsertBST(root, node1);
    InsertBST(root, node2);
    InsertBST(root, node3);
    InsertBST(root, node4);
    InsertBST(root, node5);
}


void CreateBST5(node* &root)
{
    node* node1 = new node();
    node1->value = 10;
    node* node2 = new node();
    node2->value = 5;
    node* node3 = new node();
    node3->value = 15;
    node* node4 = new node();
    node4->value = 3;
    node* node5 = new node();
    node5->value = 7;
    node* node6 = new node();
    node6->value = 12;
    node* node7 = new node();
    node7->value = 20;
    node* node8 = new node();
    node8->value = 1;
    node* node9= new node();
    node9->value = 4;
    node* node10 = new node();
    node10->value = 18;
    node* node11= new node();
    node11->value = 25;
    node* node12= new node();
    node12->value = 2;
    node* node13= new node();
    node13->value = 24;
    node* node14= new node();
    node14->value = 30;
    
    InsertBST(root, node1);
    InsertBST(root, node2);
    InsertBST(root, node3);
    InsertBST(root, node4);
    InsertBST(root, node5);
    InsertBST(root, node6);
    InsertBST(root, node7);
    InsertBST(root, node8);
    InsertBST(root, node9);
    InsertBST(root, node10);
    InsertBST(root, node11);
    InsertBST(root, node12);
    InsertBST(root, node13);
    InsertBST(root, node14);
}

int create_binary_search_tree(node **root)
{
    // first level node
    *root = new node();
    if(!root)
        return -1;

    (*root)->value = 100;

    // second level node
    node *child1 = new node();
    if(!child1)
        return -1;
    
    child1->value = 50;
    node *child2 = new node();
    if(!child2)
        return -1;
    
    child2->value = 150;
    (*root)->left = child1;
    (*root)->right = child2;

    // third level node
    // left subtree
    node *child1_1 = new node();
    if(!child1_1)
        return -1;
    
    child1_1->value = 25;
    node *child1_2 = new node();
    if(!child1_2)
        return -1;
    
    child1_2->value = 75;
    child1->left = child1_1;
    child1->right = child1_2;
    // right subtree
    node *child2_1 = new node();
    if(!child2_1)
        return -1;
    
    child2_1->value = 125;
    node *child2_2 = new node();
    if(!child2_2)
        return -1;
    
    child2_2->value = 175;
    child2->left = child2_1;
    child2->right = child2_2;

    // forth level node
    node *child3_1 = new node();
    if(!child3_1)
        return -1;
    
    child3_1->value = 110;
    child2_1->left = child3_1;

    return 0;
}

int create_binary_search_tree2(node **root)
{
    // first level node
    *root = new node();
    if(!root)
        return -1;

    (*root)->value = 5;

    // second level node
    node *child1 = new node();
    if(!child1)
        return -1;

    child1->value = 3;
    node *child2 = new node();
    if(!child2)
        return -1;
    
    child2->value = 10;
    (*root)->left = child1;
    (*root)->right = child2;

    // third level node
    // left subtree
    node *child1_1 = new node();
    if(!child1_1)
        return -1;
    
    child1_1->value = 1;
    node *child1_2 = new node();
    if(!child1_2)
        return -1;
    
    child1_2->value = 4;
    child1->left = child1_1;
    child1->right = child1_2;
    // right subtree
    node *child2_1 = new node();
    if(!child2_1)
        return -1;
    
    child2_1->value = 6;
    node *child2_2 = new node();
    if(!child2_2)
        return -1;
    
    child2_2->value = 12;
    child2->left = child2_1;
    child2->right = child2_2;

    return 0;
}

void create_binary_tree(node* &root)
{
    root              = new node(4);
    root->left        = new node(2);
    root->right       = new node(5);
    root->left->left  = new node(1);
    root->left->right = new node(3);
}

void create_binary_tree2(node* &root)
{
    root              = new node(3);
    root->left        = new node(2);
    root->right       = new node(5);
    root->left->left  = new node(1);
    root->left->right = new node(4);
}

void create_binary_tree3(node* &root)
{
    root                     = new node(20);
    root->left               = new node(8);
    root->right              = new node(22);
    root->left->left         = new node(4);
    root->left->right        = new node(12);
    root->left->right->left  = new node(10);
    root->left->right->right = new node(14);
}

void create_binary_tree4(node* &root)
{
    root                     = new node(1);
    root->left               = new node(2);
    root->right              = new node(3);
    root->left->left         = new node(4);
    root->left->right        = new node(5);
    root->right->left        = new node(6);
    root->right->right       = new node(7);
    root->right->left->right = new node(8);
}

void create_binary_tree5(node* &root)
{
    root               = new node(30);
    root->left         = new node(10);
    root->right        = new node(20);
    root->left->left   = new node(50);
    root->right->left  = new node(45);
    root->right->right = new node(35); 
}

void create_binary_search_tree3(node* &root)
{
    root                      = new node(3);
    root->left                = new node(1);
    root->right               = new node(4);
    root->left->left          = new node(1);
    root->right->right        = new node(5);
    root->right->right->left  = new node(5);
    root->right->right->right = new node(5);
}

