//
//  UnAndsignedInt.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <iostream>

using namespace std;

int main()
{
    signed char k = 0;
    cout << static_cast<signed int>(k) << " ";

    while(++k) 
        cout << static_cast<signed int>(k) << " ";

    cout << endl << endl;

    unsigned char uk = 0;
    cout << static_cast<signed int>(uk) << " ";
    while(++uk) 
        cout << static_cast<signed int>(uk) << " ";

	cout << endl << endl;

    return 0;
}
