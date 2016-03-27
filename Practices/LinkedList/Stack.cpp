//
//  Stack.cpp
//
//  Modified by 罗铮 on 04/19/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Creating a NODE Structure
struct node
{
    int data;
    node *next;
};

// Creating a class STACK
class stack
{
    struct node *top;
    public:
    stack() // constructor
    {
        top = NULL;
    }
    void push(); // to insert an element
    void pop();  // to delete an element
    void show(); // to show the stack
};

// PUSH Operation
void stack::push()
{
    int value;
    struct node *ptr;
    cout << "\nPUSH Operation\n"
            "Enter a number to insert: ";
    cin >> value;
    ptr = new node;
    ptr->data = value;
    ptr->next = NULL;
    if(top != NULL)
    {
        ptr->next = top;
    }
    top = ptr;
    cout << "\nNew item is inserted to the stack!!!";
}

// POP Operation
void stack::pop()
{
    struct node *temp;
    if(top == NULL)
    {
        cout<<"\nThe stack is empty!!!";
    }
    else
    {
        temp = top;
        top = top->next;
        cout << "\nPOP Operation........\nPoped value is " 
             << temp->data;
        delete temp;
    }
}

// Show stack
void stack::show()
{
    struct node *ptr = top;
    cout << "\nThe stack is\n";
    while(ptr != NULL)
    {
        cout << ptr->data << " ->";
        ptr = ptr->next;
    }
    cout << "NULL\n";
}

// Main function
int main(int argc, char* argv[])
{
    stack s;
    int choice;
    while(1)
    {
        cout << "\n--------------------------------------"
                "---------------------"
                "\n\t\tSTACK USING LINKED LIST\n\n"
                "1:PUSH\n2:POP\n3:DISPLAY STACK\n4:EXIT"
                "\nEnter your choice(1-4): ";
        cin >> choice;
        cout << "Your choice is " << choice;
        switch(choice)
        {
            case 1:
                s.push();
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.show();
                break;
            case 4:
                return 0;
            default:
                cout<<"Please re-enter correct choice(1-4)!!";
        }
    }
    return 0;
}



