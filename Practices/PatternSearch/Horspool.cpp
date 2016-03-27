//
//  Horspool.cpp
//  
//  Created by 罗铮 on 03/24/14.
//
/*  Program for Horspool Matching Algorithm */
 
#include <climits>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std; 

#define NO_OF_CHARS 256

void printTable(int *table)
{
    for (int i = 0; i < NO_OF_CHARS; ++i) {
        cout << "T[" << i << "] = " << table[i] << endl;
    }
}

int* shiftTable(char *p)
{
    int m = strlen(p);
    int *table = new int [NO_OF_CHARS];

    for (int i = 0; i < NO_OF_CHARS; i++)
        table[i] = m;

    for (int j = 0; j < m -1 ; j++)
        table[(size_t)p[j]] = m - 1- j;

    return table;
}
 
int horspoolMatching(char *p, char *t)
{
    int m = strlen(p);
    int n = strlen(t);

    int *table = shiftTable(p); // Generate table of shifts
    //printTable(table);
    int i = m - 1; // Position of the pattern's right end
    while (i <= n-1) {
        int k = 0; // Number of matched characters
        while (k <= m-1 && p[m-1-k] == t[i-k])
            k++;
        if (k == m)
            return i - m + 1;
        else
            i = i + table[(size_t)t[i]];
    }
    delete [] table;
    return -1;
}
 
/* Driver program to test above funtion */
int main()
{
    char t[] = "JIM_SAW_ME_IN_A_BARBERSHOP";
    char p[] = "BARBER";
    
    int index = horspoolMatching(p, t);
    
    printf("pattern occurs at shift = %d\n", index);

    return 0;
}