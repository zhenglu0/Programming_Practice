//
//  AddTwoList.cpp
//
//  Created by 罗铮 on 05/16/14.
//  Copyright (c) 2014 罗铮. All rights reserved.
//
//  http://www.geeksforgeeks.org/add-two-numbers-represented-by-linked-lists/
//  http://www.geeksforgeeks.org/sum-of-two-linked-lists/
//
//  This Program adds two linked list as integers

/*
    Given two numbers represented by two lists, 
    write a function that returns sum list. The sum 
    list is list representation of addition of two input numbers.

    Example 1
    Input:
      First List: 5->6->3  // represents number 365
      Second List: 8->4->2 //  represents number 248
    Output
      Resultant list: 3->1->6  // represents number 613

    Example 2
    Input:
      First List: 7->5->9->4->6  // represents number 64957
      Second List: 8->4 //  represents number 48
    Output
      Resultant list: 5->0->0->5->6  // represents number 65005
*/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct node
{
    int data;
    node *next;
    node(int d):data(d),next(NULL){};
};

// Unitily Functions
void print_list(node* head)
{
    node *current = head;
    while(current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void print_list_reversely(node* head)
{
    if (head)
    {
        print_list_reversely(head->next);
        cout << head->data << " ";
    }
}

node* clone_list(node *h)
{
    if (!h)
        return NULL;

    node* pClonedHead = new node(h->data);
    node* pCloned = pClonedHead; 
    node* pCurrent = h->next;

    while (pCurrent) {
        pCloned->next = new node(pCurrent->data);
        pCloned = pCloned->next;
        pCurrent = pCurrent->next;
    }

    return pClonedHead;
}

void delete_list(node *head)
{
    node *next, *current_delete;
    current_delete = head;
    while(current_delete)
    {
        next = current_delete->next;
        delete current_delete;
        current_delete = next;
    }
}

/* Function to insert a node at the beginning of the Doubly Linked List */
void push_front(node** head_ref, int new_data)
{
    /* allocate node */
    node* new_node = new node(new_data);
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}

// #1. My own solution
int sum(int a, int b, int &current_carry, int previous_carry)
{
    int sum = a + b + previous_carry;
    if (sum >= 10) {
        current_carry = 1;
        return sum - 10;
    } else {
        current_carry = 0;
        return sum;
    }
}

node* add_two_list(node *h1, node* h2)
{
    // If both list are NULL
    if (!h1 && !h2)
        return NULL;

    // If one of them is empty
    if (h1 && !h2)
        return clone_list(h1);
    if (!h1 && h2)
        return clone_list(h2); 

    // If none of them is empty
    int current_carry = 0, previous_carry = 0;
    // Get the head of the result first
    node *result_head = new node( sum(h1->data,h2->data,
                                      current_carry,previous_carry) );
    node *result_current = result_head;
    node *current1 = h1->next;
    node *current2 = h2->next;
    
    // Add the rest of the digit
    while (current1 && current2) {
        previous_carry = current_carry;
        result_current->next = new node( sum(current1->data,
                                             current2->data, 
                                             current_carry, 
                                             previous_carry) );
        current1 = current1->next;
        current2 = current2->next;
        result_current = result_current->next;
    }

    // Add the rest of the list when either of them is empty
    if (current1 && !current2) {
        result_current->next = clone_list(current1);
        result_current->next->data += current_carry;
    } else if (!current1 && current2) {
        result_current->next = clone_list(current2);
        result_current->next->data += current_carry;
    } else {
        if (current_carry == 1)
            result_current->next = new node(1);    
    }

    return result_head;
}

node* create_linkedlist1()
{
    // create the nodes
    node *node1 = new node(5);
    node *node2 = new node(3);
    node *node3 = new node(9);
    //node *node4 = new node(3);
    //node *node5 = new node(4);

    // set the next pointer and head
    node1->next = node2;
    node2->next = node3;
    //node3->next = node4;
    //node4->next = node5;

    return node1;
}

node* create_linkedlist2()
{
    // create the nodes
    node *node1 = new node(7);
    node *node2 = new node(0);
    node *node3 = new node(1);

    // set the next pointer and head
    node1->next = node2;
    node2->next = node3;

    return node1;
}

// #2. Soluton from Geeks for Geeks 
/* Adds contents of two linked lists and return the head node of resultant list */
node* addTwoLists (node* first, node* second)
{
    node* res = NULL; // res is head node of the resultant list
    node *temp, *prev = NULL;
    int carry = 0, sum;
 
    while (first != NULL || second != NULL) //while both lists exist
    {
        // Calculate value of next digit in resultant list. 
        // The next digit is sum of following things
        // (i)  Carry
        // (ii) Next digit of first list (if there is a next digit)
        // (ii) Next digit of second list (if there is a next digit)
        sum = carry + (first? first->data: 0) + (second? second->data: 0);
 
        // update carry for next calulation
        carry = (sum >= 10)? 1 : 0;
 
        // update sum if it is greater than 10
        sum = sum % 10;
 
        // Create a new node with sum as data
        temp = new node(sum);
 
        // if this is the first node then set it as head of the resultant list
        if(res == NULL)
            res = temp;
        else // If this is not the first node then connect it to the rest.
            prev->next = temp;
 
        // Set prev for next insertion
        prev  = temp;
 
        // Move first and second pointers to next nodes
        if (first)
            first = first->next;
        if (second) 
            second = second->next;
    }
 
    if (carry > 0)
      temp->next = new node(carry);
 
    // return head of the resultant list
    return res;
}

//  #3
/*  Given two numbers represented by two linked lists, write a function that 
    returns sum list. The sum list is linked list representation of addition 
    of two input numbers. It is not allowed to modify the lists. Also, not 
    allowed to use explicit extra space (Hint: Use Recursion)

    Example

    Input:
      First List: 5->6->3  // represents number 563
      Second List: 8->4->2 //  represents number 842
    Output
      Resultant list: 1->4->0->5  // represents number 1405
*/

//  A utility function to swap two pointers
inline void swapPointer( node** a, node** b )
{
    node* t = *a;
    *a = *b;
    *b = t;
}
 
/* A utility function to get size of linked list */
int getSize(node *node)
{
    int size = 0;
    while (node != NULL)
    {
        node = node->next;
        size++;
    }
    return size;
}
 
// Adds two linked lists of same size represented by head1 and head2 and returns
// head of the resultant linked list. Carry is propagated while returning from
// the recursion
node* addSameSize(node* head1, node* head2, int* carry)
{
    // Since the function assumes linked lists are of same size,
    // check any of the two head pointers
    if (head1 == NULL)
        return NULL;
 
    int sum;
 
    // Allocate memory for sum node of current two nodes
    node* result = (node *)malloc(sizeof(node));
 
    // Recursively add remaining nodes and get the carry
    result->next = addSameSize(head1->next, head2->next, carry);
 
    // add digits of current nodes and propagated carry
    sum = head1->data + head2->data + *carry;
    *carry = sum / 10;
    sum = sum % 10;
 
    // Assigne the sum to current node of resultant list
    result->data = sum;
 
    return result;
}
 
// This function is called after the smaller list is added to the bigger
// lists's sublist of same size.  Once the right sublist is added, the carry
// must be added toe left side of larger list to get the final result.
void addCarryToRemaining(node* head1, node* cur, int* carry, node** result)
{
    int sum;
 
    // If diff. number of nodes are not traversed, add carry
    if (head1 != cur)
    {
        addCarryToRemaining(head1->next, cur, carry, result);
 
        sum = head1->data + *carry;
        *carry = sum/10;
        sum %= 10;
 
        // add this node to the front of the result
        push_front(result, sum);
    }
}
 
// The main function that adds two linked lists represented by head1 and head2.
// The sum of two lists is stored in a list referred by result
void addList(node* head1, node* head2, node** result)
{
    node *cur;
 
    // first list is empty
    if (head1 == NULL)
    {
        *result = clone_list(head2);
        return;
    }
 
    // second list is empty
    else if (head2 == NULL)
    {
        *result = clone_list(head1);
        return;
    }
 
    int size1 = getSize(head1);
    int size2 = getSize(head2);
 
    int carry = 0;
 
    // Add same size lists
    if (size1 == size2)
        *result = addSameSize(head1, head2, &carry);
 
    else
    {
        int diff = abs(size1 - size2);
 
        // First list should always be larger than second list.
        // If not, swap pointers
        if (size1 < size2)
            swapPointer(&head1, &head2);
 
        // move diff. number of nodes in first list
        cur = head1;
        while (diff > 0) 
        {
            cur = cur->next;
            diff--;
        }
 
        // get addition of same size lists
        *result = addSameSize(cur, head2, &carry);
 
        // get addition of remaining first list and carry
        addCarryToRemaining(head1, cur, &carry, result);
    }
 
    // if some carry is still there, add a new node to the fron of
    // the result list. e.g. 999 and 87
    if (carry)
        push_front(result, carry);
}

// Driver program to test above functions
int main()
{
    // #1.
    node *h1 = create_linkedlist1();
    node *h2 = create_linkedlist2();
    node *r  = add_two_list(h1, h2);

    cout << "h1: ";
    print_list(h1);
    delete_list(h1);
    cout << "h2: ";
    print_list(h2);
    delete_list(h2);
    cout << "r : ";
    print_list(r);
    delete_list(r);
    cout << endl;

    // #2.
    node* res = NULL;
    node* first = NULL;
    node* second = NULL;
 
    // create first list 7->5->9->4->6
    push_front(&first, 6);
    push_front(&first, 4);
    push_front(&first, 9);
    push_front(&first, 5);
    push_front(&first, 7);
    printf("h1: ");
    print_list(first);
 
    // create second list 8->4
    push_front(&second, 4);
    push_front(&second, 8);
    printf("h2: ");
    print_list(second);
 
    // Add the two lists and see result
    res = addTwoLists(first, second);
    delete_list(first);
    delete_list(second);
    printf("r : ");
    print_list(res);
    delete_list(res);
    cout << endl;

    // #3.
    node *head1 = NULL, *head2 = NULL, *result = NULL;
 
    int arr1[] = {          9, 8, 7};
    int arr2[] = { 9, 9, 9, 0, 5, 3};
 
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
 
    // Create first list as 9->9->9
    for (int i = size1-1; i >= 0; --i)
        push_front(&head1, arr1[i]);
 
    // Create second list as 1->8
    for (int i = size2-1; i >= 0; --i)
        push_front(&head2, arr2[i]);
 
    cout << "h1: ";
    print_list_reversely(head1);
    cout << endl << "h2: ";
    print_list_reversely(head2);

    // Add the two lists and see result
    addList(head1, head2, &result);

    delete_list(head1);
    delete_list(head2);

    cout << endl << "r : ";
    print_list_reversely(result);
    delete_list(result);
    cout << endl;

    return 0;
}
