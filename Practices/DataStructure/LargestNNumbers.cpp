//
//  LargestNNumbers.cpp
//  
//  Created by 罗铮 on 3/12/14.
//  Copyright (c) 2014 罗铮. All rights reserved.
//  
//  http://en.cppreference.com/w/cpp/container/priority_queue

#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <algorithm>      // std::make_heap, std::pop_heap, std::push_heap

using namespace std;

// build for max heap
bool comp(const int& a, const int& b)
{
    return (a < b) ? true : false;
}

vector<int> 
largestNNumbers_heap (int *a , int size, int n) 
{
    vector <int> A(a, a + size);
    vector <int> v;

    if (A.empty())
        return v;

    // build a max heap
    make_heap (A.begin(),A.end(),comp);
    
    int max;

    while(n > 0) {
        pop_heap (A.begin(),A.end());
        max = A.back();
        A.pop_back();    
        v.push_back(max);
        n--;
    }

    return v;
}

vector<int> 
largestNNumbers_pq (int *a , int size, int n) 
{
    priority_queue <int, vector<int>, less<int> >
                   A (a,a + size);
    vector <int> v;

    if (A.empty())
        return v;
    
    int max;

    while(n > 0) {
        max = A.top();
        A.pop();    
        v.push_back(max);
        n--;
    }

    return v;
}

/*
    Or we can use the randomized selectd to
    find the median of the array
*/

// The swap function
inline void exchange(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Partitioning the array
int Partition(int A[], int p, int r)
{
    int x =  A[r];
    int i = p-1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x){
            i++;
            exchange(A[i], A[j]);
        }
    }
    exchange(A[i+1], A[r]);
    return i+1;
}

int Ramdomized_Partition(int A[], int p, int r)
{
    int i = p + rand()%(r-p);
    exchange(A[r], A[i]);
    return Partition(A, p, r);
}

// Randomized Select
int Ramdomized_Select(int A[],int p, int r, int i)
{
    if (p == r)
        return A[p];
    
    int q = Ramdomized_Partition(A, p, r);
    int k = q - p + 1;

    if (i == k)
        return A[q];
    else if (i < k)
        return Ramdomized_Select(A, p, q-1, i);
    else
        return Ramdomized_Select(A, q+1, r, i-k);
}

int main(int argc, const char * argv[])
{

    int a[] = {4,3,2,1,20,100,88,
               5,6,7,8,11,12,15,14,13,9,0,10};
    int n = 5, size = sizeof(a)/sizeof(int);

    // #1
    // Find the largest n numbers, by using heap
    vector <int > r = largestNNumbers_heap(a,size,n);

    for (size_t i = 0; i < r.size(); ++i)
        cout << r[i] << " ";
    cout << endl;

    r = largestNNumbers_pq(a,size,n);

    for (size_t i = 0; i < r.size(); ++i)
        cout << r[i] << " ";
    cout << endl;

    // #2
    // Find the largest n numbers, by using select 
    int index = Ramdomized_Select(a,0,size-1,size-n+1);
    int element = a[index];
    vector <int > s;
    
    for (int i = 0; i < size; ++i) {
        if (a[i] >= element)
            s.push_back(a[i]);   
    }

    for (size_t i = 0; i < s.size(); ++i)
        cout << s[i] << " ";
    cout << endl;

    return 0;
}

