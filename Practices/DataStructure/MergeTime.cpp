//
//  MergeTime.cpp
//  
//  Created by 罗铮 on 2/1/13.
//  Copyright (c) 2013 罗铮. All rights reserved.
//  
//  Always merge the smallest time array first,
//  this greedy method leads to optionmal solution
//  
//  http://en.cppreference.com/w/cpp/container/priority_queue

/*
    A priority queue is a data structure that stores priorities 
    (comparable values) and perhaps associated information. A priority 
    queue supports inserting new priorities, and removing/retrning the 
    highest priority. When a priority queue is implemented using a heap,
    the worst-case times for both insert and removeMax are logarithmic 
    in the number of values in the priority queue.
*/

#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <algorithm>      // std::make_heap, std::pop_heap, std::push_heap

using namespace std;

bool comp(const int& a, const int& b)
{
    return (a < b) ? false : true;
}


// #1. We can sort the array into heap
int min_merge_time_heap ( vector<int> &A ) 
{
    
    if (A.empty())
        return 0;
    // build a min heap
    make_heap (A.begin(),A.end(),comp);
    
    if(A.size() == 1)
        return A[0];
    
    int totalTime = 0;
    
    while(A.size() >= 2) {
        
        // pop two elements from heap
        pop_heap (A.begin(),A.end(),comp);
        int temp1 = A.back();
        A.pop_back();
        pop_heap (A.begin(),A.end(),comp);
        int temp2 = A.back();
        A.pop_back();
        
        int total = temp1 + temp2;
        A.push_back(total);
        push_heap (A.begin(),A.end(),comp);
        
        totalTime = total;
    }
    
    return totalTime;
}

//#2. we can use the c++ priority queue
int min_merge_time_pq (int *a, int size)
{
    
    if (size == 0)
        return 0;

    // build a priority queue
    priority_queue<int> A (a,a+size);
    
    if(A.size() == 1)
        return A.top();
    
    int totalTime = 0;
    
    while(A.size() >= 2) {
        
        // pop two elements from heap
        int temp1 = A.top();
        A.pop();
        int temp2 = A.top();
        A.pop();
        
        // add them
        int temp_total = temp1 + temp2;
        A.push(temp_total);
        
        totalTime = temp_total;
    }
    
    return totalTime;
}

int main(int argc, const char * argv[])
{
    int a[] = {11, 5, 3, 2};
    int size = sizeof(a) / sizeof(int);
    
    vector <int > v(a, a + size);
    cout << min_merge_time_heap(v) << endl;
    
    cout << min_merge_time_pq(a,size) << endl;

    return 0;
}

