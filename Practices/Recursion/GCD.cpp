//
//  GCD.cpp
//  
//  Created by 罗铮 on 03/09/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <iostream>

using namespace std;

int gcd (int m, int n) 
{
	if (n == 0)
		return m;
	
	return gcd (n, m % n);
}

int Euclid (int m, int n) 
{
	while (n != 0) {
		int r = m % n;
		m = n;
		n = r;
	}
	return m;
}

int main(int argc, char * argv[])
{
	int m = 120, n = 24;
	
	cout << "gcd( "<< m << "," << n << ") = " 
		 << gcd(m,n) << endl;

	cout << "Euclid( "<< m << "," << n << ") = " 
		 << Euclid(m,n) << endl;

    return 0;
}


