//
//  RobotCoinCollection.cpp
//  
//  Created by 罗铮 on 03/09/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int n = 5, m = 6;

int c[5][6] = { {0,0,0,0,1,0},
				{0,1,0,1,0,0},
				{0,0,0,1,0,1},
				{0,0,1,0,0,1},
				{1,0,0,0,1,0} };

int f[5][6]; // The table used for storing dp result

int robotCoinCollection_topdown(int n, int m) 
{
	if (n == 0)
		return c[0][m];
	if (m == 0)
		return c[0][n];
	
	return max (robotCoinCollection_topdown(n-1,m),
				robotCoinCollection_topdown(n, m-1)) + c[n][m];
}

int robotCoinCollection_bottomup(int n, int m) 
{
	// Initialize the base case for the table
	f[0][0] = c[0][0];
	for (int j = 1; j <= m; j++) {
		f[0][j] = f[0][j-1] + c[0][j];
	}
	// do the dynamic programming
	for (int i = 1; i <= n; i++) {
		f[i][0] = f[i-1][0] + c[i][0];		
		for (int j = 1; j <= m; j++) {
			f[i][j] = max(f[i-1][j],f[i][j-1]) + c[i][j];
		}
	}
	return f[n][m];
}

void robotCoinCollection(int i, int j, int &max_sum, vector<int> &v)
{
	v.push_back(c[i][j]);
	
	if (i == n-1 && j == m-1) {
		int sum = 0;
		for (size_t k = 0; k < v.size(); ++k)
			sum += v[k] ;

		max_sum = max(max_sum, sum);
	}
	
	if (i < n)
		robotCoinCollection(i+1,j,max_sum,v);
	if (j < m)
		robotCoinCollection(i,j+1,max_sum,v);

	v.pop_back();
}

int robotCoinCollection_traversal()
{
	vector<int> v;
	int max_sum = 0;
	robotCoinCollection(0,0,max_sum,v);
	return max_sum;
}

int main(int argc, char* argv[])
{
	cout << "robotCoinCollection_topdown   = " << 
			robotCoinCollection_topdown(4,5)  << endl;
	cout << "robotCoinCollection_bottomup  = " << 
			robotCoinCollection_bottomup(4,5)  << endl;
	cout << "robotCoinCollection_traversal  = " << 
			robotCoinCollection_traversal()  << endl;

	return 0;
}

