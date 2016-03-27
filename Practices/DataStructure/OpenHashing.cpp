//
//  OpenHashing.cpp
//  
//  Also means Seperate Channing
//  Modified by 罗铮 on 03/18/14.
//  http://www.algolist.net/Data_structures/Hash_table/Chaining

#include <iostream>

using namespace std;

const int TABLE_SIZE = 128;

class LinkedHashEntry {
private:
    int key;
    int value;
    LinkedHashEntry *next;
public:
    LinkedHashEntry(int key, int value) 
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }

    int getKey() { return key; }

    int getValue() { return value; }

    void setValue(int value) { this->value = value; }

    LinkedHashEntry *getNext() { return next; }

    void setNext(LinkedHashEntry *next) { this->next = next; }
};
  
class HashMap {
private:
    LinkedHashEntry **table;
public:
    HashMap() 
    {
        table = new LinkedHashEntry*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }

    int find(int key) 
    {
        // A really simple hash function
        int hash = (key % TABLE_SIZE);
        if (table[hash] == NULL)
            return -1;
        else {
            LinkedHashEntry *entry = table[hash];
            while (entry != NULL && entry->getKey() != key)
                entry = entry->getNext();
            if (entry == NULL)
                return -1;
            else
                return entry->getValue();
        }
    }

    void insert(int key, int value) 
    {
        int hash = (key % TABLE_SIZE);
        if (table[hash] == NULL)
            table[hash] = new LinkedHashEntry(key, value);
        else {
            LinkedHashEntry *entry = table[hash];
            while (entry->getNext() != NULL)
                entry = entry->getNext();
            // we should check whether the entry already exist
            // if not exist we insert at the end of the list
            if (entry->getKey() == key)
                entry->setValue(value);
            else
                entry->setNext(new LinkedHashEntry(key, value));
        }
    }

    void remove(int key) 
    {
        int hash = (key % TABLE_SIZE);
        if (table[hash] != NULL) {
            LinkedHashEntry *prevEntry = NULL;
            LinkedHashEntry *entry = table[hash];
            while (entry->getNext() != NULL && 
                   entry->getKey() != key) {
                prevEntry = entry;
                entry = entry->getNext();
            }
            // check if we find the element
            if (entry->getKey() == key) {
                // the element is the head of the list
                if (prevEntry == NULL) {
                    LinkedHashEntry *nextEntry = entry->getNext();
                    delete entry;
                    table[hash] = nextEntry;
                } else {
                    // if not the head of the list
                    LinkedHashEntry *next = entry->getNext();
                    delete entry;
                    prevEntry->setNext(next);
                }
            }
        }
    }

    ~HashMap() 
    {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != NULL) {
                LinkedHashEntry *prevEntry = NULL;
                LinkedHashEntry *entry = table[i];
                // delete each entry in the chain
                while (entry != NULL) {
                    prevEntry = entry;
                    entry = entry->getNext();
                    delete prevEntry;
                }
            }
        }
        delete[] table;
    }
};

int main() 
{
    HashMap m;
    
    m.insert(1,100);
    m.insert(2,20);
    m.insert(3,333);
    cout << "m.find(3) = " 
         << m.find(3) << endl;

    cout << "m.find(1) = " 
         << m.find(1) << endl;

    m.insert(3,555);
    cout << "m.find(3) = " 
         << m.find(3) << endl;
         
    m.remove(3);
    cout << "m.find(3) = " 
         << m.find(3) << endl;

    return 0;
}