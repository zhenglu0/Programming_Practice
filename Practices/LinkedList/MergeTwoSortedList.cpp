//
//  MergeTwoSortedList.cpp
//  
//  Modified by 罗铮 on 03/19/14.
//  
//  http://www.geeksforgeeks.org/merge-two-sorted-linked-lists/
//
/*  Program to alternatively split a linked list into two halves */

#include <cstdio>
#include <cstdlib>
#include <cassert>
 
/* Link list node */
struct node
{
    int data;
    struct node* next;
};
 
/* pull off the front node of the source and put it in dest */
void MoveNode(struct node** destRef, struct node** sourceRef);
 
/* Takes two lists sorted in increasing order, and splices 
   their nodes together to make one big sorted list which 
   is returned.  */
struct node* SortedMerge_Dummy(struct node* a, struct node* b) 
{
    /* a dummy first node to hang the result on */   
    struct node dummy;      

    /* tail points to the last result node  */
    struct node* tail = &dummy;  

    /* so tail->next is the place to add new nodes 
    to the result. */
    dummy.next = NULL;
    while(1) 
    {
        if(a == NULL) 
        { 
            /* if either list runs out, use the other list */
            tail->next = b;
            break;
        }
        else if (b == NULL) 
        {
            tail->next = a;
            break;
        }
        if (a->data <= b->data) 
            MoveNode(&(tail->next), &a);
        else
            MoveNode(&(tail->next), &b);

        tail = tail->next;
    }
    return(dummy.next);
}  

struct node* SortedMerge_Local_References(struct node* a, 
                                          struct node* b) 
{
    struct node* result = NULL;

    /* point to the last result pointer */
    struct node** lastPtrRef = &result; 

    while(1) 
    {
        if (a == NULL) 
        {
            *lastPtrRef = b;
            break;
        }
        else if (b == NULL) 
        {
            *lastPtrRef = a;
            break;
        }
        if(a->data <= b->data) 
            MoveNode(lastPtrRef, &a);
        else
            MoveNode(lastPtrRef, &b);

        /* tricky: advance to point to the next ".next" field */
        lastPtrRef = &((*lastPtrRef)->next); 
    }
    return(result);
}

// The recursive algorithm is much simpler to implement
struct node* SortedMerge_Recursive(struct node* a, struct node* b) 
{
    struct node* result = NULL;

    /* Base cases */
    if (a == NULL) 
        return(b);
    else if (b == NULL)
        return(a);

    /* Pick either a or b, and recur */
    if (a->data <= b->data) 
    {
        result = a;
        result->next = SortedMerge_Recursive(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge_Recursive(a, b->next);
    }
    return(result);
}

/* UTILITY FUNCTIONS */
/* MoveNode() function takes the node from the front of the source, 
   and move it to the front of the dest.
   It is an error to call this with the source list empty. 
 
   Before calling MoveNode():
   source == {1, 2, 3}
   dest == {1, 2, 3}
 
   Affter calling MoveNode():
   source == {2, 3}
   dest == {1, 1, 2, 3}
*/
void MoveNode(struct node** destRef, struct node** sourceRef)
{
    /* the front source node  */
    struct node* newNode = *sourceRef;
    assert(newNode != NULL);

    /* Advance the source pointer */
    *sourceRef = newNode->next;

    /* Link the old dest off the new node */
    newNode->next = *destRef; 

    /* Move dest to point to the new node */
    *destRef = newNode;
}
 
 
/* Function to insert a node at the beginging of the linked list */
void push(struct node** head_ref, int new_data)
{
    /* allocate node */
    struct node* new_node =
            (struct node*) malloc(sizeof(struct node));

    /* put in the data  */
    new_node->data  = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);     

    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}
 
/* Function to print nodes in a given linked list */
void printList(struct node *node)
{
    while(node!=NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
} 

/* Drier program to test above functions*/
int main()
{
    /* Start with the empty list */
    struct node* res = NULL;
    struct node* a = NULL;
    struct node* b = NULL;  

    /* Let us create two sorted linked lists to test the functions
    Created lists shall be a: 5->10->15,  b: 2->3->20 */
    push(&a, 15);
    push(&a, 10);
    push(&a, 5);

    push(&b, 20);
    push(&b, 3);
    push(&b, 2);  

    /* Remove duplicates from linked list */
    //res = SortedMerge_Dummy(a, b); 
    //res = SortedMerge_Local_References(a, b); 
    res = SortedMerge_Recursive(a, b); 

    printf("Merged Linked List is: \n");
    printList(res);            

    return 0;
}