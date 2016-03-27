//
//  Singleton.cpp
//  
//  Modified by 罗铮 on 04/06/14.
//  From the Cracking The Coding Interview
/*
	Implement a singleton design pattern as a template such that,
	for any given class Foo, you can call Singleton::instance() 
	and get a pointer to an instance of a singleton of type Foo
	Assume the existence of a class Lock which has acquire() and
	release() methods.

	How could you make your implementation 
	thread safe and exception safe?

	The general method to make a program thread safe is to lock
	shared resources whenever write permission is given This way,
	if one thread is modifying the resource, other threads can 
	not modify it
*/

#include <iostream>

using namespace std;

/* Place holder for thread synchronization lock */ 
class Lock {
public:
	Lock() { /* placeholder code to create the lock */ } 
	~Lock() { /* placeholder code to deallocate the lock */ } 
	void AcquireLock() { /* placeholder to acquire the lock */ } 
	void ReleaseLock() { /* placeholder to release the lock */ }
};

/* 	Singleton class with a method that creates a new instance of 
	the * class of the type of the passed in template if it does not
	already exist. */
template <class T> 
class Singleton { 
private:
	static Lock lock;
	static T* object;
	Singleton() {}; 

public:
	static T * instance(); 
};

template <typename T>
Lock Singleton<T>::lock;

template <typename T>
T *Singleton<T>::object = 0;

template <typename T>
T *Singleton<T>::instance() 
{
	// If object is not initialized, acquire lock
	if (object == 0) {
		lock.AcquireLock();
		// If two threads simultaneously check and pass the first “if”
		// condition, then only the one who acquired the lock first
		// should create the instance  
		if (object == 0) 
			object = new T(); 
		lock.ReleaseLock(); 
	}
	return object;
}

class Foo {
public:
	Foo() {cout << "Foo()" << endl;};
	void hello() {cout << "hello" << endl;};
};

int main() 
{
	/* foo is any class defined for which we want singleton access */ 
	Foo* singleton_foo = Singleton<Foo>::instance();
	singleton_foo->hello();
	// singleton will be constructed only once
	Foo* singleton_foo2 = Singleton<Foo>::instance();
	singleton_foo2->hello();

	return 0;
}
