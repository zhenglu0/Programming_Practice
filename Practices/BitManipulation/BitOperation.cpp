//
//  BitOperation.cpp
//  
//  Created by 罗铮 on 11/30/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

// expre_Shift_Operators.cpp
// compile with: /EHsc
// Demonstrate shift operators

/*
 The bitwise shift operators are:
 
 Right shift (>>)
 
 Left shift (<<)
 
 These binary operators have left-to-right associativity.
 
 Both operands of the shift operators must be of integral types.
 Integral promotions are performed according to the rules described in Integral Promotions.
 The type of the result is the same as the type of the left operand. The value of a right-shift expression e1 >> e2 is e1 / 2e2,
 and the value of a left-shift expression e1 << e2 is e1 * 2e2.
 
 The results are undefined if the right operand of a shift expression is negative or if the right operand is greater than or equal to
 the number of bits in the (promoted) left operand.
 
 The left shift operator causes the bit pattern in the first operand to be shifted left the number of bits specified by
 the second operand. Bits vacated by the shift operation are zero-filled. This is a logical shift, as opposed to a
 shift-and-rotate operation.
 
 The right shift operator causes the bit pattern in the first operand to be shifted right the number
 of bits specified by the second operand. Bits vacated by the shift operation are zero-filled for unsigned quantities.
 For signed quantities, the sign bit is propagated into the vacated bit positions. The shift is a logical shift if the left operand
 is an unsigned quantity; otherwise, it is an arithmetic shift.
 
 Operator Keyword for &
 
 The bitand operator is the text equivalent of &. There are two ways to access the bitand operator in your programs: include the header file iso646.h, or compile with the /Za (Disable language extensions) compiler option.
 
 */

#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    cout << "5 times 2 is " << (5 << 1) << endl;
    cout << "20 divided by 4 is " << (20 >> 2) << endl << endl;;
    
    unsigned short a = 0xFFFF;      // pattern 1111 ...
    unsigned short b = 0xAAAA;      // pattern 1010 ...
    unsigned short c = 0;
    unsigned short d = 1;
    int i1 = 5;
    int i2 = 4;
    
    cout  << hex << ( a & b ) << endl;   // prints "aaaa", pattern 1010 ...
    cout  << hex << ( b & c ) << endl;
    cout  << hex << ( b & d ) << endl << endl;;
    
    cout  << hex << ( i1 & d ) << endl;
    cout  << hex << ( i2 & d ) << endl;

    return 0;
}


