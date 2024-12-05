#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINE_LENGTH 50

void print_array(int *arr, int n, int safe) {
    const char *RED = "\033[31m";
    const char *ORANGE = "\033[33m";
    const char *GREEN = "\033[32m";
    const char *RESET = "\033[0m";
    for (int i = 0; i < n; i++) {
        if (safe == 0) {
            printf("%s%d%s ", GREEN, arr[i], RESET);
        } else if (safe == 1) {
            printf("%s%d%s ", ORANGE, arr[i], RESET);
        } else {
            printf("%s%d%s ", RED, arr[i], RESET);
        }
    }
    printf("\n");
}

bool is_safe(int *lvls, int n) {
    int inc = 0, dec = 0;
    for (int i = 1; i < n; i++) {
        int p = lvls[i] - lvls[i - 1];
        if (p > 0 && p <= 3) {
            inc++;
        } else if (p < 0 && p >= -3) {
            dec++;
        } else {
            return false;
        }
    }
    if (inc > 0 && dec > 0) {
        return false;
    }
    return true;
}

bool is_dampener_safe(int *lvls, int n) {
    for (int i = 0; i < n; i++) {
        int temp[n-1];
        int idx = 0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                temp[idx++] = lvls[j];
            }
        }
        if (is_safe(temp, n - 1)) {
            return true;
        }
    }
    return false;
}

int main() {
    FILE *file = fopen("input-2.txt", "r");
    int safe_count = 0;
    int dampener_count = 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        int lvls[8];
        int count = 0;

        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            lvls[count++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }

        if (is_safe(lvls, count)) {
            safe_count++;
            dampener_count++;
            print_array(lvls, count, 0);
        } else if (is_dampener_safe(lvls, count)) {
            dampener_count++;
            print_array(lvls, count, 1);
        } else {
            print_array(lvls, count, 2);
        }
    }
    printf("Safe: %d\n", safe_count);
    printf("Dampener safe: %d\n", dampener_count);

    fclose(file);
    return 0;
}
