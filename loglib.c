#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

typedef struct __dateTime__ 
{
    int year, month, day; 
    int hour, min, sec;
} __dateTime__;

void __getDateTime__(FILE *LOG_FILE)
{
    time_t t = time(NULL); 
    struct tm local_time = *localtime(&t);
    __dateTime__ date; 

    date.year = local_time.tm_year + 1900;  
    date.month = local_time.tm_mon + 1;
    date.day = local_time.tm_mday; 
    date.hour = local_time.tm_hour;
    date.min = local_time.tm_min;
    date.sec = local_time.tm_sec;

    fprintf(LOG_FILE, "%d%d%d %d:%d:%d ", date.year, date.day, date.month, date.hour, date.min, date.sec);
}

void __formatLog__(char *logRow, va_list args, FILE *LOG_FILE)
{
    char append_to_file[strlen(logRow)], text_stream[strlen(logRow)];
    int stream_reader = 0, checkForArgs = 0;

    for (int i = 0; i < strlen(logRow); ++i)
    {
        if (i + 1 < strlen(logRow) && logRow[i] == '%')
        {
            strcpy(append_to_file, text_stream);
            fprintf(LOG_FILE, "%s", append_to_file);
            stream_reader = 0;
            checkForArgs = 1;

            switch (logRow[i++ + 1])
            {
            case 's':
                fprintf(LOG_FILE, "%s", va_arg(args, char *));
                break;
            case 'c':
                fprintf(LOG_FILE, "%c", va_arg(args, int));
                break;
            case 'd':
                fprintf(LOG_FILE, "%d", va_arg(args, int));
                break;
            default:
                break;
            }
        }
        else
        {
            text_stream[stream_reader++] = logRow[i];
            text_stream[stream_reader] = '\0';
        }
    }

    if (!checkForArgs)
    {
        fprintf(LOG_FILE, "%s", logRow);
    }
    else
    {
        fprintf(LOG_FILE, "%s", text_stream);
    }

    fprintf(LOG_FILE, "\n");
    fclose(LOG_FILE);
    LOG_FILE = NULL;
}

void eventLog(char *logRow, ...)
{
    va_list args; 
    va_start(args, logRow);
    
    FILE *LOG_FILE = fopen("debug.log", "a");
    __getDateTime__(LOG_FILE); 
    __formatLog__(logRow, args, LOG_FILE);

    va_end(args);
}