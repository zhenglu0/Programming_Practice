//
//  PrintAllSubset.cpp
//  
//  Created by 罗铮 on 3/8/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 1. use the recursive algorithm
// 
void print_all_subset_internal(const int numbers[], const size_t size, 
                               const int begin_index, int print[])
{
    if ( begin_index == (int)size )
    {
        for ( unsigned i = 0; i < size; i ++ )
        {
            if ( print[i] ) 
                cout << numbers[i] << " ";
        }
        cout << endl;
        return;
    }
    print[begin_index] = 1;
    print_all_subset_internal(numbers, size, begin_index + 1, print);
    print[begin_index] = 0;
    print_all_subset_internal(numbers, size, begin_index + 1, print);
}

void print_all_subset(const int numbers[], const size_t size)
{
    vector<int> print;
    print.resize(size);
    print_all_subset_internal(numbers, size, 0, &print[0]);
}

// 2. use the bit shift
//  
void PrintSubsets() 
{ 
    int source[3] = {1,2,3}; 
    int currentSubset = 8; 
    int tmp; 
    while(currentSubset) 
    { 
        cout << "("; 
        tmp = currentSubset; 
        for(int i = 0; i < 3; i++) 
        { 
            if (tmp & 1) 
                cout << source[i]; 
            tmp >>= 1; 
        } 
        cout << ")" << endl; 
        currentSubset--; 
    } 
}

int main(int argc, const char * argv[])
{
    int test[] = {1,2,3};

    cout << "Recursive Solution:" << endl;
    print_all_subset(test, 3);

    cout << "Non-Recursive Solution:" << endl;
    PrintSubsets();

    return 0;
}

