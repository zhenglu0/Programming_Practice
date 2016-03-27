//
//  EightQueen.cpp
//
//  Created by 罗铮 on 11/29/12.
//  Copyright (c) 2012 罗铮. All rights reserved.
//

/*
    We will use a backtracking algorithm For each row, 
    the column where we want to put the queen 
    is based on checking that it does not violate 
    the required condition 1 it 2 » »
    For this, we need to store the column of the 
    queen in each row as soon as we have finalized 
    Let ColumnForRow[] be the array which stores 
    the column number for each row
    The checks that are required for the three given conditions are:
    On same Column : ColumnForRow[i] == ColumnForRow[j]
    On same Diagonal: (ColumnForRow[i] - ColumnForRow[j] ) == (i - j) or
    (ColumnForRow[j] - ColumnForRow[i]) == (i - j)
 */

#include <cmath>
#include <iostream>

using namespace std;

bool check(int columForRow[], int row)
{
	for(int i = 0; i < row; i++)
    {
        int diff = abs(columForRow[i] - columForRow[row]);
        if( diff == 0 || diff == row - i)
            return false;
    }
	return true;
}

void DoPlaceQueen(int columForRow[], int row)
{
	if(row == 8)
    {
        for(int i = 0; i < 8; i++)
            cout << columForRow[i] << " ";
        cout << endl;
    }
	
    for(int i = 0; i < 8; i++)
    {
        // We first try to place a queen on position i
        columForRow[row] = i;
        // This is the backtrack step
        if(check(columForRow, row))
            DoPlaceQueen(columForRow, row + 1);
    }
}

void placeQueen()
{
	int columForRow[8];
	int row = 0;
	DoPlaceQueen(columForRow, row);
}


int main(int argc, const char * argv[])
{
    placeQueen();
    return 0;
}

