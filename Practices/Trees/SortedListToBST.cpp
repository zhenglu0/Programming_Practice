//
//  SortedListToBST.cpp
//  
//  Modified by 罗铮 on 03/13/14.
//  http://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

/* Link list node */
struct LNode
{
    int data;
    struct LNode* next;
};
 
/* A Binary Tree node */
struct TNode
{
    int data;
    struct TNode* left;
    struct TNode* right;
};

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct TNode* newNode(int data)
{
    struct TNode* node = (struct TNode*)
                         malloc(sizeof(struct TNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}

/* The method 1 constructs the tree from root to leaves. 
   Return the size of the array
*/
int* copyListToArray(int &size, LNode *ptr)
{
    int n = 0;
    LNode *head = ptr;
    // Get the size of the list
    while (ptr) {
        ptr = ptr->next;
        n++;
    }

    int *s = new int [n];
    size = n;
    
    n = 0;
    ptr = head;
    // Get the data of the list
    while (ptr) {
        s[n] = ptr->data;
        ptr = ptr->next;
        n++;
    }

    return s;
}

struct TNode* sortedListToBST_topdown(int *s, int l, int r)
{
    if (l > r)
        return NULL;

    int mid = (l + r) / 2;
    TNode *root = newNode(s[mid]);
    root->left  = sortedListToBST_topdown(s, l, mid-1);
    root->right = sortedListToBST_topdown(s, mid+1, r);

    return root;
}
 
/* The method 1 constructs the tree from root to leaves. In this method, 
   we construct from leaves to root. The idea is to insert nodes in BST 
   in the same order as the appear in Linked List, so that the tree can 
   be constructed in O(n) time complexity. We first count the number of
   nodes in the given Linked List. Let the count be n. After counting 
   nodes, we take left n/2 nodes and recursively construct the left 
   subtree. After left subtree is constructed, we allocate memory for 
   root and link the left subtree with root. Finally, we recursively 
   construct the right subtree and link it with root.
   While constructing the BST, we also keep moving the list head pointer 
   to next so that we have the appropriate pointer in each recursive call.
   The main function that constructs balanced BST and returns root of it.
   head_ref -->  Pointer to pointer to head node of linked list
   n  --> No. of nodes in Linked List */

/* A utility function that returns count of nodes in a given 
   Linked List */
int countLNodes(struct LNode *head)
{
    int count = 0;
    struct LNode *temp = head;
    while(temp)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

struct TNode* sortedListToBSTRecur(struct LNode **head_ref, int n)
{
    /* Base Case */
    if (n <= 0)
        return NULL;
 
    /* Recursively construct the left subtree */
    struct TNode *left = sortedListToBSTRecur(head_ref, n/2);
 
    /* Allocate memory for root, and link the above constructed left 
       subtree with root */
    struct TNode *root = newNode((*head_ref)->data);
    root->left = left;
 
    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref)->next;
 
    /* Recursively construct the right subtree and link it with root 
      The number of nodes in right subtree  is total nodes - nodes in 
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = sortedListToBSTRecur(head_ref, n-n/2-1);
 
    return root;
}

/* This function counts the number of nodes in Linked List and then calls
   sortedListToBSTRecur() to construct BST */
struct TNode* sortedListToBST(struct LNode *head)
{
    /*Count the number of nodes in Linked List */
    int n = countLNodes(head);
 
    /* Construct BST */
    return sortedListToBSTRecur(&head, n);
}

/* UTILITY FUNCTIONS */
/* Function to insert a node at the beginging of the linked list */
void push(struct LNode** head_ref, int new_data)
{
    /* allocate node */
    struct LNode* new_node =
        (struct LNode*) malloc(sizeof(struct LNode));
    /* put in the data  */
    new_node->data  = new_data;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}
 
/* Function to print nodes in a given linked list */
void printList(struct LNode *node)
{
    while(node!=NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}
 
/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

///////////////////////////////////////////////////////////////////////
// Print a binary tree from top level to bottom level
// Input: pTreeRoot - the root of binary tree
///////////////////////////////////////////////////////////////////////
void PrintFromTopToBottom(TNode *pTreeRoot)
{
    if(!pTreeRoot)
        return;
    TNode * dummy = newNode(0);
    // get a empty queue
    deque<TNode *> dequeTreeNode;
    // insert the root at the end of queue
    dequeTreeNode.push_back(pTreeRoot);
    while(dequeTreeNode.size()) {
        // get a node from the head of queue, 
        // the element is still in the queue
        TNode *pNode = dequeTreeNode.front();
        dequeTreeNode.pop_front();
        
        // print the node
        cout << pNode->data << " ";
        if (pNode == dummy)
            continue;
        
        // print its left child sub-tree if it has
        if(pNode->left) 
            dequeTreeNode.push_back(pNode->left);
        else
            dequeTreeNode.push_back(dummy);
            
        // print its right child sub-tree if it has
        if(pNode->right)
            dequeTreeNode.push_back(pNode->right);
        else
            dequeTreeNode.push_back(dummy);
            
    }
    free (dummy);
}

/* Drier program to test above functions*/
int main()
{
    /* Start with the empty list */
    struct LNode* head = NULL;
 
    /* Let us create a sorted linked list to test the functions
       Created linked list will be 1->2->3->4->5->6->7 */
    push(&head, 11);
    push(&head, 10);
    push(&head, 9);
    push(&head, 8);
    push(&head, 7);
    push(&head, 6);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
 
    printf("Given Linked List ");
    printList(head);
 
    // #1
    /* Convert List to BST */
    struct TNode *root = sortedListToBST(head);
    printf("\nPreOrder Traversal of constructed BST ");
    preOrder(root);
    printf("\n");
    
    // #2
    // Using the array method
    int size = 0;
    int *s = copyListToArray(size,head);
    TNode *root2 = sortedListToBST_topdown(s,0,size-1);
    printf("PreOrder Traversal of constructed BST ");
    preOrder(root2);
    printf("\n");
    delete [] s; // Remember to free memory

    // Check the solution
    PrintFromTopToBottom(root);
    cout << endl;
    PrintFromTopToBottom(root2);
    cout << endl;

    return 0;
}