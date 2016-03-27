//
//  Knapsack.cpp
//  
//  Created by 罗铮 on 03/09/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <iostream>
#include <algorithm>    // std::max

using namespace std;

int W = 5;
int Weights[] = {0, 2, 1, 3, 2};
int Values[]  = {0,12,10,20,15}; 
int F [5][6];

int MFKnapsack(int i, int j) 
{
	if (i == 0 || j == 0)
		return 0;

	int value;
	if (F[i][j] < 0) {
		if (j < Weights[i])
			value = MFKnapsack(i-1,j);
		else 
			value = max (MFKnapsack(i-1,j),
						 Values[i] + MFKnapsack(i-1,j-Weights[i]));

		F[i][j] = value;
		// show which the value
		cout << "F[" << i << "][" << j << "] = " 
			 << F[i][j] << endl;
	}
	return F[i][j];
}

int Knapsack_bottomup(int n, int m)
{
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (j < Weights[i]) {
				F[i][j] = F[i-1][j];
				cout << "F[" << i << "][" << j << "] = " 
					 << F[i][j] << endl;
			} else {
				F[i][j] = max (F[i-1][j],
							 Values[i] + F[i-1][j-Weights[i]]);
				cout << "F[" << i << "][" << j << "] = " 
					 << F[i][j] << endl;
			}
		}
	}
	return F[n][m];
}

/*
	The O(nW) complexity does not contradict the fact that the knapsack
 	problem is NP-complete, since W, unlike n, is not polynomial 
 	in the length of the input to the problem. The length of the W 
 	input to the problem is proportional to the number of bits in W, 
 	\log W, not to W itself.
*/

int main(int argc, char * argv[])
{
	// Initial the memorize table
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 6; j++)
			F[i][j] = -1;
    
	cout << "MFKnapsack = " << 
		 MFKnapsack(4,5) << endl;

	// Initial the memorize table
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 6; j++)
			F[i][j] = 0;

	cout << "Knapsack_bottomup = " << 
		 Knapsack_bottomup(4,5) << endl;

    return 0;
}


