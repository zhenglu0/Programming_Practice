//
//  TreeHasSubtree.cpp
//  
//  Created  by 罗铮 on 10/30/12.
//  Modified by 罗铮 on 04/01/14.
//  Copyright (c) 2012-2014 罗铮. All rights reserved.
//  http://zhedahht.blog.163.com/blog/static/25411174201011445550396/

#include "TreeCommon.h"
#include <iostream>
#include <string>

using namespace std;

bool hasTheSameTree(node *r1, node *r2)
{
    if (r1 == NULL && r2 == NULL)
        return true;
    
    if (r1 == NULL || r2 == NULL)
        return false;
    
    if (r1->value != r2->value)
        return false;
    
    return hasTheSameTree(r1->left, r2->left) && 
           hasTheSameTree(r1->right, r2->right);
}

bool T1HasAllNodesOfT2(node* pTreeHead1, 
                              node* pTreeHead2)
{
    if(pTreeHead2 == NULL)
        return true;
    
    if(pTreeHead1 == NULL && pTreeHead2 != NULL)
        return false;
    
    if(pTreeHead1->value != pTreeHead2->value)
        return false;
    
    return T1HasAllNodesOfT2(pTreeHead1->left, 
                             pTreeHead2->left) && 
           T1HasAllNodesOfT2(pTreeHead1->right, 
                             pTreeHead2->right);
}

bool HasSubtree(node* pTreeHead1, node* pTreeHead2)
{
    bool result = false;
    
    if(pTreeHead1->value == pTreeHead2->value)
        result = T1HasAllNodesOfT2(pTreeHead1, pTreeHead2);
    
    if(!result && pTreeHead1->left != NULL)
        result = HasSubtree(pTreeHead1->left, pTreeHead2);
    
    if(!result && pTreeHead1->right != NULL)
        result = HasSubtree(pTreeHead1->right, pTreeHead2);
    
    return result;
}

void PreOrderToString(string &s, node *r)
{
    if (r == NULL)
        return;

    s += to_string(r->value) + " ";
    PreOrderToString(s, r->left);
    PreOrderToString(s, r->right);
}

void InOrderToString(string &s, node *r)
{
    if (r == NULL)
        return;

    InOrderToString(s, r->left);
    s += to_string(r->value) + " ";
    InOrderToString(s, r->right);
}

bool HasSubtreeByString(node* r1, node* r2)
{
    string preOrderStr1, preOrderStr2;
    string inOrderStr1, inOrderStr2;

    PreOrderToString(preOrderStr1, r1);
    PreOrderToString(preOrderStr2, r2);

    InOrderToString(inOrderStr1, r1);
    InOrderToString(inOrderStr2, r2);
    
    cout << preOrderStr1 << endl 
         << preOrderStr2 << endl
         << inOrderStr1 << endl
         << inOrderStr2 << endl << endl;

    if (preOrderStr1.find(preOrderStr2) != string::npos &&
        inOrderStr1.find(inOrderStr2)   != string::npos)
        return true;
    else
        return false;
}


// Prgram entrance
int main(int argc, const char * argv[])
{
    node *root1 = NULL;
    node *root2 = NULL;
    node *root3 = NULL;
    
    CreateBST1(root1);
    CreateBST2(root2);
    CreateBST3(root3);
    
    // Calculate whether the same tree
    cout << "Tree1 and Tree2 the same ? " 
         << boolalpha << hasTheSameTree(root1, root2) << endl << endl;
    
    // Method 1 
    // Calculate the sub tree
    cout << "Tree1 has the subtree of Tree2 ? " 
         << boolalpha << HasSubtree(root1, root2)<< endl
         << "Tree2 has the subtree of Tree1 ? " 
         << boolalpha << HasSubtree(root2, root1)<< endl
         << "Tree2 has the subtree of Tree3 ? " 
         << boolalpha << HasSubtree(root2, root3)<< endl
         << "Tree1 has the subtree of Tree3 ? " 
         << boolalpha << HasSubtree(root1, root3)<< endl << endl;

    // Waring !!!!
    // Method 2 Does NOT Work !!!! 
    // Calculate the sub tree
    cout << "Tree1 has the subtree of Tree2 ? " 
         << boolalpha << HasSubtreeByString(root1, root2)<< endl
         << "Tree2 has the subtree of Tree1 ? " 
         << boolalpha << HasSubtreeByString(root2, root1)<< endl
         << "Tree2 has the subtree of Tree3 ? " 
         << boolalpha << HasSubtreeByString(root2, root3)<< endl
         << "Tree1 has the subtree of Tree3 ? " 
         << boolalpha << HasSubtreeByString(root1, root3)<< endl;

    return 0;
}


