/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#include <time.h>
#include "Logger.h"

int main(void)
{
#ifdef DEBUG
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
#endif

    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);

#ifdef DEBUG
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
#endif

    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    eventLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);

#ifdef DEBUG
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by text\n(text)test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
    debugLog("Testing: numbers: %d %d %d more numbers:  %d %d and with a string, char and num: %s  %c %d a newline followed by test done.",
              1, 12, 123, 1234, 12345, "Astring", 'c', 123456);
#endif

    return 0;
}
