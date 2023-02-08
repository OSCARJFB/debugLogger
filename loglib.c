#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct dateTime
{
    int year, month, day;
    int hour, min, sec;
} dateTime;

typedef struct fileMetaData
{
    char fileName[100];
    int currentLine;
} fileMetaData;

/* "Evil" global variable.... */
fileMetaData metaData;

#define RUN_IF_FILE_ACCESS_ERR               \
    if (LOG_FILE == NULL)                    \
    {                                        \
        puts("Error couldn't access file."); \
    }

/**
 * This function gets the date time year/day/month/hour/min/sec.
 * Data which is used to determine at what time a line was written in the log.
 */
void setCurrentDateTime(FILE *LOG_FILE)
{
    time_t t = time(NULL);
    struct tm local_time = *localtime(&t);
    dateTime date;

    date.year = local_time.tm_year + 1900;
    date.month = local_time.tm_mon + 1;
    date.day = local_time.tm_mday;
    date.hour = local_time.tm_hour;
    date.min = local_time.tm_min;
    date.sec = local_time.tm_sec;

    fprintf(LOG_FILE, "%d%d%d %d:%d:%d ", date.year, date.day, date.month, date.hour, date.min, date.sec);
}

/**
 * Switches all the different formatting types in a string.
 * The formatter should correspond to the actual datatype stored in the va_list.
 * To be added: manage errors that can occure from wrong formatting input.
 */
void switchStringFormatters(char formatter, va_list args, FILE *LOG_FILE)
{
    switch (formatter)
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
    case 'f':
        fprintf(LOG_FILE, "%f", va_arg(args, double));
        break;
    default:
        break;
    }
}

/**
 * Here we actually write most parts of the string to the file.
 * If we find a % character we check wether or not it's followed by a string formatter character.
 */
void writeStringToFile(char *logRow, va_list args, FILE *LOG_FILE)
{
    char append_to_file[strlen(logRow)], text_stream[strlen(logRow)];
    int stream_reader = 0;
    bool checkForArgs = false;

    for (int i = 0; i < strlen(logRow); ++i)
    {
        if (i + 1 < strlen(logRow) && logRow[i] == '%')
        {
            strcpy(append_to_file, text_stream);
            fprintf(LOG_FILE, "%s", append_to_file);
            stream_reader = 0;
            checkForArgs = true;
            switchStringFormatters(logRow[++i], args, LOG_FILE);
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

/**
 * Simply counts all the lines in a file.
 * This is used to keep track of when to write/create a new file.
 */
int countLinesInFile(char *fileName)
{
    FILE *LOG_FILE = fopen(fileName, "w+");
    RUN_IF_FILE_ACCESS_ERR;

    int newlines = 0, c;
    while (c = getc(LOG_FILE) != EOF)
    {
        if(c == '\n')
        {
            ++newlines; 
        }
    }
    return newlines;
}

/**
 * Simply counts all the lines in a file.
 * This is used to keep track of when to write/create a new file.
 * Only file name is needed as a parameter, not the extension type.
 */
void setLogName(char *fileName)
{
    const int max_size = 99; 
    if(strlen(fileName) > max_size)
    {
        fileName[max_size + 1] = '\0';
    }

    strcpy(metaData.fileName, fileName);
    strcat(metaData.fileName, ".log");
    metaData.currentLine = 0;
}

/**
 * This is the "logger" function.
 * Which when called, initiates the actual log writing.
 * It takes a string with formatters followed by any corresponding amount of parameters.
 */
void logEvent(char *logRow, ...)
{
    va_list args;
    va_start(args, logRow);

    FILE *LOG_FILE = fopen(metaData.fileName, "a");
    RUN_IF_FILE_ACCESS_ERR;

    if (metaData.currentLine == 0)
    {
        countLinesInFile(metaData.fileName);
    }

    setCurrentDateTime(LOG_FILE);
    writeStringToFile(logRow, args, LOG_FILE);

    va_end(args);
}