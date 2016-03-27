//
//  UniquePartitionInt.cpp
//
//  Modified by 罗铮 on 03/16/14.
//  
//  A C++ program to find the unique partition of integer

#include <iostream>
#include <cstdio>

using namespace std;
 
// A utility function to print an array p[] of size 'n'
void printArray(int p[], int n)
{
    for (int i = 0; i < n; i++)
       cout << p[i] << " ";
    cout << endl;
}
 
void printAllUniqueParts(int n)
{
    int p[n]; // An array to store a partition
    int k = 0;  // Index of last element in a partition
    p[k] = n;  // Initialize first partition as number itself
 
    // This loop first prints current partition, then generates next
    // partition. The loop stops when the current partition has all 1s
    while (true)
    {
        // print current partition
        printArray(p, k+1);
 
        // Generate next partition
 
        // Find the rightmost non-one value in p[]. Also, update the
        // rem_val so that we know how much value can be accommodated
        int rem_val = 0;
        while (k >= 0 && p[k] == 1)
        {
            rem_val += p[k];
            k--;
        }
 
        // if k < 0, all the values are 1 so there are no more partitions
        if (k < 0)  return;
 
        // Decrease the p[k] found above and adjust the rem_val
        p[k]--;
        rem_val++;
 
 
        // If rem_val is more, then the sorted order is violeted.  Divide
        // rem_val in differnt values of size p[k] and copy these values at
        // different positions after p[k]
        while (rem_val > p[k])
        {
            p[k+1] = p[k];
            rem_val = rem_val - p[k];
            k++;
        }
 
        // Copy rem_val to next position and increment position
        p[k+1] = rem_val;
        k++;
    }
}

int list[255];
 
void partition(int n, int m = 0)
{
    int i;
    // if the partition is done
    if(n == 0) {
        // Output the result
        for(i = 0; i < m; ++i)
            printf("%d ", list[i]);
        printf("\n");
        return;
    }
    // Do the split from large to small int
    for(i = n; i > 0; --i) {
        // if the number not partitioned or
        // willbe partitioned no larger than 
        // previous partition number
        if(m == 0 || i <= list[m - 1]) {
            // store the partition int
            list[m] = i;
            // partition the rest
            partition(n - i, m + 1);
        }
    }
}

// Driver program to test above functions
int main()
{
    /*
    cout << "All Unique Partitions of 2 \n";
    printAllUniqueParts(2);
 
    cout << "\nAll Unique Partitions of 3 \n";
    printAllUniqueParts(4);
 
    cout << "\nAll Unique Partitions of 4 \n";
    printAllUniqueParts(7);
    */
    
    partition(6);

    return 0;
}
