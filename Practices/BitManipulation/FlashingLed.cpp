//
//  FlashingLed.cpp
//  
//  Modified by 罗铮 on 04/10/14.

#include <cstdio>
#include <cstdint>

#ifdef _WIN32
#include <windows.h>
void sleeping(unsigned milliseconds)
{
    Sleep(milliseconds);
}
#else
#include <unistd.h>
void sleeping(unsigned milliseconds)
{
    usleep(milliseconds * 1000); 
}
#endif

// print dec in binary 
void printBinary(uint16_t a)
{
    // 16 bit print
    for(uint16_t i = 32768; i > 0; i = (i>>1)) {
        if(a & i)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void LedFlash()
{
    volatile 
        uint16_t a = (uint16_t)0;
    while(1) {
        // bit-4
        a ^= (1 << 4);
        printBinary(a);
        sleeping(1000); //1 sec delay
    }
}

int main()
{
    LedFlash();
    return 0;
}
