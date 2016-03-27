//
//  Concurrency.cpp
//  
//  Modified by 罗铮 on 03/26/14.

#include <iostream>
#include <algorithm>
#include <thread>
#include <cassert>
#include <string>

using namespace std;

template<int ROWS, int COLS>
int countArray(int value, int a[ROWS][COLS], 
		       int rbegin, int rend, int cbegin, int cend)
{
	int count = 0;
	for (int i = rbegin; i < rend; i++)
		for (int j = cbegin; j < cend; j++)
			if (a[i][j] == value)
				count++;

	return count;
}

template<int ROWS, int COLS>
void addArrays(int a[ROWS][COLS], int b[ROWS][COLS], 
			   int c[ROWS][COLS], int rbegin, int rend, 
			   int cbegin, int cend)
{
	for (int i = rbegin; i < rend; i++)
		for (int j = cbegin; j < cend; j++)
			c[i][j] = a[i][j] + b[i][j];
}

template<int M, int N, int P>
void multiplyArrays(int a[M][P], int a_rbegin, int a_rend, int a_cbegin, int a_cend, 
					int b[P][N], int b_rbegin, int b_rend, int b_cbegin, int b_cend, 
					int c[M][N], int c_rbegin, int c_rend, int c_cbegin, int c_cend)
{
	int m = a_rend - a_rbegin;
	int n = b_cend - b_cbegin;
	int p = a_cend - a_cbegin;

	assert(m == c_rend - c_rbegin);
	assert(n == c_cend - c_cbegin);
	assert(p == b_rend - b_rbegin);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			c[c_rbegin + i][c_cbegin + j] = 0;
			for (int k = 0; k < p; k++)
			{
				c[c_rbegin + i][c_cbegin + j] += 
					a[a_rbegin + i][a_cbegin + k] + 
					b[b_rbegin + k][c_cbegin + j];
			}
		}
}

template<typename T> 
void test(T &t)
{
	cout << "The T is " << t << endl;
}

template<typename T, int ROWS, int COLS>
void printArrayPortion(T a[ROWS][COLS], int rbegin, int rend, 
					   int cbegin, int cend)
{
	for (int i = rbegin; i < rend; i++)
	{ 
		for (int j = cbegin; j < cend; j++)
			cout << a[i][j] << " ";
		
		cout << endl;
	}

}


int main(int argc, char* argv[])
{
	int a[16][4];
	int b[4][16];
	int c[16][16];
	double d[4][4];

	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 4; j++)
			a[i][j] = 4*i + j;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 16; j++)
			b[i][j] = 16*i + j;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		        d[i][j] = (4*i + j)*0.1;

	cout << thread::hardware_concurrency() << endl;

	// Split into rectangles
	thread t1([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4, 
		b, 0, 4, 0, 2,
		c, 0, 16, 0, 2); 
	});
	thread t2([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4, 
		b, 0, 4, 2, 4,
		c, 0, 16, 2, 4); 
	});
	thread t3([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4, 
		b, 0, 4, 4, 6,
		c, 0, 16, 4, 6); 
	});
	thread t4([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4,
		b, 0, 4, 6, 8,
		c, 0, 16, 6, 8); 
	});
	thread t5([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4,
		b, 0, 4, 8, 10,
		c, 0, 16, 8, 10); 
	});
	thread t6([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4,
		b, 0, 4, 10, 12,
		c, 0, 16, 10, 12); 
	});
	thread t7([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4, 
		b, 0, 4, 12, 14,
		c, 0, 16, 12, 14); 
	});
	thread t8([&a, &b, &c]{ multiplyArrays<16,16,4>(
		a, 0, 16, 0, 4,
		b, 0, 4, 14, 16,
		c, 0, 16, 14, 16); 
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			cout << c[i][j] << endl;
	
	string s = "hello zheng";
	test<string>(s);
	
	int o = 1;
	test<int>(o);

	printArrayPortion<double,4,4> (d,0,3,0,3);

	return 0;
}

