//
//  TreeOperation.cpp
//  
//  Created  by 罗铮 on 10/30/12.
//  Modified by 罗铮 on 04/01/14.
//  Copyright (c) 2012-2014 罗铮. All rights reserved.
// 
//  http://zhedahht.blog.163.com/blog/
//  #m=0&t=1&c=fks_081075092084086070092074084070080087080066083082

#include "TreeCommon.h"
#include <stack>
#include <deque>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////
// Find first node whose value equals 6
///////////////////////////////////////////////////////////////////////
node *FindSixNode_iterative(node *root)
{
    node *curNode = root;
    while(curNode)
    {
        if(curNode->value == 6)
            return curNode;
        
        else if(curNode->value < 6)
            curNode = curNode->right;
        
        else if(curNode->value > 6)
            curNode = curNode->left;
    }
    
    return NULL;
}

node *FindSixNode_recursive(node *root)
{
    node *curNode = root;
    while(curNode)
    {
        if(curNode->value == 6)
            return curNode;
        
        else if(curNode->value < 6)
            FindSixNode_recursive(curNode->right);
        
        else if(curNode->value > 6)
            FindSixNode_recursive(curNode->left);
    }
    
    return NULL;
}

///////////////////////////////////////////////////////////////////////
// Mirror a BST (swap the left right child of each node) recursively
// the head of BST in initial call
///////////////////////////////////////////////////////////////////////
void MirrorRecursively(node *pNode)
{
    if(!pNode) 
        return;
    
    // swap the right and left child sub-tree
    node *pTemp = pNode->left;
    pNode->left = pNode->right;
    pNode->right = pTemp;
    
    // mirror left child sub-tree if not null
    if(pNode->left)
        MirrorRecursively(pNode->left);
    
    // mirror right child sub-tree if not null
    if(pNode->right)
        MirrorRecursively(pNode->right);
}

///////////////////////////////////////////////////////////////////////
// Mirror a BST (swap the left right child of each node) Iteratively
// Input: pTreeHead: the head of BST
///////////////////////////////////////////////////////////////////////
void MirrorIteratively(node *pTreeHead)
{
    if(!pTreeHead) return;
    
    stack<node *> stacknode;
    stacknode.push(pTreeHead);
    
    while(stacknode.size())
    {
        node *pNode = stacknode.top();
        stacknode.pop();
        
        // swap the right and left child sub-tree
        node *pTemp = pNode->left;
        pNode->left = pNode->right;
        pNode->right = pTemp;
        
        // push left child sub-tree into stack if not null
        if(pNode->left)
            stacknode.push(pNode->left);
        
        // push right child sub-tree into stack if not null
        if(pNode->right)
            stacknode.push(pNode->right);
    }
}

///////////////////////////////////////////////////////////////////////
// Print a binary tree from top level to bottom level
// Input: pTreeRoot - the root of binary tree
///////////////////////////////////////////////////////////////////////
void PrintFromTopToBottom(node *pTreeRoot)
{
    if(!pTreeRoot)
        return;
    // get a empty queue
    deque<node *> dequenode;
    // insert the root at the end of queue
    dequenode.push_back(pTreeRoot);
    while(dequenode.size())
    {
        // get a node from the head of queue, 
        // the element is still in the queue
        node *pNode = dequenode.front();
        dequenode.pop_front();
        
        // print the node
        cout << pNode->value << " ";
        
        // print its left child sub-tree if it has
        if(pNode->left)
            dequenode.push_back(pNode->left);
        // print its right child sub-tree if it has
        if(pNode->right)
            dequenode.push_back(pNode->right);
    }
}

///////////////////////////////////////////////////////////////////////
// Find paths whose sum equal to expected sum
///////////////////////////////////////////////////////////////////////
void FindPath
(
 node*   pnode,               // a node of binary tree
 int         expectedSum,     // the expected sum
 vector<int>& path,           // a path from root to current node
 int&        currentSum       // the sum of path
 )
{
    if(!pnode)
        return;
    
    currentSum += pnode->value;
    path.push_back(pnode->value);
    
    // if the node is a leaf, and the sum is same as pre-defined,
    // the path is what we want. print the path
    bool isLeaf = (!pnode->left && !pnode->right);
    if(currentSum == expectedSum && isLeaf)
    {
        for(vector<int>::iterator iter = path.begin(); 
            iter != path.end(); ++iter)
            cout << *iter << " ";
        cout << endl;
    }
    
    // if the node is not a leaf, goto its children
    if(pnode->left)
        FindPath(pnode->left, expectedSum, path, currentSum);
    if(pnode->right)
        FindPath(pnode->right, expectedSum, path, currentSum);
    
    // when we finish visiting a node and return to its parent node,
    // we should delete this node from the path and
    // minus the node's value from the current sum
    currentSum -= pnode->value;
    path.pop_back();
}


///////////////////////////////////////////
// Print the Tree in Zigzag order
///////////////////////////////////////////
void PringZigzagly(node *root)
{
    if (!root)
        return;
    
    int now= 1, level = 1, next = 0;
    node *current = NULL;
    vector <node *> v;
    queue  <node *> q;
    
    q.push(root);
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        --now;

        if (level % 2 == 0)
            cout << current->value << " ";
        if (level % 2 == 1)
            v.push_back(current);
        
        if (current->left)
        {
            q.push(current->left);
            ++next;
        }
        if (current->right)
        {
            q.push(current->right);
            ++next;
        }

        if (now == 0)
        {
            if (level % 2 == 1)
            {
                while (!v.empty())
                {
                    cout << v.back()->value << " ";
                    v.pop_back();
                }
            }
            now = next;
            next = 0;
            ++level;
            cout << endl;
        }
    }
}


// Prgram entrance
int main(int argc, const char * argv[])
{
    node *root;
    node **p_root = &root;
    node *root1 = NULL;
    node *root4 = NULL;
    node *root5 = NULL;
    
    CreateBST1(root1);
    CreateBST4(root4);
    CreateBST5(root5);
    create_binary_search_tree2(p_root);
    
    // Find value functions
    node *found_iterative = FindSixNode_iterative(root);
    node *found_recursive = FindSixNode_iterative(root);

    if(!found_iterative)
        cout << "The node not found" << endl;
    
    else
        cout << "The node is found by iterative, value = " 
             << found_iterative->value << endl;

    if(!found_recursive)
        cout << "The node not found" << endl;
    else
        cout << "The node is found by recursive, value = " 
             << found_recursive->value << endl;

    // Reverset the BST
    cout << "Mirror \n";
    MirrorIteratively(root1);
            
    // Print tree in level order
    cout << "In level order \n";
    PrintFromTopToBottom(root1);
    
    // Print the path of the tree
    cout << "Path of the tree \n";
    vector<int> path;
    int currentSum = 0;
    int expectedSum = 22;
    FindPath(root4, expectedSum, path, currentSum);
    
    // Print tree zigzagly
    cout << "Print tree zigzagly \n";
    PringZigzagly(root5);
    
    return 0;
}


