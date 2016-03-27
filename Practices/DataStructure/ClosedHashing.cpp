//
//  ClosedHashing.cpp
//  
//  Also means Open addressing hashing by linear probing
//  Modified by 罗铮 on 03/18/14.
//  http://www.algolist.net/Data_structures/Hash_table/Open_addressing

#include <iostream>

using namespace std;

const int TABLE_SIZE = 128;

class HashEntry {
private:
    int key;
    int value;
public:
    HashEntry(int key, int value) 
    {
        this->key = key;
        this->value = value;
    }

    int getKey() { return key; }

    int getValue() { return value; }

    void setValue(int value) { this->value = value; }
};
 
class DeletedEntry: public HashEntry {
private:
    static DeletedEntry *entry;
    DeletedEntry():HashEntry(-1, -1) {}
public:
    static DeletedEntry *getUniqueDeletedEntry() {
        if (entry == NULL)
            entry = new DeletedEntry();
        return entry;
    }
};
 
DeletedEntry *DeletedEntry::entry = NULL;
  
class HashMap {
private:
    HashEntry **table;
public:
    HashMap() 
    {
        table = new HashEntry*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }
 
    int find(int key) 
    {
        int hash = (key % TABLE_SIZE);
        int initialHash = -1;
        while (hash != initialHash && 
               (table[hash] == DeletedEntry::getUniqueDeletedEntry() || 
                (table[hash] != NULL && table[hash]->getKey() != key)
              )) {
            if (initialHash == -1)
                initialHash = hash;
            hash = (hash + 1) % TABLE_SIZE;
        }
        if (table[hash] == NULL || hash == initialHash)
            return -1;
        else
            return table[hash]->getValue();
    }
 
    void insert(int key, int value) 
    {
        int hash = (key % TABLE_SIZE);
        int initialHash = -1;
        int indexOfDeletedEntry = -1;
        while (hash != initialHash && 
               (table[hash] == DeletedEntry::getUniqueDeletedEntry() || 
                (table[hash] != NULL && table[hash]->getKey() != key)
              )) {
            if (initialHash == -1)
                initialHash = hash;
            if (table[hash] == DeletedEntry::getUniqueDeletedEntry())
                indexOfDeletedEntry = hash;
            hash = (hash + 1) % TABLE_SIZE;
        }
        if ((table[hash] == NULL || hash == initialHash) && 
             indexOfDeletedEntry != -1)
            table[indexOfDeletedEntry] = new HashEntry(key, value);
        else if (initialHash != hash) {
            if (table[hash] != DeletedEntry::getUniqueDeletedEntry() && 
                table[hash] != NULL && table[hash]->getKey() == key)
                table[hash]->setValue(value);
            else
                table[hash] = new HashEntry(key, value);
        }
              
    }

    void remove(int key) 
    {
        int hash = (key % TABLE_SIZE);
        int initialHash = -1;
        while (hash != initialHash && 
               (table[hash] == DeletedEntry::getUniqueDeletedEntry() || 
                (table[hash] != NULL && table[hash]->getKey() != key)
              )) {
            if (initialHash == -1)
                initialHash = hash;
            hash = (hash + 1) % TABLE_SIZE;
        }
        if (hash != initialHash && table[hash] != NULL) {
            delete table[hash];
            table[hash] = DeletedEntry::getUniqueDeletedEntry();
        }
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL && 
                table[i] != DeletedEntry::getUniqueDeletedEntry())
                delete table[i];
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
