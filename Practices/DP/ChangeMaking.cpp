//
//  changeMaking.cpp
//  
//  Created by 罗铮 on 03/09/14.
//  Copyright (c) 2014 罗铮. All rights reserved.


#include <iostream>
#include <algorithm>    // std::max
#include <limits>       // std::numeric_limits

using namespace std;

//int d[]  = {0,1,3,4};
int d[]  = {0,1,5,10};

int d_s = 3; // size of the array d
int f[7] = {0}; 


int changeMaking_topdown (int n) 
{
	if (n == 0) return 0;
	
	int f_m = numeric_limits<int>::max();
	int j = 1;

	while (n >= d[j] && j <= d_s) {
		f_m = min(f_m, changeMaking_topdown(n-d[j]));
		j++;
	}

	return f_m+1;
}

int changeMaking_bottomup (int n) 
{
	for (int i = 1; i <= n; i++) {
		int temp = numeric_limits<int>::max();
		int j = 1;
		while (j <= d_s && i >= d[j]) {
			temp = min(f[i - d[j]], temp);
			j++;
		}
		f[i] = temp + 1;
	}

	return f[n];
}

int changeMaking_greedy (int n) 
{
	int count = 0;
	for (int i = d_s; i > 0 ; i--) {
		while (n >= d[i]) {
			n -= d[i];
			count++;
		}
		i--;
	}
	return count;
}

int main(int argc, char * argv[])
{
	cout << "changeMaking_topdown  = " << 
		 changeMaking_topdown(6)  << endl;
	cout << "changeMaking_bottomup = " << 
		 changeMaking_bottomup(6) << endl;
	cout << "changeMaking_greedy = " << 
		 changeMaking_bottomup(6) << endl;

	cout << "changeMaking_bottomup = " << 
		 changeMaking_bottomup(99) << endl;
	cout << "changeMaking_greedy = " << 
		 changeMaking_bottomup(99) << endl;

    return 0;
}


