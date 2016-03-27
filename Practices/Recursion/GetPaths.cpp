//
//  GetPathsWithOffLimits.cpp
//  
//  Created by 罗铮 on 11/4/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <vector>
#include <iostream>

using namespace std;

// d stands for the dimention, and d >= 2
const int d = 3;
static int number = 0;

// store the value of points
struct Point
{
    int x;
    int y;
    Point(int a, int b):x(a),y(b){}
};

// check whether the point is off the limit
bool is_free(int x, int y)
{
    return (x == 1 && y == 1) ? false : true;
}


void print_all_path(int i, int j, vector<Point> &v)
{
	// store the value of point
    Point p(i,j);
    
	// push the value to the vector to store the value
    v.push_back(p);
    
	// if the ant reachs the end
	if (i == d-1 && j == d-1)
	{
		// print out the value
		unsigned int k;
		for(k = 0; k < v.size()-1; k++)
		{
			cout << "(" << v[k].x << "," 
				 << v[k].y << ")" << "->";
		}
		cout << "(" << v[k].x << "," << v[k].y 
			 << ")" << endl;
        number++;
	}
    
	// if the ant moves right
    if (is_free(i+1,j) && i < d-1)
        print_all_path(i + 1,j,v);
    
    // if the ant moves down
    if (is_free(i,j+1) && j < d-1)
        print_all_path(i,j + 1,v);
    
	// pop the already visited points
	v.pop_back();
}


// function called by main
void begin_print()
{
    int i = 0;
    int j = 0;
	// store the value already traversed
    vector<Point> v;
	// call the print function
    print_all_path(i,j,v);
}


int main(int argc, char* argv[])
{
	// print all possible path
	begin_print();
    cout << endl << "Total number of routine is " 
    	 << number << endl;

	return 0;
}

