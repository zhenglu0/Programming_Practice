//
//  Kinght.cpp
//  
//  Created by 罗铮 on 03/12/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <vector>
#include <iostream>

using namespace std;

// d stands for the dimention, and d >= 2
const int d = 6;

// store the value of points

struct position {
	int x;
	int y;
	position (int _x, int _y):x(_x),y(_y){};
};

struct board
{
	int onboard[d][d];
	int node_visited;
	board():node_visited(0)
	{
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j) 
				onboard[i][j] = 0;
	};
};

vector<position> next_possible_position (position *p) 
{
	vector<position> v;

	if (!p)
		return v;

	int i = p->x, j = p->y;

	if (i-1 >= 0 && j-2 >= 0 &&
	    i-1 <  d && j-2 <  d) {
		position p1(i-1,j-2);
		v.push_back(p1);
	} 
	if (i+1 >= 0 && j-2 >= 0 &&
		i+1 <  d && j-2 <  d) {
		position p2(i+1,j-2);
		v.push_back(p2);
	} 
	if (i-2 >= 0 && j-1 >= 0 &&
		i-2 <  d && j-1 <  d) {
		position p3(i-2,j-1);
		v.push_back(p3);
	} 
	if (i+2 >= 0 && j-1 >= 0 &&
		i+2 <  d && j-1 <  d) {
		position p4(i+2,j-1);
		v.push_back(p4);
	}
	if (i-2 >= 0 && j+1 >= 0 &&
		i-2 <  d && j+1 <  d) {
		position p5(i-2,j+1);
		v.push_back(p5);
	}
	if (i+2 >= 0 && j+1 >= 0 &&
		i+2 <  d && j+1 <  d) {
		position p6(i+2,j+1);
		v.push_back(p6);
	}
	if (i-1 >= 0 && j+2 >= 0 &&
		i-1 < d  && j+2 < d) {
		position p7(i-1,j+2);
		v.push_back(p7);
	}
	if (i+1 >= 0 && j+2 >= 0 &&
		i+1 <  d && j+2 <  d) {
		position p8(i+1,j+2);
		v.push_back(p8);
	}

	return v;
}

void test_hyposisthsis (position *p, bool &flag, 
						board *b, int &total) { 
	
	//if (flag)
		//return;
	
	if (b->onboard[p->x][p->y] == 1) {
		return;
	}

	if(b->node_visited == d*d-1) {
		//flag = true;
		total++;
		return;
	} 
	
	vector <position> v = next_possible_position(p);
	/*
	cout << "Next Position" << endl;

	for (size_t i = 0; i < v.size(); i++) {
		cout << "(" << v[i].x << ","
			 << v[i].y << ")" << endl;
	}
	*/
	b->onboard[p->x][p->y] = 1;
	b->node_visited++;

	for (size_t i = 0; i < v.size(); i++) {
		test_hyposisthsis(&v[i], flag, b, total);
	}
	
	b->onboard[p->x][p->y] = 0;
	b->node_visited--;
}

int main(int argc, char* argv[])
{
	/*
	position p(4,4);

	vector<position> v = next_possible_position(&p);

	for (size_t i = 0; i < v.size(); ++i) {
		cout << "(" << v[i].x << ","
			 << v[i].y << ")" << endl;
	}
	*/

	bool flag = false;
	int total = 0;
	board b;
	
	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < d; ++j)  {
			position p2(i,j);
			test_hyposisthsis(&p2, flag, &b, total);
		}
	}
		 
	cout << "The total number is " << total << endl;
	//cout << boolalpha << flag << endl;
	

	// Test all possible knight move
	/*
	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < d; ++j)  {
			position p3(i,j);
			vector<position> t =  next_possible_position (&p3);
			cout <<  t.size() << " ";
		}
		cout << endl;
	}
	*/
	return 0;
}

