/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#include <time.h>
#include <stdio.h>
#include "loglib.h"

int main(void)
{
    clock_t start_time = clock(); 
    clock_t end_time = clock(); 
    double total_time = 0.0; 

    for(int i = 0; i < 1000; ++i)
    {
        start_time = clock(); 
        eventLog("Test %d test %d test %d test %d test %d test %d ", 1, 2, 3, 4, 5, 6);
        end_time = clock(); 
        total_time = (start_time - end_time) / CLOCKS_PER_SEC; 
    }

    printf("%f", total_time); 

    return 0;
}
