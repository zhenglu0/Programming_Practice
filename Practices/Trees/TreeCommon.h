//
//  TreeConstruction.h
//  
//  Created  by 罗铮 on 10/30/12.
//  Modified by 罗铮 on 04/01/14.
//  Copyright (c) 2012-2014 罗铮. All rights reserved.

#ifndef TreeCommon_H
#define TreeCommon_H

#include <iostream>

struct node {
    int value;
    struct node *left;
    struct node *right;
    node():left(0),right(0){}
    node(int v):value(v),left(0),right(0){}
};

class bstree {
public:
    bstree();
    ~bstree();
    void insert(int key);
    node *search(int key);
    void destroy_tree();
    void pre_oder_traversal();
    void in_oder_traversal();
    void post_oder_traversal();
    // This method can only be used in the BST
    int find_lowest_common_ancestor(int value1, int value2);
    int times;

private:
    void destroy_tree(node *leaf);
    void insert(int key, node *leaf);
    node *search(int key, node *leaf);
    void pre_oder_traversal(node *leaf);
    void in_oder_traversal(node *leaf);
    void post_oder_traversal(node *leaf);
    node *root;
};

// Functions
void InsertBST(node* &root, node* node);
node* SearchNode(node* root, int value);
int maxValue(node *root);
int minValue(node *root);
void CreateBST1(node* &root);
void CreateBST2(node* &root);
void CreateBST3(node* &root);
void CreateBST4(node* &root);
void CreateBST5(node* &root);
int create_binary_search_tree(node **root);
int create_binary_search_tree2(node **root);
void create_binary_search_tree3(node* &root);
void create_binary_tree(node* &root);
void create_binary_tree2(node* &root);
void create_binary_tree3(node* &root);
void create_binary_tree4(node* &root);
void create_binary_tree5(node* &root);

#endif
