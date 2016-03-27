//
//  SwapsTwoInts.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>

using namespace std;

void inplace_swap_A(int &a, int &b)
{
    a = b - a;
    b = b - a;
    a = a + b;
}

// Using xor property: a^b^b => a
void inplace_swap_B(int &a, int &b)
{
    a = a ^ b;// a holds a_old ^ b_old
    b = a ^ b;// b holds a_old which is (a_old ^ b_old) ^ b_old
    a = a ^ b;// this line means a <--    (a_old ^ b_old) ^ a_old 
    // since b holds a_old.
    // So, as a result, a gets the value of b_old.
}

int main()
{
    int a = 10, b = 20;
    cout << "init values:    a = " << a << " b = " << b << endl;

    inplace_swap_A(a,b);
    cout << "swap A:    a = " << a << " b = " << b << endl;

    a = 100, b = 200;
    cout << "init values:    a = " << a << " b = " << b << endl;

    inplace_swap_B(a,b);
    cout << "swap B:    a = " << a << " b = " << b << endl;

    return 0;
}
