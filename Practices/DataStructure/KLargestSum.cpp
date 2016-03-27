//
//  KLargestSum.cpp
//  
//  Created by 罗铮 on 5/12/14.
//  Copyright (c) 2014 罗铮. All rights reserved.
//
//  http://stackoverflow.com/questions/5212037/
//  find-the-pair-across-2-arrays-with-kth-largest-sum

/*
    That can be easily done in O(k*logk). 
    I'll only assume arrays are sorted in descending order, 
    to simplify notation.

    The idea is simple. We'll find 1st, 2nd, .., k-th maximum values 
    one by one. But to even consider pair (i, j) we need to have both
    (i-1, j) and (i, j-1) already selected, because they both are 
    greater or equal than (i, j).

    It's much like if we push all n*m pairs into the heap and then
    remove max k times. Only we don't need all n*m pairs.

    heap.add(pair(0, 0));  // biggest pair

    // remove max k-1 times
    for (int i = 0; i < k - 1; ++i) {
        // get max and remove it from the heap
        max = heap.popMax();

        // add next candidates
        heap.add(pair(max.i + 1, max.j));
        heap.add(pair(max.i, max.j + 1));
    }

    // get k-th maximum element
    max = heap.popMax();
    maxVal = a[max.i] + b[max.j];
    Some things to consider.

    Duplicated pairs can be added to the heap, 
    this can be prevented with hash.
    Indexes need to be validated, 
    e.g. that max.i + 1 < a.length.
*/

#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <algorithm>      // std::make_heap, std::pop_heap, std::push_heap
#include <utility>        // std::pair
#include <unordered_set>  // hash table
#include <string>         // std::string, std::to_string

using namespace std;

struct index_pair {
    int i, j;
    int *a, *b;
    index_pair(){};
    index_pair(int x, int y, int *m, int *n)
    :i(x),j(y),a(m),b(n){};
};

class mycomparison {
public:
    mycomparison(const bool& revparam = false) 
    {
        reverse = revparam;
    }
    bool operator() (const index_pair &lhs, const index_pair &rhs) const
    {
        if (reverse) 
            return ( lhs.a[lhs.i] + lhs.b[lhs.j] > 
                     rhs.a[rhs.i] + rhs.b[rhs.j] );
        else 
            return ( lhs.a[lhs.i] + lhs.b[lhs.j] < 
                     rhs.a[rhs.i] + rhs.b[rhs.j] );
    }
private:
    bool reverse;
};

int KLargestSum (int *a, int *b, int size, int k)
{
    // Used as a hash table to store pairs
    unordered_set<string> s;
    // Like a max heap, using mycomparison:
    typedef priority_queue<index_pair,
                vector<index_pair>,mycomparison> mypq_type;

    // greater-than comparison
    mypq_type pq;

    // push first element to the queue
    index_pair max = index_pair(0, 0, a, b);
    pq.push(max);

    // insert pair to hash table
    string pair_str = to_string(0) + "," + to_string(0);
    s.insert(pair_str);

    while (k > 0)
    {
        // get max and remove it from the heap
        max = pq.top();
        cout << "max.i = " << max.i << " max.j = " << max.j 
             << " sum = " << a[max.i] + b[max.j] << endl;
        pq.pop();

        // If the pair is not in the table add next candidates
        pair_str = to_string(max.i+1) + "," + to_string(max.j);
        if (s.find(pair_str) == s.end())
            pq.push( index_pair(max.i+1, max.j, a, b) );
        
        pair_str = to_string(max.i) + "," + to_string(max.j+1);
        if (s.find(pair_str) == s.end())
            pq.push( index_pair(max.i, max.j+1, a, b) );

        k--;
    }

    return a[max.i] + b[max.j];
}

int main(int argc, const char * argv[])
{
    int a[] = {10, 5, 3, 1};
    int b[] = {8,  6, 3, 2};
    
    int size = sizeof(a) / sizeof(int);
    int k = 4;

    cout << KLargestSum(a,b,size,k) << endl;

    return 0;
}
