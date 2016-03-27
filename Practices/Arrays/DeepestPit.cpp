//
//  DeepestPit.cpp
//
//  Created by 罗铮 on 2/1/13.
//  Copyright (c) 2013 罗铮. All rights reserved.
//  http://stackoverflow.com/questions/12329711/interview-test-deepest-pit

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int deepest_pit ( const vector<int> &A ) {
    
    int depth = 0;
    int P = 0, Q = -1, R = -1;
    
    for (size_t i = 1; i < A.size(); i++) {
        
        if (Q < 0 && A[i] >= A[i-1])
            Q = i-1;
        
        if ((Q >= 0 && R < 0) && 
            (A[i] <= A[i-1] || i + 1 == A.size())) {
            R = i-1;
            // compare with the previous depth
            depth = max(depth, min(A[P]-A[Q], A[R]-A[Q]));
            // update the index
            P = i - 1;
            Q = R = -1;
        }
    }
    
    if (depth == 0)
        depth = -1;
    
    return depth;
}

int main(int argc, const char * argv[])
{

    int A[] = {0,1,3,-2,0,1,0,-3,2,3};
    vector<int> v(A, A + sizeof(A) / sizeof(int));
    cout << deepest_pit(v);
    return 0;
}

