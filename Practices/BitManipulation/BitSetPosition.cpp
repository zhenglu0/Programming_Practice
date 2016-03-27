//
//  BitSetPosition.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>

using namespace std;

void binary(int n)
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

int bitCount(int n)
{
    int count = 0;
    while(n) {
        if(n & 1)
            count++;
        n >>= 1;
    }
    return count;
}

void bitSetPos(int n, int a[])
{
    int ic = 0;
    for(int i = 0; i < 32; i++) {
        if(n & 1) 
            a[ic++] = i;
        n >>= 1;
    }
}

int main()
{
    int num = 100;
    int nbit;
    int *a;

    /* get bit count */
    nbit = bitCount(num);
    /* array to store the bit set postion */
    a = new int[nbit];
    /* display the integer in bits */
    binary(num);
    /* get the position of bit set */
    bitSetPos(num,a);

    cout << "bit set position " << endl;
    for(int i = 0; i < nbit; i++)
        cout << a[i] << " ";

    cout << endl;
    
    delete [] a;
    return 0;
}
