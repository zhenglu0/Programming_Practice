//
//  TreeLevelDepth.cpp
//  
//  Created  by 罗铮 on 10/30/12.
//  Modified by 罗铮 on 04/01/14.
//  Copyright (c) 2012-2014 罗铮. All rights reserved.
// 
//  http://www.geeksforgeeks.org/
//  a-program-to-check-if-a-binary-tree-is-bst-or-not/
// 
//  http://www.geeksforgeeks.org/
//  check-given-binary-tree-follows-height-property-red-black-tree/

#include "TreeCommon.h"
#include <climits>
#include <limits>
#include <iostream>

using namespace std;

int TheMaxLevelOfTree(node *root)
{
    if (root == NULL) 
        return 0;

    int leftSubTree = TheMaxLevelOfTree(root->left) + 1;
    int rightSubTree = TheMaxLevelOfTree(root->right) + 1;

    return (leftSubTree > rightSubTree) ? leftSubTree : rightSubTree;
        
}

int TheMinLevelOfTree(node *root)
{
    if (root == NULL) 
        return 0;

    int leftSubTree = TheMinLevelOfTree(root->left) + 1;
    int rightSubTree = TheMinLevelOfTree(root->right) + 1;

    return (leftSubTree < rightSubTree) ? leftSubTree : rightSubTree;
    
}

// TreeDepth is the same as the TheMaxLevelOfTree
int TreeDepth(node *pnode)
{
    // the depth of a empty tree is 0
    if(!pnode) 
        return 0;
    
    // the depth of left sub-tree
    int nLeft = TreeDepth(pnode->left);
    // the depth of right sub-tree
    int nRight = TreeDepth(pnode->right);
    
    // depth is the binary tree
    return (nLeft > nRight) ? nLeft + 1 : nRight + 1;
}

bool IsBalanced(node* pRoot)
{
    if(pRoot == NULL)
        return true;
    
    int left = TreeDepth(pRoot->left);
    int right = TreeDepth(pRoot->right);
    
    int diff = left - right;
    if(diff > 1 || diff < -1)
        return false;
    
    return ( IsBalanced(pRoot->left) && 
             IsBalanced(pRoot->right) );
}

// This function will traverse the tree
// for Only One time, so it is a constant factor
// time faster than the TreeDepth()
void DepthOfTree(node *root, int &max, int &min)
{
    if (!root)
    {
        max = min = 0;
        return;
    }
    int max1 = 0, min1 = 0;
    int max2 = 0, min2 = 0;

    DepthOfTree(root->left, max1, min1);
    DepthOfTree(root->right, max2, min2);

    max = (max1 > max2) ? max1 + 1 : max2 + 1;
    min = (min1 < min2) ? min1 + 1 : min2 + 1;
}

bool TreeBalanced(int max, int min)
{
    return (max - min <= 1) ? true : false;
}

/* Returns true if the given tree is a BST and its
 values are >= min and <= max. */
int isBSTUtil(struct node* node, int min, int max)
{
    
    /* an empty tree is BST */
    if (node == NULL)
        return 1;
    
    /* false if this node violates the min/max constraint */
    if (node->value < min || node->value > max)
        return 0;
    
    /* otherwise check the subtrees recursively,
     tightening the min or max constraint */
    return
    // Allow only distinct values
        isBSTUtil(node->left, min, node->value-1) &&  
        isBSTUtil(node->right, node->value+1, max); 
}

/* Returns true if the given tree is a binary search tree
 (efficient version). */
int isBST1(struct node* node)
{
    return isBSTUtil(node, INT_MIN, INT_MAX);
}

/*
 1) Do In-Order Traversal of the given tree and store the 
    result in a temp array.
 2) Check if the temp array is sorted in ascending order, 
    if it is, then the tree is BST.
 
 Time Complexity: O(n)
 
 We can avoid the use of Auxiliary Array. While doing In-Order traversal, 
 we can keep track of previously visited node. If the value of the currently 
 visited node is less than the previous value, then tree is not BST.
 */
bool isBST2(struct node* root)
{
    static struct node *prev = NULL;
    
    // traverse the tree in inorder fashion and keep track of prev node
    if (root)
    {
        if (!isBST2(root->left))
            return false;
        
        // Allows only distinct valued nodes
        if (prev != NULL && root->value <= prev->value)
            return false;
        
        prev = root;
        
        return isBST2(root->right);
    }
    
    return true;
}

// traverse the tree in inorder fashion and keep track of prev node
bool isBST3(node * root, int &lastVisit)
{
    if (!root)
        return true;
    
    node* currentNode = root;
    bool isBSTFlag = true;
    
    if (currentNode->left)
        isBSTFlag = isBST3(currentNode->left, lastVisit);
    
    // Allows only distinct valued nodes
    if (isBSTFlag && currentNode->value < lastVisit)
        isBSTFlag = false;
    
    lastVisit = currentNode->value;
    
    if (isBSTFlag && currentNode->right)
        isBSTFlag = isBST3(currentNode->right, lastVisit);
    
    return isBSTFlag;
}

/* Returns true if a binary tree is a binary search tree */
int isBST4(struct node* node)
{
    if (node == NULL)
        return true;
    
    /* false if the max of the left is > than us */
    if (node->left!= NULL && maxValue(node->left) > node->value)
        return false;
    
    /* false if the min of the right is <= than us */
    if (node->right!= NULL && minValue(node->right) < node->value)
        return false;
    
    /* false if, recursively, the left or right is not a BST */
    if (!isBST4(node->left) || !isBST4(node->right))
        return false;
    
    /* passing all that, it's a BST */
    return true; 
}

// Returns returns tree if the Binary tree is balanced like a 
// Red-Black tree. This function also sets value in maxh and 
// minh (passed by reference). maxh and minh are set as maximum 
// and minimum heights of root.
void isBalancedAsRBTUtil(node *root, int &maxh, int &minh, bool &flag)
{
    // Base case
    if (root == NULL)
    {
        maxh = minh = 0;
        return;
    }
    // Just for efficiency reason
    if (!flag)
        return;
 
    int lmxh, lmnh; // To store max and min heights of left subtree
    int rmxh, rmnh; // To store max and min heights of right subtree
 
    // Check if left subtree is balanced, also set lmxh and lmnh
    isBalancedAsRBTUtil(root->left, lmxh, lmnh, flag);
 
    // Check if right subtree is balanced, also set rmxh and rmnh
    isBalancedAsRBTUtil(root->right, rmxh, rmnh, flag);
 
    // Set the max and min heights of this node for the parent call
    maxh = max(lmxh, rmxh) + 1;
    minh = min(lmnh, rmnh) + 1;
 
    // See if this node is balanced
    if (maxh > 2 * minh)
    {
        flag = false;  
        return;
    }
}
 
// A wrapper over isBalancedUtil()
bool isBalancedAsRBT(node *root)
{
    int maxh, minh;
    bool flag = true;
    isBalancedAsRBTUtil(root, maxh, minh, flag);
    return flag? true: false;
}

// Most common element in the BST
void mostCommonElement(node *root, node* &prev, 
                      int &counter, int &max, int &result)
{
    if (root == NULL)
        return;

    mostCommonElement(root->left, prev, counter, max, result);

    if (prev != NULL && 
        prev->value == root->value) {
        counter++;
        if (counter > max) {
            max = counter;
            result = root->value;
        }
    } else
        counter = 1;

    prev = root;

    mostCommonElement(root->right, prev, counter, max, result);
}


// Prgram entrance
int main(int argc, const char * argv[])
{
    node *root1 = NULL;
    node *root2 = NULL;
    node *root3 = NULL;
    node *root4 = NULL;
    node *root5 = NULL;
    node *root6 = NULL;

    CreateBST1(root1);
    CreateBST2(root2);
    CreateBST3(root3);
    create_binary_tree(root4);
    create_binary_tree(root5);
    create_binary_search_tree3(root6);

    // Calculate tree level
    cout << "\nMax level of Tree 1 = " 
         << TheMaxLevelOfTree(root1) << endl
         << "Max level of Tree 2 = " 
         << TheMaxLevelOfTree(root2) << endl
         << "Max level of Tree 1 = " 
         << TheMinLevelOfTree(root1) << endl
         << "Max level of Tree 2 = " 
         << TheMinLevelOfTree(root2) << endl;
        
    // Calculate the depth of the tree
    int max1 = 0, min1 = 0;
    int max2 = 0, min2 = 0;
    int max3 = 0 ,min3 = 0;
    
    DepthOfTree(root1, max1, min1);
    DepthOfTree(root2, max2, min2);
    DepthOfTree(root3, max3, min3);
    
    cout << "\nMax level of Tree 1 = " << max1 << endl
         << "Min level of Tree 1 = " << min1 << endl
         << "Tree 1 balanced ? " << boolalpha 
         << TreeBalanced(max1, min1) << endl << endl
    
         << "Max level of Tree 2 = " << max2 << endl
         << "Min level of Tree 2 = " << min2 << endl
         << "Tree 2 balanced ? " << boolalpha 
         << TreeBalanced(max2, min2) << endl << endl

         << "Max level of Tree 3 = " << max3 << endl
         << "Min level of Tree 3 = " << min3 << endl
         << "Tree 3 balanced ? " << boolalpha 
         << TreeBalanced(max3, min3) << endl;
    
    // Test the tree class
    bstree bst;
    bst.insert(10);
    bst.insert(6);
    bst.insert(14);
    bst.insert(5);
    bst.insert(8);
    bst.insert(11);
    bst.insert(18);

    bst.pre_oder_traversal();
    cout << endl;
    bst.in_oder_traversal();
    cout << endl;
    bst.post_oder_traversal();
    cout << endl;

    int com = bst.find_lowest_common_ancestor(4,14);
    cout << "\nThe common ancester is " << com << endl;
    bst.search(14);
    cout << "Times = " << bst.times << endl;

    // test case1
    // 1.
    if (isBST1(root4))
        printf("Is BST \n");
    else
        printf("Not a BST \n");
    
    // 2.
    if (isBST2(root4))
        printf("Is BST \n");
    else
        printf("Not a BST \n");
    
    // 3.
    int lastVist = std::numeric_limits<int>::min();
    if (isBST3(root4,lastVist))
        printf("Is BST \n");
    else
        printf("Not a BST \n");
    
    // 4.
    if (isBST4(root4))
        printf("Is BST \n");
    else
        printf("Not a BST \n");
    
    cout << endl;
    
    // test case 2    
    // 1.
    if (isBST1(root5))
        printf("Is BST \n");
    else
        printf("Not a BST \n");
    
    // 2.
    if (isBST2(root5))
        printf("Is BST \n");
    else
        printf("Not a BST \n");
    
    // 3.
    lastVist = std::numeric_limits<int>::min();
    if (isBST3(root5,lastVist))
        printf("Is BST \n");
    else
        printf("Not a BST \n");
    
    // 4.
    if (isBST4(root5))
        printf("Is BST \n");
    else
        printf("Not a BST \n");

    // If a tree is balanced as red black tree
    if (isBalancedAsRBT(root5))
        cout << "Balanced as Red Black Tree\n";
    else
        cout << "Not Balanced as Red Black Tree\n";
    
    // Most common element in the BST
    node *prev = NULL;
    int counter = 0, max = 0, result = root6->value;

    mostCommonElement(root6, prev, counter, max, result);

    cout << "The most common element is " << result << endl;

    return 0;
}


