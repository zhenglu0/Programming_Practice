//
//  DecToHex.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>
#include <climits>

using namespace std;

/* hex with leading zeros */
void decToHex(int n)
{
    //const int CHAR_BIT = 8;
    const int NIBBLES = sizeof(int)*CHAR_BIT / 4;
    cout << "NIBBLES = " << NIBBLES << endl;
    char hexString[] = "0123456789ABCDEF";

    cout << "decimal: " << n << endl;        
    cout << "hex        : ";
    
    for (int i = NIBBLES - 1; i >= 0; i--)
        cout << hexString[(n >> i*4) & 0xF];

    cout << endl << endl;
}

int main() 
{
    decToHex(10);
    decToHex(100);
    decToHex(1000);

    // for 1000, it will print out 0x3e8
    cout << showbase << hex << 1000 << endl;

    return 0;
}
