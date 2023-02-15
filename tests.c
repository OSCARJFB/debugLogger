/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "loglib.h"

int main(void)
{
    clock_t start_time = 0, end_time = 0;
    double total_time = 0.0;
    const int ExecutionLimit = 1000;
    
    for (int i = 0; i < ExecutionLimit; ++i)
    {
        start_time = clock();

        logEvent("Start Test -> char: %c string: %s", 'c', "charArr -> Test End.");
        logEvent("Start Test -> int: %d long: %ld float: %f -> Test End.", 100411, 9223372036854775807, 12300.423f);
        logEvent("Start Test -> hex %x -> Test End.", 0x01);
        logEvent("Start Test -> Only text -> Test End.");
        logEvent("Start Test -> None %%q -> Test End.");

        end_time = clock(); 
        total_time += (double)(start_time - end_time) / CLOCKS_PER_SEC; 
    }

    printf("Average time: %f", total_time / ExecutionLimit);

    return 0;
}
