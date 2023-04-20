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
        intptr_t pid = _spawnl(_P_NOWAIT, "cmd.exe", "cmd.exe", "/C", "exit", NULL);
        if (pid >= 0) {
            int random = rand() % 5;
            char dateUsed[50];
            sprintf(dateUsed, "%d-%d-%d", tm.tm_year + 1900, 1, 1 + i);
            for (int j = 0; j < random; j++) {
                FILE* fp = _popen("git add .", "w");
                if (fp == NULL) { // Error handling for _popen
                    perror("_popen");
                    exit(EXIT_FAILURE);
                }
                fprintf(fp, "echo %s-%d >> green.txt\n", dateUsed, j);
                fprintf(fp, "git commit --date=\"%d day ago\" -m \"%d\"\n", 365 - i, i);
                if (_pclose(fp) == -1) { // Error handling for _pclose
                    perror("_pclose");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else { // Error handling for _spawnl
            perror("_spawnl");
            exit(EXIT_FAILURE);
        }

        DWORD exit_code;
        if (GetExitCodeProcess((HANDLE)pid, &exit_code) && exit_code == STILL_ACTIVE) {
            WaitForSingleObject((HANDLE)pid, INFINITE);
            printf("-----------------------------\n");
            printf("Processing Day %d\n", i);
            printf("-----------------------------\n");
        }
    }
    return 0;
}
