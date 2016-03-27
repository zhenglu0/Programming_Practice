//
//  MergeStream.cpp
//  
//  Created by 罗铮 on 04/18/14.
//  
//  C++ program for implementation of merge of multiple streams

#include <vector>
#include <deque>
#include <iostream>

using namespace std;

// #1.
// Definition of the Stream
template <class T>
class Stream
{
public:
	const T& front() const { return d.front(); };
	void pop_front() { d.pop_front(); };
	bool empty() const { return d.empty(); };
	void push_back(const T& t) { return d.push_back(t); };
private:
	deque<T> d;
};

// #2
// Definition of the output Stream
template <class T>
class Ostream
{
public:
	void insert(const T& t) { return v.push_back(t); };
	size_t size() const { return v.size(); };
	const T& operator[] (size_t n) const { return v[n]; };
private:
	vector<T> v;	
};

// Definition of the compare function
template <typename T>
int compare(const T &a, const T &b)
{
	if (a < b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}

// Definition of the compare functor
template <typename T>
struct Compare {
	bool operator() (T i,T j) { return (i > j); }
};

// Implementation of the Merge function
template <typename T>
void merge_multiple_stream(vector <Stream<T> > &s, 
						 Ostream<T> &o,
						 Compare<T> &comp)
{
	int size = (int)s.size(), index = 0;
	bool flag = false;
	T *min = NULL;

	while (true) {
		// Check if every stream is empty
		for (int i = 0; i < size; i++) {
			if (!s[i].empty()) {
				flag = true;
				break;
			}
		}
		// If all the stream is empty
		if (!flag)
			break;

		// Reset the flag
		flag = false;

		// Get the smallest element
		for (int i = 0; i < size; i++) {
			if (!s[i].empty()) {
				if (min == NULL ||
					comp(*min, s[i].front())) {
					min = const_cast<int*>(&s[i].front());
					index = i;
				}
			}
		}

		// Insert to the output stream
		o.insert(*min);
		// Reset the pointer to NULL
		min = NULL;
		// Remvoe the min element
		s[index].pop_front();
	}
}

// Driver Program
int main ()
{
	Stream<int> v1;
	Stream<int> v2;
	Stream<int> v3;
	Stream<int> v4;
	Stream<int> v5;

	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	v1.push_back(7);
	v2.push_back(1);
	v2.push_back(8);
	v3.push_back(9);
	v3.push_back(10);
	v3.push_back(11);
	v4.push_back(12);
	v4.push_back(15);
	v5.push_back(13);
	v5.push_back(14);
	v5.push_back(16);

	vector<Stream<int> > v;
  	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);
	v.push_back(v5);

	Ostream<int> o;
	Compare<int> comp;
	
	merge_multiple_stream(v, o, comp);

	for (int i = 0; i < (int)o.size(); i++)
		cout << o[i] << " ";

	cout << endl;

  	return 0;
}
