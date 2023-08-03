/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

// This function gets the date time year/day/month/hour/min/sec.
static void setCurrentDateTime(FILE *LOG_FILE)
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

// Switching the different formatting types in a string according to what was stored in the va_list.
static int switchStringFormatters(char f_one, char f_two,
                           va_list args, FILE *LOG_FILE)
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

    if (f_one + f_two == LD)
    {
        fprintf(LOG_FILE, "%ld", va_arg(args, long));
        forChar += 2;
    }

    return ++forChar;
}

// Write the string and va_list arguments to the file. 
static void writeStringToFile(const char *logRow, va_list args, FILE *LOG_FILE)
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

// Check if a folder exists, if not create one. 
static int createLogFolder(void)
{
    struct stat l_stat;
    const char *folderName = "LogArchive";

    if (stat(folderName, &l_stat) == -1)
    {
        if (mkdir(folderName, 0777) == -1)
        {
            return -1;
        }
    }

    return 0;
}

// string concatenation, adding a number to the end of the logfile.
static void lstrcat(char *fileName, int logNum)
{
    int strEnd = 0;
    const char *extention = ".log";
    char str[10];
    sprintf(str, "%d", logNum);

    for (int i = 0; fileName[i] != '\0'; ++i)
    {
        if (fileName[i + 1] == '\0')
        {
            strEnd = i + 1;
        }
    }

    for (int i = 0; str[i] != '\0'; ++i)
    {
        fileName[strEnd++] = str[i];
    }

    for (int i = 0; extention[i] != '\0'; ++i)
    {
        fileName[strEnd + i] = extention[i];
    }
}

// Counts the number of newlines in the current logfile.
static int countLogFileNewLines(char *fileName)
{
    int newLines = 0, c = 0;
    FILE *LOG_FILE = fopen(fileName, "r");
    if (LOG_FILE == NULL)
    {
        return newLines;
    }

    while ((c = fgetc(LOG_FILE)) != EOF)
    {
        newLines += c == '\n' ? 1 : 0;
    }

    fclose(LOG_FILE);
    LOG_FILE = NULL;

    return newLines;
}

#define NEWLINE_LIMIT 1000

// Numerates the logfiles, depending on the amount of rows currently written to the log.
static int newNumerationOnFile(char *fileName, int newLines, int logNum)
{
    if (newLines >= NEWLINE_LIMIT)
    {
        ++logNum;
        strcpy(fileName, "LogArchive/file");
        lstrcat(fileName, logNum);
    }

    return logNum;
}

#define FILENAME_LIMIT 20

// This is the "logger" function, Which when called, initiates the actual log writing.
void logEvent(const char *logRow, ...)
{
    if (createLogFolder() == -1)
    {
        puts("logEvent: Error couldn't create log archive folder.");
        return;
    }

    char *fileName = malloc(FILENAME_LIMIT * sizeof(char));
    if (fileName == NULL)
    {
        puts("logEvent: Error memory allocation resulted in a nullptr.");
        return;
    }

    strcpy(fileName, "LogArchive/file");

    static int logNum = 0;
    lstrcat(fileName, logNum);
    int newLines = countLogFileNewLines(fileName);
    logNum = newNumerationOnFile(fileName, newLines, logNum);

    va_list args;
    va_start(args, logRow);

    FILE *LOG_FILE = fopen(fileName, "a");
    if (LOG_FILE == NULL)
    {
        puts("logEvent: Error couldn't access file.");
        return;
    }

    setCurrentDateTime(LOG_FILE);
    writeStringToFile(logRow, args, LOG_FILE);

    va_end(args);

    fclose(LOG_FILE);
    LOG_FILE = NULL;

    free(fileName);
    fileName = NULL;
}