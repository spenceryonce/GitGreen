#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <process.h>
#include <Windows.h>

int main() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentDayOfYear = tm.tm_yday + 1;
    srand(time(NULL)); // Initialize random seed

    for (int i = 0; i < currentDayOfYear; i++) {
        for (int j = 0; j < rand() % 5; j++) {
            char dateUsed[50];
            sprintf(dateUsed, "%d-%d-%d", tm.tm_year + 1900, 1, 1 + i);
            char command[256];

            // Run "git add ."
            snprintf(command, sizeof(command), "git add .");
            if (system(command) != 0) {
                perror("Error running git add");
                exit(EXIT_FAILURE);
            }

            // Run "echo ... >> green.txt"
            snprintf(command, sizeof(command), "echo %s-%d >> green.txt", dateUsed, j);
            if (system(command) != 0) {
                perror("Error running echo");
                exit(EXIT_FAILURE);
            }

            // Run "git commit ..."
            snprintf(command, sizeof(command), "git commit --date=\"%d day ago\" -m \"%d\"", 365 - i, i);
            if (system(command) != 0) {
                perror("Error running git commit");
                exit(EXIT_FAILURE);
            }
        }

        printf("-----------------------------\n");
        printf("Processing Day %d\n", i);
        printf("-----------------------------\n");
    }
    return 0;
}
