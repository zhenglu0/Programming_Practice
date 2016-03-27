//
//  CheckEndian.cpp
//  
//  Modified by 罗铮 on 04/10/14.

/*  If the dereferenced pointer is 1, the machine is little-endian 
    otherwise the machine is big-endian */

//  Think about the different types of pointer casting here

/*
    Static_cast can perform conversions between pointers to related 
    classes, not only upcasts (from pointer-to-derived to 
    pointer-to-base), but also downcasts (from pointer-to-base to 
    pointer-to-derived). No checks are performed during runtime to 
    guarantee that the object being converted is in fact a full 
    object of the destination type. Therefore, it is up to the 
    programmer to ensure that the conversion is safe. On the other 
    side, it does not incur the overhead of the type-safety checks 
    of dynamic_cast.
*/

/*
    Dynamic_cast can only be used with pointers and references to 
    classes (or with void*). Its purpose is to ensure that the 
    result of the type conversion points to a valid complete object
    of the destination pointer type.

    This naturally includes pointer upcast (converting from 
    pointer-to-derived to pointer-to-base), 
    in the same way as allowed as an implicit conversion.

    But dynamic_cast can also downcast (convert from pointer-to-base
    to pointer-to-derived) polymorphic classes (those with virtual 
    members) if -and only if- the pointed object is a valid 
    complete object of the target type. 
*/

/*
    Reinterpret_cast converts any pointer type to any other pointer 
    type, even of unrelated classes. The operation result is a simple 
    binary copy of the value from one pointer to the other. 
    All pointer conversions are allowed: neither the content pointed 
    nor the pointer type itself is checked.

    It can also cast pointers to or from integer types. The format 
    in which this integer value represents a pointer is platform-
    specific. The only guarantee is that a pointer cast to an integer 
    type large enough to fully contain it (such as intptr_t), 
    is guaranteed to be able to be cast back to a valid pointer.

    The conversions that can be performed by reinterpret_cast 
    but not by static_cast are low-level operations based on 
    reinterpreting the binary representations of the types, 
    which on most cases results in code which is system-specific, 
    and thus non-portable.
*/

#include <iostream>

using namespace std;

int check_endian() 
{
    int one = 1;
    char *ptr = reinterpret_cast<char *>(&one);
    return *ptr;
}

int main()
{
    if(check_endian()) 
        cout << "little endian\n";
    else
        cout << "big endian\n";

    return 0;
}
