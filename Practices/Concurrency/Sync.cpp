//
//  Sync.cpp
//  
//  Modified by 罗铮 on 03/26/14.

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

template<typename LOCK>
class OurVec {
private:
    LOCK m;
    vector<int> vec;

public:
    OurVec& operator<< (const int& num) 
    {
        lock_guard<LOCK> lg(m);
        vec.push_back(num);
        return *this;
    }

    int operator() () 
    {
        lock_guard<LOCK> lg(m);
        int sum = 0;
        for (size_t i = 0; i < vec.size(); ++i) {
            sum += vec[i];
        }
        return sum;
    }

    void synchPrint(int num) 
    {
        lock_guard<LOCK> lg(m);
        cout << num << endl;
    }

    void factorialOfSum() 
    {
        lock_guard<LOCK> lg(m);
        int fact = 1;
        for (int sum = (*this)(); sum > 0; sum--) {
            fact *= sum;
        }
        cout << fact << endl;
    }
};

int main(int argc, char* argv[])
{
    OurVec<recursive_mutex> vec1;
    
    /*thread t1([&vec1]{vec1 << 1 << 2 << 3 << 4;});
    thread t2([&vec1]{vec1 << 4;vec1.synchPrint(vec1());
    vec1 << 5; vec1.synchPrint(vec1()); vec1 << 6; });
    
    thread t3([&vec1]{vec1.synchPrint(vec1()); 
    vec1.synchPrint(vec1()); vec1.synchPrint(vec1());});
    t1.join(); t2.join(); t3.join();
    */
    vec1.factorialOfSum();
    
    return 0;
}
