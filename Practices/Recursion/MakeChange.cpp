//
//  MakeChange.cpp
//  
//  Created by 罗铮 on 11/30/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <vector>
#include <iostream>

using namespace std;

//
// 1. only return the total number of ways 
int MakeChange1(int n, int d)
{
    int nextD = 0;
    
    if (n == 0)
        return  1;

    if (d == 5)
        nextD = 2;
    else if (d == 2)
        nextD = 1;
    else
        return 1;
    
    int ways = 0;
    
    for (int i = 0; i * d <= n; i++)
        ways += MakeChange1(n - i * d, nextD);
    
    return ways;
}


//
// 2. returns the number of ways and print the combination
int DoMakeChange(int n, int d, vector<int> &v)
{
    int nextD = 0;
        
    if (d == 5)
        nextD = 2;
    else if (d == 2)
        nextD = 1;
    else
    {
        cout << "# of 5 is " << v[0] <<
                " ,# of 2 is " << v[1] <<
                " ,# of 1 is " << n << endl;
        return 1;
    }
    
    int ways = 0;
    
    for (int i = 0; i * d <= n; i++)
    {
        v.push_back(i);
        ways += DoMakeChange(n - i * d, nextD,v);
        v.pop_back();
    }
    
    
    return ways;
}

int MakeChange2(int n)
{
    vector<int> v;
    
    return DoMakeChange(n, 5, v);
}


int main(int argc, const char * argv[])
{

    cout << "The number of changes we can "
            "make by using 5,2,1 to change 10 is "
         << MakeChange1(10,5) << endl << endl;
    
    int ways = MakeChange2(10);
    cout << endl << "The number of changes we can "
         "make by using 5,2,1 to change 10 is "
         << ways << endl;
    
    return 0;
}

