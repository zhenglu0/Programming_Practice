//
//  DeleteNode.cpp
//
//  Created by 罗铮 on 11/7/12.
//  Copyright (c) 2012 罗铮. All rights reserved.
//  
//  http://zhedahht.blog.163.com/blog/static/254111742007112255248202/

#include <iostream>

using namespace std;

// 题目：给定链表的头指针和一个结点指针，在O(1)时间删除该结点。链表结点的定义如下：

struct Node
{
    int    key;
    Node*  next;
};

///////////////////////////////////////////////////////////////////////
// Delete a node in a list
// Input: pListHead - the head of list
//        pToBeDeleted - the node to be deleted
///////////////////////////////////////////////////////////////////////
void DeleteNode(Node* pListHead, Node* pToBeDeleted)
{
    // always to remember to check if the linked list is empty
    if(!pListHead || !pToBeDeleted)
        return;
    
    // if pToBeDeleted is not the last node in the list
    if(pToBeDeleted->next != NULL)
    {
        // copy data from the node next to pToBeDeleted
        Node* pNext = pToBeDeleted->next;
        pToBeDeleted->key = pNext->key;
        pToBeDeleted->next = pNext->next;
        
        // delete the node next to the pToBeDeleted
        delete pNext;
        pNext = NULL;
    }
    // if pToBeDeleted is the last node in the list
    else
    {
        // get the node prior to pToBeDeleted
        Node* pNode = pListHead;
        while(pNode->next != pToBeDeleted)
            pNode = pNode->next;

        // deleted pToBeDeleted
        pNode->next = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
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

Node* CreateLinkedList1()
{
    // create the nodes
    Node *node1 = new Node();
    Node *node2 = new Node();
    Node *node3 = new Node();
    Node *node4 = new Node();
    Node *node5 = new Node();
    // set the value
    node1->key = 5;
    node2->key = 3;
    node3->key = 1;
    node4->key = 3;
    node5->key = 4;
    // set the next pointer and head
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = NULL;
    return node1;
}

Node* CreateLinkedList2()
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
    Node *pListHead = CreateLinkedList1();
    PrintLinkedList(pListHead);
    cout << endl;
    
    Node *ptoBeDeleted1 = pListHead->next->next;
    DeleteNode(pListHead,ptoBeDeleted1);
    PrintLinkedList(pListHead);
    cout << endl;
    
    Node *ptoBeDeleted2 = pListHead->next->next->next;
    DeleteNode(pListHead,ptoBeDeleted2);
    PrintLinkedList(pListHead);
    cout << endl;
    
    Node *pListHead2 = CreateLinkedList2();
    PrintLinkedList(pListHead2);
    cout << endl;
    
    Node *ptoBeDeleted1_2 = pListHead2->next->next;
    DeleteNode(pListHead2,ptoBeDeleted1_2);
    PrintLinkedList(pListHead2);
    cout << endl;
    
    Node *ptoBeDeleted2_2 = pListHead2->next->next->next;
    DeleteNode(pListHead2,ptoBeDeleted2_2);
    PrintLinkedList(pListHead2);
    cout << endl;

    return 0;
}

