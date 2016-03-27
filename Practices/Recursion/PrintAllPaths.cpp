// 
// PrintAllPaths.cpp
// 
// Created by Zheng Luo on 09/21/2012
// 
// You have a chess board of size 8x8. An ant starts at the top left,
// which we'll say has coordinates (0,0). 
// The ant must move to the bottom right, which has coordinates (7,7). 
// It can only move either down or to the right, never up or to the 
// left. Write a program that will print all possible paths
// the ant could take.

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
			cout << "(" << v[k].x << "," << v[k].y << ")" << "->";
		}
		cout << "(" << v[k].x << "," << v[k].y << ")" << endl;
        number++;
	}
    
	// if the ant moves right
    if (i < d-1)
        print_all_path(i + 1,j,v);
    
    // if the ant moves down
    if (j < d-1)
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
    cout << endl << "Total number of routine is " << number << endl;
	return 0;
}

