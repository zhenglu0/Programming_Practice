//
//  ReverseLinkedList.cpp
//  
//  Created by 罗铮 on 11/9/12.
//  Modified by 罗铮 on 05/12/14.
//  Copyright (c) 2012 罗铮. All rights reserved.
//  http://zhedahht.blog.163.com/blog/static/2541117420073471124487/

#include <iostream>

using namespace std;

struct Node
{
    int   key;
    Node* next;
};


///////////////////////////////////////////////////////////////////////
// Reverse a list iteratively
// Input: pHead - the head of the original list
// Output: the head of the reversed head
// We need at least 3 pointers to do the operation
///////////////////////////////////////////////////////////////////////
Node* ReverseIteratively(Node* pHead)
{
    Node* pReversedHead = NULL;
    Node* pNode = pHead;
    Node* pPrev = NULL;
    while(pNode != NULL)
    {
        // get the next node, and save it at pNext
        Node* pNext = pNode->next;
        
        // if the next node is null, the currect is the end of original
        // list, and it's the head of the reversed list
        if(pNext == NULL)
            pReversedHead = pNode;
        
        // reverse the linkage between nodes
        pNode->next = pPrev;
        
        // move forward on the the list
        pPrev = pNode;
        pNode = pNext;
    }
    
    return pReversedHead;
}


// 1.
void DoReverse1(Node *pPrev,Node *pNode,
                Node *pNext,Node *&pReversedHead)
{
    pNode->next = pPrev;
    pReversedHead = pNode;
    if (pNext)
        DoReverse1(pNode, pNext, pNext->next, pReversedHead);
}

// 1. ReverseRecursively is used as a wrapper for the recursion
Node* ReverseRecursively1(Node* pHead)
{
    if(!pHead)
        return NULL;
    Node *pPrev = NULL;
    Node *pNode = pHead;
    Node *pReversedHead = pHead;
    Node *pNext = pNode->next ? pNode->next : NULL;
    if (pNext)
        DoReverse1(pPrev,pNode,pNext,pReversedHead);
    return pReversedHead;
}


// 2. using the call stack to do the recursion
// very elegant solution, because the call stack
// remembers the previous node, pHead
Node* ReverseRecursively2(Node* pHead)
{
    if (pHead && pHead->next)
    {
        Node *pRemainedHead = ReverseRecursively2(pHead->next);
        pHead->next->next  = pHead;
        pHead->next = NULL;
        return pRemainedHead;
    }
    else
        return pHead;
}


// 3.
Node* DoReverse2(Node *pPrev,Node *pNode,Node *pNext)
{
    pNode->next = pPrev;
    if (pNext)
        return DoReverse2(pNode, pNext, pNext->next);
    else
        return pNode;
}

// 3.
// ReverseRecursively is used as a wrapper for the recursion
Node* ReverseRecursively3(Node* pHead)
{
    if(!pHead)
        return NULL;
    Node *pPrev = NULL;
    Node *pNode = pHead;
    Node *pReversedHead = pHead;
    Node *pNext = pNode->next ? pNode->next : NULL;
    if (pNext)
        pReversedHead = DoReverse2(pPrev,pNode,pNext);
    return pReversedHead;
}


void PrintLinkedList(Node *pListHead)
{
    Node *currentNode = pListHead;
    while (currentNode != NULL)
    {
        cout << currentNode->key << " ";
        currentNode = currentNode->next;
    }
}


Node* CreateLinkedList()
{
    Node *pHead = new Node();
    pHead->key = 5;
    Node *previous = pHead;
    for (int i = 4; i > 0; --i)
    {
        Node *node = new Node();
        node->key = i;
        previous->next = node;
        previous = node;
    }
    return pHead;
}


int main(int argc, const char * argv[])
{
    Node *pHead = CreateLinkedList();
    PrintLinkedList(pHead);
    cout << endl;
    
    Node *rHead = ReverseRecursively3(pHead);
    PrintLinkedList(rHead);
    cout << endl;

    return 0;
}

