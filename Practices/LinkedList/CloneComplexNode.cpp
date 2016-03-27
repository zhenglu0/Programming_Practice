//
//  CloneComplexNode.cpp
//
//  Created by 罗铮 on 10/29/12.
//  Copyright (c) 2012 罗铮. All rights reserved.
//
//  http://zhedahht.blog.163.com/blog/static/254111742010819104710337/
//  http://www.geeksforgeeks.org/a-linked-list-with-next-and-arbit-pointer/

#include <iostream>
#include <unordered_map>

using namespace std;

// Definition of Complex Nodes
struct ComplexNode
{
    int value;
    ComplexNode* next;
    ComplexNode* arbit;
    ComplexNode():next(NULL),arbit(NULL){}
};

// #1 Inplace Clone Complex Node
////////////////////////////////////////////////////////////
// Clone all nodes in a complex linked list with head pHead,
// and connect all nodes with next link
////////////////////////////////////////////////////////////
void CloneNodes(ComplexNode* pHead)
{
    ComplexNode* pNode = pHead;
    while(pNode != NULL)
    {
        ComplexNode* pCloned = new ComplexNode();
        pCloned->value = pNode->value;
        pCloned->next = pNode->next;
        pCloned->arbit = NULL;
        
        pNode->next = pCloned;
        
        pNode = pCloned->next;
    }
}

////////////////////////////////////////////////////////////
// Connect sibling nodes in a complex link list
////////////////////////////////////////////////////////////
void ConnectSiblingNodes(ComplexNode* pHead)
{
    ComplexNode* pNode = pHead;
    while(pNode != NULL)
    {
        ComplexNode* pCloned = pNode->next;
        if(pNode->arbit != NULL)
        {
            pCloned->arbit = pNode->arbit->next;
        }
        
        pNode = pCloned->next;
    }
}

////////////////////////////////////////////////////////////
// Split a complex list into two:
// Reconnect nodes to get the original list, and its cloned list
////////////////////////////////////////////////////////////
ComplexNode* ReconnectNodes(ComplexNode* pHead)
{
    ComplexNode* pNode = pHead;
    ComplexNode* pClonedHead = NULL;
    ComplexNode* pClonedNode = NULL;
    
    if(pNode != NULL)
    {
        pClonedHead = pClonedNode = pNode->next;
        pNode->next = pClonedNode->next;
        pNode = pNode->next;
    }
    
    while(pNode != NULL)
    {
        pClonedNode->next = pNode->next;
        pClonedNode = pClonedNode->next;
        
        pNode->next = pClonedNode->next;
        pNode = pNode->next;
    }
    
    return pClonedHead;
}

////////////////////////////////////////////////////////////
// Clone a complex linked list with head pHead
////////////////////////////////////////////////////////////
ComplexNode* CloneInPlace(ComplexNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

// Create a complex node linked list for test
ComplexNode* CreateComplexNodeLinkedList()
{
    // Create nodes
    ComplexNode* node1 = new ComplexNode();
    ComplexNode* node2 = new ComplexNode();
    ComplexNode* node3 = new ComplexNode();
    ComplexNode* node4 = new ComplexNode();
    ComplexNode* node5 = new ComplexNode();
    // Set value to nodes
    node1->value = 1;
    node2->value = 2;
    node3->value = 3;
    node4->value = 4;
    node5->value = 5;
    // Link them with next
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    // Link them with arbit
    node1->arbit = node3;
    node2->arbit = node1;
    node3->arbit = node5;
    node4->arbit = node3;
    node5->arbit = node2;
    
    return node1;
}

// #2. By using the hash table to store the node
////////////////////////////////////////////////////////////
// Clone a complex linked list with head pHead
////////////////////////////////////////////////////////////
ComplexNode* CloneByHashing(ComplexNode* pHead)
{
    if (pHead == NULL)
        return NULL;

    unordered_map<ComplexNode*,ComplexNode*> ptrMap;

    ComplexNode* pClonedHead = new ComplexNode();
    pClonedHead->value = pHead->value;
    pClonedHead->arbit = pHead->arbit;
    ptrMap[pHead] = pClonedHead;

    ComplexNode* pCloned = pClonedHead; 
    ComplexNode* pCurrent = pHead->next;

    while (pCurrent != NULL)
    {
        pCloned->next = new ComplexNode();
        ptrMap[pCurrent] = pCloned->next;
        pCloned->next->value = pCurrent->value;
        pCloned->next->arbit = pCurrent->arbit;

        pCloned = pCloned->next;
        pCurrent = pCurrent->next;
    }

    ComplexNode* pClonedCurrent = pClonedHead;
    ComplexNode* temp = NULL;
    while (pClonedCurrent != NULL)
    { 
        temp = pClonedCurrent->arbit;
        pClonedCurrent->arbit = ptrMap.find(temp)->second;
        pClonedCurrent = pClonedCurrent->next;
    }

    return pClonedHead;
}

// Unitily function
void PrintList(ComplexNode *head)
{
    ComplexNode *ptr = head;
    
    while (ptr != NULL)
    {
        cout << "node address = " << ptr << ","
             << " node value = " << ptr->value << ","
             << " node arbit address = " << ptr->arbit << ","
             <<  " node arbit value = " << ptr->arbit->value << endl;

        ptr = ptr->next;
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    ComplexNode *head = CreateComplexNodeLinkedList();
    ComplexNode *headCloned1 = CloneInPlace(head);
    ComplexNode *headCloned2 = CloneByHashing(head);

    PrintList(head);
    PrintList(headCloned1);
    PrintList(headCloned2);
    
    return 0;
}

