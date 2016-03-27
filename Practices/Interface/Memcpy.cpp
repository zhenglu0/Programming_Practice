//
//  Memcpy.cpp
//  
//  Created by 罗铮 on 04/18/14.
//  http://www.cplusplus.com/reference/cstring/memcpy/
//  
//  C++ program for implementation of memory copy

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

#include <cstdio>
#include <cstring>

struct Person {
	char name[40];
	int age;
};

void my_memcpy_original (void* destination, const void* source, size_t num)
{
	size_t counter = 0;
	while (counter < num) {
		*((char*)destination + counter) = *((char*)source + counter);
		counter++;
	}
}

void my_memcpy_revised (void* destination, const void* source, size_t num)
{
	char *d = static_cast<char *>(destination);
	const char *s = static_cast<const char *>(source);

	for (size_t i = 0; i < num; i++)
		d[i] = s[i];
}

int main ()
{
	Person person, person_copy, my_person, my_person_copy;
	char myname[] = "Pierre de Fermat";

	//#1. C stdlib function
	/* using memcpy to copy string: */
	memcpy ( person.name, myname, strlen(myname)+1 );
	person.age = 46;

	/* using memcpy to copy structure: */
	memcpy ( &person_copy, &person, sizeof(person) );

	printf ("person_copy: %s, %d \n", person_copy.name, person_copy.age );

	//#2. my own function
	/* using memcpy to copy string: */
	my_memcpy_original ( my_person.name, myname, strlen(myname)+1 );
	my_person.age = 46;

	/* using memcpy to copy structure: */
	my_memcpy_revised ( &my_person_copy, &my_person, sizeof(person) );

	printf ("my_person_copy: %s, %d \n",
            my_person_copy.name, my_person_copy.age );

  	return 0;
}

