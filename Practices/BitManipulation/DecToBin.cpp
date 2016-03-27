//
//  DecToBin.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>
#include <iomanip>
#include <bitset>
#include <climits>

using namespace std; 
 
void binary_bit(unsigned int u) 
{ 
    int upper;
    if(u < 256)
        upper = 128;
    else
        upper = 32768;

    cout << setw(5) << u << ": ";

    // check if bit is set starting from the highest bit
    // (ex) upper = 128, 10000000, 01000000, 00100000, ..., 00000001

    for(int i = upper; i > 0; i = i/2) {
        if(u & i) 
            cout << "1 "; 
        else 
            cout << "0 "; 
    }
    cout << "\n"; 
}

// This method can be used to calculate  
// any number representation 
void binary_count(int n)
{
    cout << n << ": ";
    char s[100];
    int i = 0;
    while(n > 0) {
        if(n % 2 == 0 ) 
            s[i++] = '0';
        else
            s[i++] = '1';
        n = n /2;
    }
    s[i] = '\0';
    string r = string(s);
    r = string ( r.rbegin(), r.rend() );
    cout << r << endl;
}

void binary_bitSet(unsigned int u) 
{ 
    cout << setw(5) << u << ": ";
    cout << bitset<16>((int)u);
    cout << "\n"; 
}

int main() 
{
    binary_bit(5);
    binary_bit(55);
    binary_bit(255);

    binary_count(5);
    binary_count(55);
    binary_count(255); 

    binary_bitSet(5);
    binary_bitSet(55);
    binary_bitSet(255); 

    //const int CHAR_BIT = 8;
    const int BITS = sizeof(int)*CHAR_BIT;

    cout << "BITS = " << BITS << endl; 

    int n = 23;

    // using bitset
    bitset<BITS> m(n);     // or m = n
    cout << m << endl;

    // using right shift
    for(int i = BITS-1; i >= 0; i--) {
        cout << ((n >> i) & 1 );
    }
    
    cout << endl;

    return 0;
}
