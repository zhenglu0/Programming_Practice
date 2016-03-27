//
//  Slist.cpp
//
//  Modified by 罗铮 on 04/19/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>

using namespace std;

struct element
{
    int data;
    struct element *next;
};

element* create_list()
{
    element *p,*q,*head;
    int x,n = 4;
    head = new element();
    head->next = 0;
    head->data = 8;
    q = head;
    for(int i=0; i<n; ++i)
    {
        switch(i)
        {
            case 0:
                x = 12;
                break;
            case 1:
                x = 8;
                break;
            case 2:
                x = 8;
                break;
            case 3:
                x = 6;
                break;
            default:  // Note the colon, not a semicolon
                cout<<"Error, bad input, quitting\n";
                break;
        }
       p = new element();
       p->data = x;
       p->next = 0;
       q->next = p;
       q = p;
       p = 0;
    }
    return head;
}

void output(element *head)
{
    element *p = head;
    while(p)
    {
       cout << p->data << " ";
       p = p->next;
    }
    cout << "\n";
}

int change_head(element **head)
{
    element *newElem = new element();
    if(newElem == 0)
    {
        return -1;
    }
    newElem->next = (*head);
    newElem->data = 7;
    *head = newElem;
    return 0;
}

element *find_element_six(element *elem)
{
    while(elem)
    {
        if(elem->data == 6)
        {
            return elem;
        }
    elem = elem->next;
    }
    return 0;
}

void delete_list(element *head)
{
    element *next, *deleteMe;
    deleteMe = head;
    while(deleteMe)
    {
        next = deleteMe->next;
        delete deleteMe;
        deleteMe = next;
    }
}

int delete_element_found_first(element **head, int deleteMe)
{
    element *elem = *head;
    element *temp;
    if((*head)->data == deleteMe)
    {
        temp = elem->next;
        delete (*head);
        *head = temp;
        return 0;
    }
    while(elem)
    {
        if(elem->next->data == deleteMe)
        {
            temp = elem->next->next;
            delete elem->next;
            elem->next = temp;
            return 0;
        }
        elem = elem->next;
    }
    return 0;
}

int delete_element(element **head, int deleteMe)
{
    element *curPos = *head;
    if(deleteMe == (*head)->data)
    {
        delete (*head);
        *head = curPos->next;
    }
    else
    {
        while(curPos)
        {
            if(curPos->next != 0 && 
               curPos->next->data == deleteMe)
            {
                element *temp = curPos->next;
                curPos->next = curPos->next->next;
                delete temp;
            }
            else
            {
                curPos = curPos->next;
            }
        }
    }
    return 0;
}

int InsertAfter(element **head, int after, int data)
{
    element *newElem, *curPos = *head;
    newElem = new element();
    newElem->data = data;
    int element_found = 0;
    while(curPos)
    {
        if(curPos->data == after)
        {
            newElem->next = curPos->next;
            curPos->next = newElem;
            element_found = 1;
            return 0;
        }
        curPos = curPos->next;
    }
    if(element_found == 0)
    {
        delete newElem;
    }
    return 0;
}

void RemoveHead(element **head)
{
    element *temp;
    if((*head) != 0 )
    {
        temp = (*head)->next;
        delete(*head) ;
        (*head) = temp;
    }
}

element* FindMToLastElement(element *head, int m)
{
    element *current, *mBehind = 0;
    current = head;
    if(m <= 0)
    {
        return 0;
    }
    for(int i = 0; i < m-1; ++i)
    {
        if(current->next)
        {
            current = current->next;
        }
        else
        {
            return 0;
        }
    }
    mBehind = head;
    while(current->next)
    {
        current = current->next;
        mBehind = mBehind->next;
    }
    return mBehind;
}

element* create_cyclic_list()
{
    element *p,*q,*head;
    int x,n = 4;
    head = new element();
    head->next = 0;
    head->data = 8;
    q = head;
    for(int i=0; i<n; ++i)
    {
        switch(i)
        {
            case 0:
                x = 12;
                break;
            case 1:
                x = 10;
                break;
            case 2:
                x = 9;
                break;
            case 3:
                x = 6;
                break;
            default:  // Note the colon, not a semicolon
                cout<<"Error, bad input, quitting\n";
                break;
        }
       p = new element();
       p->data = x;
       p->next = head;
       q->next = p;
       q = p;
       p = 0;
    }
    return head;
}

int DetermineTermination(element *head)
{
    element *fast, *slow;
    slow = head;
    fast = head->next->next;
    while(1)
    {
        if(!fast||!fast->next)
        {
            return 0;
        }
        else if(fast == slow || fast->next == slow)
        {
            return 1;
        }
        else
        {
            slow = slow->next;
            fast = fast->next->next;
        }
    }
}

int DetermineTermination_compicated(element *head)
{
    element *curPos = head;
    while(curPos != 0)
    {
        for(element *pos = head; pos != curPos; pos = pos->next)
        {
            if(pos == curPos->next)
            {
                return 1;
            }
        }
        curPos = curPos->next;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    // initialize the element
    element *head = create_list();
    element **p_head = &head;
    change_head(p_head);
    output(head);
    element *found;
    found = find_element_six(head);
    if(found)
    {
        cout << "The element is found, and the value is " 
             << found->data << endl;
    }
    else
    {
        cout << "The element has not been found" << endl;
    }
    //delete_element_found_first(p_head,7);
    //delete_element(p_head,8);
    InsertAfter(p_head,6,520);
    //RemoveHead(p_head);
    output(head);
    element *tolast = FindMToLastElement(head,2);
    if(tolast)
    {
        cout << "The value of to last element is " 
             << tolast->data << endl;
    }

    element *cyclic_head = create_cyclic_list();
    cout << "If it is Cyclic list " 
         << DetermineTermination(cyclic_head) << endl;
    //cout << "If it is Cyclic list " 
         //<< DetermineTermination_compicated(cyclic_head)<< endl;

    //delete_list(head);
    return 0;
}
