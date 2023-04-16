#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

int is_leap_year(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int days_in_month(int month, int year)
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 1 && is_leap_year(year))
    {
        return 29;
    }
    return days[month];
}

void parse_args(int argc, char *argv[], int *backtrack_days)
{
    for (int i = 1; i < argc; ++i)
    {
        if ((strcmp(argv[i], "--backtrack") == 0 || strcmp(argv[i], "--b") == 0) && i + 1 < argc)
        {
            *backtrack_days = atoi(argv[i + 1]);
            i++;
        }
        else
        {
            fprintf(stderr, "Usage: %s [--backtrack DAYS] [--b DAYS]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[])
{
    int backtrack_days = 365;
    parse_args(argc, argv, &backtrack_days);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    srand((unsigned int)time(NULL)); // Initialize random seed

    int end_year = tm.tm_year + 1900;
    int end_month = tm.tm_mon;
    int end_day = tm.tm_mday;

    time_t start_time = t - (time_t)(backtrack_days * 86400);
    struct tm start_tm = *localtime(&start_time);
    int start_year = start_tm.tm_year + 1900;
    int start_month = start_tm.tm_mon;
    int start_day = start_tm.tm_mday;

    char dateUsed[50];

    for (int year = start_year; year <= end_year; ++year)
    {
        for (int month = (year == start_year ? start_month : 0); month <= (year == end_year ? end_month : 11); ++month)
        {
            for (int day = (year == start_year && month == start_month ? start_day : 1); day <= (year == end_year && month == end_month ? end_day : days_in_month(month, year)); ++day)
            {
                for (int j = 0; j < rand() % 5; j++)
                {
                    sprintf(dateUsed, "%d-%02d-%02d", year, month + 1, day);
                    char command[256];

                    // Run "git add ."
                    snprintf(command, sizeof(command), "git add .");
                    if (system(command) != 0)
                    {
                        perror("Error running git add");
                        exit(EXIT_FAILURE);
                    }

                    // Run "echo ... >> green.txt"
                    snprintf(command, sizeof(command), "echo %s-%d >> green.txt", dateUsed, j);
                    if (system(command) != 0)
                    {
                        perror("Error running echo");
                        exit(EXIT_FAILURE);
                    }

                    // Run "git commit ..."
                    snprintf(command, sizeof(command), "git commit --date=\"%s\" -m \"%s-%d\"", dateUsed, dateUsed, j);
                    if (system(command) != 0)
                    {
                        perror("Error running git commit");
                        exit(EXIT_FAILURE);
                    }
                }
                printf("-----------------------------\n");
                printf("Processing Date %s\n", dateUsed);
                printf("-----------------------------\n");
            }
        }
    }
    return 0;
}
