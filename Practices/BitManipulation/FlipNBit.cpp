//
//  FlipNBit.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>
#include <iomanip>

using namespace std; 
 
void binary(unsigned int u) 
{ 
    int upper;
    if(u < 256)
        upper = 128;
    else
        upper = 32768;

    cout << setw(5) << u << ": ";
    for(int i = upper; i > 0; i = i/2) {
        if(u & i) 
            cout << "1 "; 
        else 
            cout << "0 "; 
    }
    cout << "\n"; 
}

void bit_flip(int& m, int nth)
{
    m ^= 1 << nth;
}

int main() 
{
    int m = 12;
    int nth = 2;
    binary(m);
    cout << "     flip " << nth << "th bit of " << m << endl;
    bit_flip(m,nth);
    binary(m);
    cout << endl;

    m = 63;
    nth = 6;
    binary(m);
    cout << "     flip " << nth << "th bit of " << m << endl;
    bit_flip(m,nth);
    binary(m);

    return 0;
}
