//
//  CoinRow.cpp
//  
//  Created by 罗铮 on 03/09/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <algorithm>    // std::max

using namespace std;

int c[]  = {0,5,1,2,10,6,2};
int f[7] = {0}; 

int coinRow_topdown(int n) 
{
	if (n == 1)
		return c[1];
	if (n == 2)
		return max(c[1],c[2]);
	
	return max(coinRow_topdown(n-1),
			   coinRow_topdown(n-2) + c[n]);
}

int coinRow_bottomup(int n) 
{
	f[1] = c[1];
	f[2] = max(c[1],c[2]);

	if (n == 1) 
		return c[1];
	if (n == 2)
		return f[2];

	for (int i = 1; i <= n; ++i)
		f[i] = max(c[i] + f[i-2], f[i-1]);

	return f[n];
}

int main(int argc, char * argv[])
{
	cout << "coinRow_topdown  = "
		 << coinRow_topdown(6)  << endl;
	cout << "coinRow_bottomup = "
		 << coinRow_bottomup(6) << endl;

    return 0;
}


