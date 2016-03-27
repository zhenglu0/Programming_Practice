//
//  Stream.cpp
//  
//  Created by 罗铮 on 04/18/14.
//  
//  C++ program for implementation of int or string streams

#include <vector>
#include <iostream>

using namespace std;

// Two helper functions
// Simulating read from stream and write to stream
// The stream can be either int or string

//char stream[] = "abcdef";
int stream[] = {1, 2, 3, 4, 5};

void read_stream(void* temp, const void* stream, size_t num)
{
	char *t = static_cast<char *>(temp);
	const char *s = static_cast<const char *>(stream);

	for (size_t i = 0; i < num; i++)
		t[i] = s[i];
}

void write_stream(void* stream, const void* source, size_t num)
{
	char *str = static_cast<char *>(stream);
	const char *sou = static_cast<const char *>(source);

	for (size_t i = 0; i < num; i++)
		str[i] = sou[i];
}

// Declaration of the MyStream
template <class T>
class MyStream
{
public:
	MyStream():size(sizeof(T)){};
	vector<T> read(size_t n);
	void write(const T* t, size_t n);
private:
	size_t size;
};

// Definition of the MyStream
template <typename T>
vector<T> MyStream<T>::read(size_t n)
{
	vector<T> v;
	T *temp = new T[n];

	read_stream(temp, stream, n);
	for (size_t i = 0; i < n / size; i++)
		v.push_back(temp[i]);

	delete [] temp;
	return v;
}

template <typename T>
void MyStream<T>::write(const T* t, size_t n)
{
	write_stream(stream, t, n);
}

// Driver Program
int main ()
{
	//char test[] = "lz love yy";
	//size_t size = sizeof(test);
	
	int test [] = {5, 4, 3, 2, 1};
	size_t size = sizeof(test);

	cout << "stream: " << stream << endl
		 << "test: " << test << endl;

	//MyStream<char> ms;
	//vector <char> v = ms.read(size);
	//ms.write(test, size);

	MyStream<int> ms;
	vector <int> v = ms.read(size);
	ms.write(test, size);

	cout << "stream: " << stream << endl;
	
	cout << "stream: ";
	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << "-";
	cout << endl;

	v = ms.read(size);
	cout << "stream: ";
	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << "-";
	cout << endl;

  	return 0;
}
