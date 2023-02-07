/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#include <time.h>
#include <stdlib.h>
#include "loglib.h"

int main(void)
{
    clock_t start_time = clock(), end_time = clock();
    double total_time = 0.0;
    const int ExecutionLimit = 1000;

    /**
     * TEXT FORMATTING TEST
     * Here we test how the function handles different ways of formatting text.
     */
    for (int i = 0; i < ExecutionLimit; ++i)
    {
        logEvent("Testing: numbers: %d %d %d more numbers: %d %d and with a string, char and num: %s %c %d.",
                 1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    }

    system("mv debug.log testA.log");

    /**
     * EXECUTION TIME TEST,
     * It will execute the log function a 1000 times and calculate the average execution time.
     */
    for (int i = 0; i < ExecutionLimit; ++i)
    {
        start_time = clock();
        logEvent("Test %d test %d test %d test %d test %d test %d ", 1, 2, 3, 4, 5, 6);
        end_time = clock();
        total_time += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }

    total_time = total_time / ExecutionLimit;

    system("rm -rf debug.log");
    logEvent("Average execution time = %f", total_time);
    system("mv debug.log testB.log");

    return 0;
}
