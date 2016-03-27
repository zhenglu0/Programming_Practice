//
//  BitSetCount.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>

using namespace std;

// Actually the arithmatic algorithm for converting
// binary and decimal is the same
void binary(unsigned int n)
{
    int upper = 255;
    for(int i = upper; i > 0; i = i/2) {
        if(n & i) 
            cout << " 1";
        else
            cout << " 0";
    }
    cout << endl;
}

/* O(n), where n is the size, in bits, of an integer */
int bitCountA(int n)
{
    int count = 0;
    while(n) {
        if(n & 1) 
            count++;
        n >>= 1;
    }
    return count;
}

/* O(m), where m is the number of 1's in the solution. 
   Every time we do n = n & (n-1)
   A 1 bit will disappear */
int bitCountB(int n)
{
    int count = 0;
    while(n) {
        n = n & (n-1);
        count++;
    }
    return count;
}


int main()
{
    int a;

    a = 250;
    binary(a);
    cout << "Bit count = " << bitCountA(a) << endl;

    a = 250;
    binary(a);
    cout << "Bit count = " << bitCountB(a) << endl;

    return 0;
}
