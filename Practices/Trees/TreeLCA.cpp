//
//  TreeLCA.cpp
//  
//  Created  by 罗铮 on 10/30/12.
//  Modified by 罗铮 on 04/01/14.
//  Copyright (c) 2012-2014 罗铮. All rights reserved.
// 
//  http://zhedahht.blog.163.com/blog/
//  #m=0&t=1&c=fks_081075092084086070092074084070080087080066083082
//  http://leetcode.com/2011/07/
//  lowest-common-ancestor-of-a-binary-tree-part-i.html

#include "TreeCommon.h"
#include <list>
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////
// If the tree with head pHead has a node pnode, return true.
// Otherwise return false.
///////////////////////////////////////////////////////////////
bool Hasnode(node* pHead, node* pnode)
{
    if(pHead == pnode)
        return true;
    
    bool has = false;
    
    if(pHead->left != NULL)
        has = Hasnode(pHead->left, pnode);
    
    if(!has && pHead->right != NULL)
        has = Hasnode(pHead->right, pnode);
    
    return has;
}

//////////////////////////////////////////////////////////////////////
// Find the last parent of pnode1 and pnode2 in a tree with head pHead
//////////////////////////////////////////////////////////////////////
node* LastCommonParent_1(node* pHead, node* pnode1, 
                             node* pnode2)
{
    // check if one of the nodes is NULL
    if(pHead == NULL || pnode1 == NULL || pnode2 == NULL)
        return NULL;
    
    // check whether left child has pnode1 and pnode2
    bool leftHasnode1 = false;
    bool leftHasnode2 = false;
    if(pHead->left != NULL)
    {
        leftHasnode1 = Hasnode(pHead->left, pnode1);
        leftHasnode2 = Hasnode(pHead->left, pnode2);
    }
    // if left child has pnode1 and pnode2, search the left subtree
    if(leftHasnode1 && leftHasnode2)
    {
        if(pHead->left == pnode1 || pHead->left == pnode2)
            return pHead;
        
        return LastCommonParent_1(pHead->left, pnode1, pnode2);
    }
    
    // check whether right child has pnode1 and pnode2
    bool rightHasnode1 = false;
    bool rightHasnode2 = false;
    if(pHead->right != NULL)
    {
        if(!leftHasnode1)
            rightHasnode1 = Hasnode(pHead->right, pnode1);
        if(!leftHasnode2)
            rightHasnode2 = Hasnode(pHead->right, pnode2);
    }
    // if right child has pnode1 and pnode2, search the right subtree
    if(rightHasnode1 && rightHasnode2)
    {
        if(pHead->right == pnode1 || pHead->right == pnode2)
            return pHead;
        
        return LastCommonParent_1(pHead->right, pnode1, pnode2);
    }
    // if one of the pHead's child is in left of its subtree 
    // and one child is in right subtree
    if((leftHasnode1 && rightHasnode2)
       || (leftHasnode2 && rightHasnode1))
        return pHead;
    
    return NULL;
}

//////////////////////////////////////////////////////////////
// Get the path form pHead and pnode in a tree with head pHead
//////////////////////////////////////////////////////////////
bool GetnodePath(node* pHead, node* pnode, 
                 list<node*>& path)
{
    if(pHead == pnode)
        return true;
    
    path.push_back(pHead);
    
    bool found = false;

    if(pHead->left != NULL)
        found = GetnodePath(pHead->left, pnode, path);
    if(!found && pHead->right)
        found = GetnodePath(pHead->right, pnode, path);
    
    if(!found)
        path.pop_back();
    
    return found;
}

/////////////////////////////////////////////////////////
// Get the last common node in two lists: path1 and path2
////////////////////////////////////////////////////////
node* LastCommonnode (const list<node*>& path1, 
                          const list<node*>& path2)
{
    list<node*>::const_iterator iterator1 = path1.begin();
    list<node*>::const_iterator iterator2 = path2.begin();
    
    node* pLast = NULL;
    
    while(iterator1 != path1.end() && iterator2 != path2.end())
    {
        if(*iterator1 == *iterator2)
            pLast = *iterator1;
        
        iterator1++;
        iterator2++;
    }
    
    return pLast;
}

//////////////////////////////////////////////////////////////////////
// Find the last parent of pnode1 and pnode2 in a tree with head pHead
//////////////////////////////////////////////////////////////////////
node* LastCommonParent_2(node* pHead, 
                             node* pnode1, node* pnode2)
{
    if(pHead == NULL || pnode1 == NULL || pnode2 == NULL)
        return NULL;
    
    list<node*> path1;
    GetnodePath(pHead, pnode1, path1);
    
    list<node*> path2;
    GetnodePath(pHead, pnode2, path2);
    
    return LastCommonnode(path1, path2);
}

//////////////////////////////////////////////////////////
// Get the last common node in two lists: path1 and path2
// If the node p1 and p2 is already known in the tree
/////////////////////////////////////////////////////////
int FindLowestCommonAncesstor(node* root, node* node1, 
                        node* node2, node* &lowestCommonAncestor)
{
    if (!root) return 0;
    
    if (root == node1 || root == node2) return 1;
    
    // calculate whether the nodes lays in the left and right part of the tree
    int result = FindLowestCommonAncesstor(root->left, node1, node2,
                                           lowestCommonAncestor) + 
                 FindLowestCommonAncesstor(root->right, node1, node2, 
                                           lowestCommonAncestor);
    
    if (result == 2 && lowestCommonAncestor == NULL) 
            lowestCommonAncestor = root;
    // if the tree is degenerated into a single linked list
    else if(result == 1 && lowestCommonAncestor == NULL)  
            lowestCommonAncestor = root; 
    
    return result;
}

///////////////////////////////////////////////////////////
// Predecessor in binary tree by inorder traversal
///////////////////////////////////////////////////////////
void PredecessorInBinaryTreeByInorderTravesal1(node *root, node *n, 
                                               node* &predecessor)
{
    node *currentnode = root;
    
    if (!predecessor && currentnode->left)
        PredecessorInBinaryTreeByInorderTravesal1(currentnode->left, n, 
                                                  predecessor);
    
    if ((currentnode->left && currentnode->left == n) ||
        (currentnode->right && currentnode->right == n))
        predecessor = currentnode;
    
    if (!predecessor && currentnode->right)
        PredecessorInBinaryTreeByInorderTravesal1(currentnode->right, n, 
                                                  predecessor);
}

node* 
PredecessorInBinaryTreeByInorderTravesal2(node *root, node *n)
{
    node *currentnode = root;
    node *predecessor = NULL;
    
    if (!predecessor && currentnode->left)
        predecessor = 
        PredecessorInBinaryTreeByInorderTravesal2(currentnode->left, n);
    
    if ((currentnode->left && currentnode->left == n) ||
        (currentnode->right && currentnode->right == n))
        predecessor = currentnode;
    
    if (!predecessor && currentnode->right)
        predecessor = 
        PredecessorInBinaryTreeByInorderTravesal2(currentnode->right, n);
    
    return predecessor;
}

///////////////////////////////////////////////////////////
// A Bottom-up Approach (Worst case O(n) ):
// Using a bottom-up approach, we can improve over the top-down a
// pproach by avoiding traversing the same nodes over and over again.

// We traverse from the bottom, and once we reach a node which matches 
// one of the two nodes, we pass it up to its parent. The parent would 
// then test its left and right subtree if each contain one of the two 
// nodes. If yes, then the parent must be the LCA and we pass its parent 
// up to the root. If not, we pass the lower node which contains 
// either one of the two nodes (if the left or right subtree contains 
// either p or q), or NULL (if both the left and right subtree does 
// not contain either p or q) up.
///////////////////////////////////////////////////////////
node *LCA(node *root, node *p, node *q) 
{
    if (!root) 
        return NULL;

    if (root == p || root == q) 
        return root;

    node *L = LCA(root->left, p, q);
    node *R = LCA(root->right, p, q);

    // if p and q are on both sides
    if (L && R) 
        return root;  

    // either one of p,q is on one side 
    // OR p,q is not in L&R subtrees
    return L ? L : R;  
}


// Prgram entrance
int main(int argc, const char * argv[])
{
    node *root1 = NULL;
    node *root5 = NULL;
    CreateBST1(root1);
    CreateBST5(root5);
        
    // Calculate the lowest common ancesstor in the Binary Tree
    node *n1 = SearchNode(root1, 3);
    node *n2 = SearchNode(root1, 7);

    // Method 1
    node *lastCommonParent1 = LastCommonParent_1(root1, n1, n2);
    cout << "Method 1, The last common parent is " 
         << lastCommonParent1->value << endl;

    // Method 2
    node *lastCommonParent2 = LastCommonParent_2(root1, n1, n2);
    cout << "Method 2, The last common parent is " 
         << lastCommonParent2->value << endl;
    
    // Method 3
    node *lastCommonParent3 = NULL;
    FindLowestCommonAncesstor(root1, n1, n2, lastCommonParent3);
    cout << "Method 3, The last common parent is " 
         << lastCommonParent3->value << endl;
    
    // Method 4
    node *lastCommonParent4 = LCA(root1, n1, n2);
    cout << "Method 4, The last common parent is " 
         << lastCommonParent4->value << endl;
    
    // Method 5
    // test PredessorInBinaryTreeByInorderTravesal
    cout << "PredessorInBinaryTree \n";
    node *n = SearchNode(root5, 4);
    node *predecessor1 = NULL;
    PredecessorInBinaryTreeByInorderTravesal1(root5, n, predecessor1);
    cout << "The Predecessor of " << n->value << " is " 
         << predecessor1->value << endl
         << "The Predecessor of " << n->value << " is " 
         << PredecessorInBinaryTreeByInorderTravesal2(root5,n)->value 
         << endl;

    return 0;
}


