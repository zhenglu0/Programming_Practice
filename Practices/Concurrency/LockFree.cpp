//
//  LockFree.cpp
//  
//  Modified by 罗铮 on 03/26/14.

/*  
    compare_exchange and compare-and-swap refers to the same concept.
    
    In computer science, compare-and-swap (CAS) is an atomic instruction 
    used in multithreading to achieve synchronization. It compares the 
    contents of a memory location to a given value and, only if they 
    are the same, modifies the contents of that memory location to a 
    given new value. This is done as a single atomic operation. The 
    atomicity guarantees that the new value is calculated based on 
    up-to-date information; if the value had been updated by another 
    thread in the meantime, the write would fail. The result of the 
    operation must indicate whether it performed the substitution; 
    this can be done either with a simple Booleanresponse (this 
    variant is often called compare-and-set), or by returning the 
    value read from the memory location (not the value written to it).

    In concurrent programming, an operation (or set of operations) is 
    atomic, linearizable, indivisible or uninterruptible if it appears 
    to the rest of the system to occur instantaneously. Atomicity is a 
    guarantee of isolation from concurrent processes. Additionally, 
    atomic operations commonly have a succeed-or-fail definition — they
    either successfully change the state of the system, or have no 
    apparent effect.

    Atomicity is commonly enforced by mutual exclusion, whether at the 
    hardware level building on a cache coherency protocol, or the software 
    level using semaphoresor locks. Thus, an atomic operation does not 
    actually occur instantaneously. The benefit comes from the appearance: 
    the system behaves as if each operation occurred instantly, separated 
    by pauses. Because of this, implementation details may be ignored by 
    the user, except insofar as they affect performance. If an operation 
    is not atomic, the user will also need to understand and cope with 
    sporadic extraneous behaviour caused by interactions between concurrent
    operations, which by their nature are likely to be hard to 
    reproduce and debug.
*/

#include <atomic>
#include <memory>
#include <iostream>
#include <thread>

using namespace std;

template<typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        node* next;
        node(T const& data_):
            data(std::make_shared<T>(data_))
        {}
    };
    std::atomic<node*> head;
public:
    void push(T const& data)
    {
        node* const new_node=new node(data);
        new_node->next=head.load();
        while(!head.compare_exchange_weak(new_node->next,new_node));
    }
    std::shared_ptr<T> pop()
    {
        node* old_head=head.load();
        while(old_head &&
              !head.compare_exchange_weak(old_head,old_head->next));
        return old_head ? old_head->data : std::shared_ptr<T>();
    }
};


int main(int argc, char* argv[])
{
    thread t3([]{
            lock_free_stack<int> stack;
 
            thread t1([&stack]{
	    for(int i = 1; i < 20; i += 2){
	        cout << "Push: " << i << endl;
	        stack.push(i);
	    }
	    for(int i = 1; i < 20; i += 2){
	        cout << "Pop: " << *stack.pop() << endl;
	    }
            });

            thread t2([&stack]{
	    for(int i = 0; i < 20; i += 2){
	        cout << "Push: " << i << endl;
	        stack.push(i);
	    }
	    for(int i = 0; i < 20; i += 2){
	        cout << "Pop: " << *stack.pop() << endl;
	    }
            });

            t1.join();
            t2.join();
    });
    
    t3.join();
    
    return 0;
}
