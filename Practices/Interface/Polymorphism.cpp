//
//  Polymorphism.cpp
//  
//  Created by 罗铮 on 05/16/14.
//  Copyright (c) 2014 罗铮. All rights reserved.
//
//  This Program show thes order of the constructor and destructor

#include <iostream>

using namespace std;

class C
{
public:
	C() { cout << "C()"  << endl; }
	~C(){ cout << "~C()" << endl; }
};

class A
{
public:
	A() { cout << "A()"  << endl; }
	~A(){ cout << "~A()" << endl; }
};

class B : public A
{
public:	
	B() { cout << "B()"  << endl; }
	~B(){ cout << "~B()" << endl; }
private:
	C c;
};

class D : public B
{
public:
	D() { cout << "D()"  << endl; }
	~D(){ cout << "~D()" << endl; }
private:
	C c;
};

int main()
{
	cout << "------" << endl;
	A *a = new A();
	delete a;

	cout << "------" << endl;
	B *b = new B();
	delete b;

	cout << "------" << endl;
	D *d = new D();
	delete d;
	cout << "------" << endl;

    return 0;
}