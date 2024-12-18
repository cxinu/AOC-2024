#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NODES 100
#define MAX_SERIES 100
#define MAX_SERIES_LENGTH 100

typedef struct {
    int from;
    int to;
} Rule;

Rule rules[MAX_NODES * MAX_NODES];
int rule_count = 0;

int series[MAX_SERIES][MAX_SERIES_LENGTH];
int series_lengths[MAX_SERIES];
int series_count = 0;

// Function to add a rule to the rule list
void add_rule(int from, int to) {
    rules[rule_count++] = (Rule){from, to};
}

// Parse the input file and populate the rules and series
void parse_input(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    bool parsing_rules = true;

    while (fgets(line, sizeof(line), file)) {
        // Trim whitespace
        char *ptr = line;
        while (isspace(*ptr)) ptr++;

        // Skip empty lines
        if (*ptr == '\0') continue;

        if (parsing_rules) {
            if (strchr(ptr, '|')) {
                // Parse a rule X|Y
                int from, to;
                if (sscanf(ptr, "%d|%d", &from, &to) == 2) {
                    add_rule(from, to);
                }
            } else {
                parsing_rules = false;
            }
        }

        if (!parsing_rules && strchr(ptr, ',')) {
            // Parse a series
            int index = 0, num;
            while (sscanf(ptr, "%d", &num) == 1) {
                series[series_count][index++] = num;
                ptr = strchr(ptr, ',');
                if (!ptr) break;
                ptr++;
            }
            series_lengths[series_count++] = index;
        }
    }

    fclose(file);
}

// Check if a series is valid according to the rules
bool is_valid_series(int series[], int size) {
    bool seen[MAX_NODES] = {false};

    for (int i = 0; i < size; i++) {
        int current = series[i];
        seen[current] = true;

        // Check all rules
        for (int j = 0; j < rule_count; j++) {
            int from = rules[j].from;
            int to = rules[j].to;

            if (seen[to] && !seen[from]) {
                // If "to" has been seen but "from" hasn't, the rule is violated
                return false;
            }
        }
    }
    return true;
}

int main() {
    parse_input("input-5.txt");

    // Check each series
    for (int i = 0; i < series_count; i++) {
        if (is_valid_series(series[i], series_lengths[i])) {
            printf("Series %d is valid.\n", i + 1);
        } else {
            printf("Series %d is invalid.\n", i + 1);
        }
    }

    return 0;
}

