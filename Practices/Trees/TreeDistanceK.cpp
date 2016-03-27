//
//  TreeDistanceKcpp
//  
//  Modified by 罗铮 on 03/26/14.
//  http://www.geeksforgeeks.org/print-nodes-at-k-distance-from-root/
//  http://www.geeksforgeeks.org/print-nodes-distance-k-given-node-binary-tree/
//  http://www.geeksforgeeks.org/print-nodes-distance-k-leaf-node/
//  http://www.geeksforgeeks.org/diameter-of-a-binary-tree/

#include "TreeCommon.h"
#include <iostream>
#include <algorithm>

#define MAX_HEIGHT 10000

using namespace std;

/* Recursive function to print all the nodes at distance k in the
   tree (or subtree) rooted with given root. */
void printkdistanceNodeDown(node *root, int k)
{
    // Base Case
    if (root == NULL || k < 0)  return;
 
    // If we reach a k distant node, print it
    if (k == 0)
    {
        cout << root->value << endl;
        return;
    }
 
    // Recur for left and right subtrees
    printkdistanceNodeDown(root->left, k-1);
    printkdistanceNodeDown(root->right, k-1);
}
 
// Prints all nodes at distance k from a given target node.
// The k distant nodes may be upward or downward.  This function
// Returns distance of root from target node, it returns -1 if target
// node is not present in tree rooted with root.
int printkdistanceNode(node* root, node* target , int k)
{
    // Base Case 1: If tree is empty, return -1
    if (root == NULL) return -1;
 
    // If target is same as root.  Use the downward function
    // to print all nodes at distance k in subtree rooted with
    // target or root
    if (root == target)
    {
        printkdistanceNodeDown(root, k);
        return 0;
    }
 
    // Recur for left subtree
    int dl = printkdistanceNode(root->left, target, k);
 
    // Check if target node was found in left subtree
    if (dl != -1)
    {
         // If root is at distance k from target, print root
         // Note that dl is Distance of root's left child from target
         if (dl + 1 == k)
            cout << root->value << endl;
 
         // Else go to right subtree and print all k-dl-2 distant nodes
         // Note that the right child is 2 edges away from left child
         else
            printkdistanceNodeDown(root->right, k-dl-2);
 
         // Add 1 to the distance and return value for parent calls
         return 1 + dl;
    }
 
    // MIRROR OF ABOVE CODE FOR RIGHT SUBTREE
    // Note that we reach here only when node was not found in left subtree
    int dr = printkdistanceNode(root->right, target, k);
    if (dr != -1)
    {
         if (dr + 1 == k)
            cout << root->value << endl;
         else
            printkdistanceNodeDown(root->left, k-dr-2);
         return 1 + dr;
    }
 
    // If target was neither present in left nor in right subtree
    return -1;
}
 
/* This function prints all nodes that are distance k from a leaf node
   path[] --> Store ancestors of a node
   visited[] --> Stores true if a node is printed as output.  A node may be k
                 distance away from many leaves, we want to print it once */
void kDistantFromLeafUtil(node* node, int path[], bool visited[],
                          int pathLen, int k)
{
    // Base case
    if (node==NULL) return;
 
    /* append this Node to the path array */
    path[pathLen] = node->value;
    visited[pathLen] = false;
    pathLen++;
 
    /* it's a leaf, so print the ancestor at distance k only
       if the ancestor is not already printed  */
    if (node->left == NULL && node->right == NULL &&
        pathLen-k-1 >= 0 && visited[pathLen-k-1] == false)
    {
        cout << path[pathLen-k-1] << " ";
        visited[pathLen-k-1] = true;
        return;
    }
 
    /* If not leaf node, recur for left and right subtrees */
    kDistantFromLeafUtil(node->left, path, visited, pathLen, k);
    kDistantFromLeafUtil(node->right, path, visited, pathLen, k);
}
 
/* Given a binary tree and a nuber k, print all nodes that are k
   distant from a leaf*/
void printKDistantfromLeaf(node* node, int k)
{
    int path[MAX_HEIGHT];
    bool visited[MAX_HEIGHT] = {false};
    kDistantFromLeafUtil(node, path, visited, 0, k);
}

/*  The function Compute the "height" of a tree. Height is the
    number f nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(struct node* node)
{
    /* base case tree is empty */
    if(node == NULL)
        return 0;
    
    /* If tree is not empty then height = 1 + max of left
     height and right heights */
    return 1 + max(height(node->left), height(node->right));
}

/* Function to get diameter of a binary tree */
int diameter(struct node * tree)
{
    /* base case where tree is empty */
    if (tree == 0)
        return 0;
    
    /* get the height of left and right sub-trees */
    int lheight = height(tree->left);
    int rheight = height(tree->right);
    
    /* get the diameter of left and right sub-trees */
    int ldiameter = diameter(tree->left);
    int rdiameter = diameter(tree->right);
    
    /* Return max of following three
     1) Diameter of left subtree
     2) Diameter of right subtree
     3) Height of left subtree + height of right subtree + 1 */
    return max(lheight + rheight + 1, max(ldiameter, rdiameter));
}

/* The second parameter is to store the height of tree.
   Initially, we need to pass a pointer to a location with value
   as 0. So, function should be used as follows:
   
   int height = 0;
   struct node *root = SomeFunctionToMakeTree();
   int diameter = diameterOpt(root, &height); 
*/
int diameterOpt(struct node *root, int* height)
{
    /* lh --> Height of left subtree
     rh --> Height of right subtree */
    int lh = 0, rh = 0;
    
    /* ldiameter  --> diameter of left subtree
     rdiameter  --> Diameter of right subtree */
    int ldiameter = 0, rdiameter = 0;
    
    if(root == NULL)
    {
        *height = 0;
        return 0; /* diameter is also 0 */
    }
    
    /* Get the heights of left and right subtrees in lh and rh
     And store the returned values in ldiameter and ldiameter */
    ldiameter = diameterOpt(root->left, &lh);
    rdiameter = diameterOpt(root->right, &rh);
    
    /* Height of current node is max of heights of left and
     right subtrees plus 1*/
    *height = max(lh, rh) + 1;
    
    return max(lh + rh + 1, max(ldiameter, rdiameter));
}


/* Driver program to test above functions*/
int main()
{
    node *root = NULL;
    node *root2 = NULL;

    create_binary_tree3(root);
    create_binary_tree4(root2);
    node * target = root->left->right;

    cout << "printkdistanceNode:\n";
    printkdistanceNode(root, target, 2);
    
    // Memorizing Parent approach
    cout << "Nodes at distance 2 are: ";
    printKDistantfromLeaf(root2, 2);
    cout << endl;
    
    cout << "Diameter of the given binary tree is " 
         << diameter(root) << endl;
    
    int height = 0;
    int diameter = diameterOpt(root, &height);
    cout << "Diameter of the given binary tree is " 
         << diameter << endl;

    return 0;
}