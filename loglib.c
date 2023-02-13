#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

/**
 * This function gets the date time year/day/month/hour/min/sec.
 * Data which is used to determine at what time a line was written in the log.
 */
void setCurrentDateTime(FILE *LOG_FILE)
{
    time_t t = time(NULL);
    struct tm local_time = *localtime(&t);

    int year = local_time.tm_year + 1900;
    int month = local_time.tm_mon + 1;
    int day = local_time.tm_mday;
    int hour = local_time.tm_hour;
    int min = local_time.tm_min;
    int sec = local_time.tm_sec;

    fprintf(LOG_FILE, "%d%d%d %d:%d:%d ", year, day, month, hour, min, sec);
}

#define LD 208

/**
 * Switches all the different formatting types in a string.
 * The formatter should correspond to the actual datatype stored in the va_list.
 * To be added: manage errors that can occure from wrong formatting input.
 */
int switchStringFormatters(char f_one, char f_two, va_list args, FILE *LOG_FILE)
{
    int forChar = 0;

    switch (f_one)
    {
    case 's':
        fprintf(LOG_FILE, "%s", va_arg(args, char *));
        ++forChar;
        break;
    case 'c':
        fprintf(LOG_FILE, "%c", va_arg(args, int));
        ++forChar;
        break;
    case 'd':
        fprintf(LOG_FILE, "%d", va_arg(args, int));
        ++forChar;
        break;
    case 'u':
        fprintf(LOG_FILE, "%u", va_arg(args, unsigned int));
        ++forChar;
        break;
    case 'i':
        fprintf(LOG_FILE, "%i", va_arg(args, int));
        ++forChar;
        break;
    case 'o':
        fprintf(LOG_FILE, "%o", va_arg(args, int));
        ++forChar;
        break;
    case 'f':
        fprintf(LOG_FILE, "%f", va_arg(args, double));
        ++forChar;
        break;
    case 'x':
        fprintf(LOG_FILE, "%x", va_arg(args, int));
        ++forChar;
        break;
    case 'p':
        fprintf(LOG_FILE, "%p", va_arg(args, void *));
        ++forChar;
        break;
    default:
        break;
    }

    if(f_one + f_two == LD)
    {
        fprintf(LOG_FILE, "%ld", va_arg(args, long));
        forChar += 2;
    }

    return ++forChar;
}

/**
 * Here we actually write most parts of the string to the file.
 * If we find a % character we check wether or not it's followed by a string formatter character.
 */
void writeStringToFile(char *logRow, va_list args, FILE *LOG_FILE)
{
    char append_to_file[strlen(logRow)], text[strlen(logRow)];
    int reader = 0;

    for (int i = 0; i < strlen(logRow); ++i)
    {
        if (i + 1 < strlen(logRow) && logRow[i] == '%')
        {
            strcpy(append_to_file, text);
            fprintf(LOG_FILE, "%s", append_to_file);
            reader = 0;

            i += switchStringFormatters(logRow[i + 1], logRow[i + 2], args, LOG_FILE);
        }

        text[reader++] = logRow[i];
        text[reader] = '\0';

        if (i + 1 == strlen(logRow))
        {
            strcpy(append_to_file, text);
            fprintf(LOG_FILE, "%s", append_to_file);
        }
    }

    fprintf(LOG_FILE, "\n");
}

#define NEWLINE_LIMIT 100

/**
 *  Counts the number of newlines in the current logfile. 
 *  Returns an integer value that is used to determine wether or not data should be written to a new file. 
 */
int countLogFileNewLines(char *fileName)
{
    int newLines = 0, c = 0; 
    FILE *LOG_FILE = fopen(fileName, "r");
    if (LOG_FILE == NULL)
    {
        puts("logEvent: Error, Couldn't read file.");
        return -1;
    }

    while((c = fgetc(LOG_FILE)) != EOF)
    {
        newLines += c == '\n' ? 1 : 0; 
    }

    fclose(LOG_FILE);
    LOG_FILE = NULL; 

    return newLines;
}

#define FILENAME_LIMIT 100

/**
 * This is the "logger" function.
 * Which when called, initiates the actual log writing.
 * It takes a string with formatters followed by any corresponding amount of parameters.
 */
void logEvent(char *logRow, ...)
{
    va_list args;
    va_start(args, logRow);

    char *fileName = "event.log";
    
    int newLines = countLogFileNewLines(fileName);

    FILE *LOG_FILE = fopen(fileName, "a");
    if (LOG_FILE == NULL)
    {
        puts("logEvent: Error, Couldn't append to file.");
        return;
    }

    setCurrentDateTime(LOG_FILE);
    writeStringToFile(logRow, args, LOG_FILE);

    va_end(args);

    fclose(LOG_FILE);
    LOG_FILE = NULL;
}