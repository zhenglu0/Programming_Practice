//
//  FindMax.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>

using namespace std;

int getSignBit(int n)
{
    int sign = (n >> 31) & 0x01;;
    return sign;
}

// returns the maximum 
// without using any comparison and if/else statements
int getMax(int a, int b)
{
    int signa, signb;
    
    // a >= b : signa = 1, signb = 0;
    // a < b : signa = 0, signb = 1;
    signb = getSignBit(a-b);
    signa = signb ^ 1;
    return signa*a + signb*b;
}

int main()
{
    int m = 215, n = 250;
    cout << getMax(m,n) << endl;

    return 0;
}
