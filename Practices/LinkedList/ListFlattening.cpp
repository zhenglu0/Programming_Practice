//
//  ListFlattening.cpp
//  
//  Created by 罗铮 on 11/8/12.
//  Modified by 罗铮 on 04/10/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <list>

using namespace std;

struct node
{
    struct node * next;
    struct node * prev;
    struct node * child;
    int data;
};

int create_list(node *&head, node *&tail)
{
    // first level nodes
    node *ptr0 = new node();
    if(!ptr0)
        return -1;
    ptr0->next = 0;
    ptr0->data = 5;
    head = ptr0;
    
    node *ptr1 = new node();
    if(!ptr1)
        return -1;
    ptr1->data = 33;
    ptr0->next = ptr1;
    ptr1->next = 0;
    ptr1->prev = ptr0;
    
    node *ptr2 = new node();
    if(!ptr2)
        return -1;
    ptr2->data = 17;
    ptr1->next = ptr2;
    ptr2->next = 0;
    ptr2->prev = ptr1;
    
    node *ptr3 = new node();
    if(!ptr3)
        return -1;
    ptr3->data = 2;
    ptr2->next = ptr3;
    ptr3->next = 0;
    ptr3->prev = ptr2;
    
    node *ptr4 = new node();
    if(!ptr4)
        return -1;
    ptr4->data = 1;
    ptr3->next = ptr4;
    ptr4->next = 0;
    ptr4->prev = ptr3;
    
    tail = ptr4;
    
    // second level nodes
    node *ptr5 = new node();
    if(!ptr5)
        return -1;
    ptr5->data = 6;
    ptr0->child = ptr5;
    ptr5->next = 0;
    ptr5->prev = 0;
    
    node *ptr6 = new node();
    if(!ptr6)
        return -1;
    ptr6->data = 25;
    ptr5->next= ptr6;
    ptr6->next = 0;
    ptr6->prev = ptr5;
    
    node *ptr7 = new node();
    if(!ptr7)
        return -1;
    ptr7->data = 6;
    ptr6->next= ptr7;
    ptr7->next = 0;
    ptr7->prev = ptr6;
    
    node *ptr8 = new node();
    if(!ptr8)
        return -1;
    ptr8->data = 2;
    ptr3->child = ptr8;
    ptr8->next = 0;
    ptr8->prev = 0;
    
    node *ptr9 = new node();
    if(!ptr9)
        return -1;
    ptr9->data = 7;
    ptr8->next = ptr9;
    ptr9->next = 0;
    ptr9->prev = ptr8;
    
    // third level nodes
    node *ptr10 = new node();
    if(!ptr10)
        return -1;
    ptr10->data = 8;
    ptr6->child= ptr10;
    ptr10->next = 0;
    ptr10->prev = 0;
    
    node *ptr11 = new node();
    if(!ptr11)
        return -1;
    ptr11->data = 9;
    ptr7->child= ptr11;
    ptr11->next = 0;
    ptr11->prev = 0;
    
    node *ptr12 = new node();
    if(!ptr12)
        return -1;
    ptr12->data = 12;
    ptr8->child= ptr12;
    ptr12->next = 0;
    ptr12->prev = 0;
    
    node *ptr13 = new node();
    if(!ptr13)
        return -1;
    ptr13->data = 5;
    ptr12->next = ptr13;
    ptr13->next = 0;
    ptr13->prev = ptr12;
    
    // forth level nodes
    node *ptr14 = new node();
    if(!ptr14)
        return -1;
    ptr14->data = 7;
    ptr11->child= ptr14;
    ptr14->next = 0;
    ptr14->prev = 0;
    
    node *ptr15 = new node();
    if(!ptr15)
        return -1;
    ptr15->data = 21;
    ptr12->child= ptr15;
    ptr15->next = 0;
    ptr15->prev = 0;
    
    node *ptr16 = new node();
    if(!ptr16)
        return -1;
    ptr16->data = 3;
    ptr15->next = ptr16;
    ptr16->next = 0;
    ptr16->prev = ptr15;
    
    return 0;
}

void print(node *head)
{
    node *p = head;
    while(p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << "\n";
}

void ExploreAndSeprarate(node *childListStart, list<node*> &l)
{
    node *curNode = childListStart;
    while(curNode)
    {
        cout << curNode->data << " ";
        l.push_back(curNode);
        
        if(curNode->child)
             ExploreAndSeprarate(curNode->child,l);
        
        curNode = curNode->next;
    }
}

void Unflatten(node *start,list<node*> &l)
{
    ExploreAndSeprarate(start,l);
}

void Append(node *child, node *&tail)
{
    node *curNode = child;
    tail->next = child;
    child->prev = tail;

    while (curNode->next)
        curNode = curNode->next;

    tail = curNode;
}

void FlattenList(node *head, node *tail)
{
    node *curNode = head;
    while(curNode)
    {
        if(curNode->child)
            Append(curNode->child,tail);
        
        curNode = curNode->next;
    }
}

int main(int argc, char* argv[])
{
    // initialize the node
    node *head, *tail;
    int status = create_list(head,tail);
    cout << "The creating status returned is " << status << endl;
    print(head);

    list <node*> l;
    cout << "The unflatten list is " << endl;
    Unflatten(head,l);

    cout << endl << "The flatten list1 is" << endl;
    for (list<node*>::iterator iter = l.begin(); iter != l.end(); ++iter )
        cout << (*iter)->data << " ";

    cout << endl << "The flatten list2 is " << endl;
    FlattenList(head,tail);
    print(head);

    return 0;
}


