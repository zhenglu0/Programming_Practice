//
//  Atomic_Wait.cpp
//  
//  Modified by 罗铮 on 03/26/14.

#include <iostream>       // std::cout
#include <atomic>         // std::atomic_flag
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <sstream>        // std::stringstream

#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;


void append_number(int x) 
{
	while (lock_stream.test_and_set()) {}
	stream << "thread #" << x << '\n';
	lock_stream.clear();
}


// a non-optimized way of checking for prime numbers:
bool is_prime (int x) 
{
	for (int i=2; i<x; ++i) 
		if (x%i==0) 
			return false;
	return true;
}


int main ()
{
	// #1 about atomic_flag
	std::vector<std::thread> threads;
	for (int i=1; i<=10; ++i) 
		threads.push_back(std::thread(append_number,i));
	for (auto& th : threads) th.join();

	std::cout << stream.str();
	
	// #2 about WaitFor
	// call function asynchronously:
	std::future<bool> fut = std::async (is_prime,700020007); 
	// do something while waiting for function to set future:
	std::cout << "checking, please wait";
	std::chrono::milliseconds span (100);
	//while (fut.wait_for(span)==std::future_status::timeout)
	std::cout << '.';

	bool x = fut.get();

	std::cout << "\n700020007 " 
			  << (x?"is":"is not") << " prime.\n";

	return 0;
}
