//
//  BitSwapRequired.cpp
//  
//  Created by 罗铮 on 04/05/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <iostream>

using namespace std;

int BitSwapRequired1(int a, int b) 
{
    int size = (int)sizeof(int), count = 0;
    for (int i = size * 8; i > 0; i--) {
        if ((a ^ b) & 1)
            count++;
        a >>= 1;
        b >>= 1;
    }
    return count;
}

int BitSwapRequired2(int a, int b) 
{
    int count = 0;
    for (int c = a ^ b; c != 0; c >>= 1) {
        count += c & 1;
    }

    return count;
}

int main()
{
    cout << BitSwapRequired1(31,14) << endl;
    cout << BitSwapRequired2(31,14) << endl;

    return 0;
}
