#include <stdio.h>
#include <stdlib.h>

#define SIZE 140

void read_matrix(const char *filename, char matrix[SIZE][SIZE]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = fgetc(file);
        }
        fgetc(file);
    }
    fclose(file);
}

int search_xmas(char matrix[SIZE][SIZE]) {
    int count_xmas = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == 'X') {
                if (i - 3 >= 0) {
                    if (matrix[i - 1][j] == 'M' && matrix[i - 2][j] == 'A' &&
                        matrix[i - 3][j] == 'S') {
                        count_xmas++;
                    }
                }
                if (i + 3 < SIZE) {
                    if (matrix[i + 1][j] == 'M' && matrix[i + 2][j] == 'A' &&
                        matrix[i + 3][j] == 'S') {
                        count_xmas++;
                    }
                }
                if (j - 3 >= 0) {
                    if (matrix[i][j - 1] == 'M' && matrix[i][j - 2] == 'A' &&
                        matrix[i][j - 3] == 'S') {
                        count_xmas++;
                    }
                }
                if (j + 3 < SIZE) {
                    if (matrix[i][j + 1] == 'M' && matrix[i][j + 2] == 'A' &&
                        matrix[i][j + 3] == 'S') {
                        count_xmas++;
                    }
                }
                if (i - 3 >= 0 && j - 3 >= 0) {
                    if (matrix[i - 1][j - 1] == 'M' &&
                        matrix[i - 2][j - 2] == 'A' &&
                        matrix[i - 3][j - 3] == 'S') {
                        count_xmas++;
                    }
                }
                if (i + 3 < SIZE && j + 3 < SIZE) {
                    if (matrix[i + 1][j + 1] == 'M' &&
                        matrix[i + 2][j + 2] == 'A' &&
                        matrix[i + 3][j + 3] == 'S') {
                        count_xmas++;
                    }
                }
                if (i - 3 >= 0 && j + 3 < SIZE) {
                    if (matrix[i - 1][j + 1] == 'M' &&
                        matrix[i - 2][j + 2] == 'A' &&
                        matrix[i - 3][j + 3] == 'S') {
                        count_xmas++;
                    }
                }
                if (i + 3 < SIZE && j - 3 >= 0) {
                    if (matrix[i + 1][j - 1] == 'M' &&
                        matrix[i + 2][j - 2] == 'A' &&
                        matrix[i + 3][j - 3] == 'S') {
                        count_xmas++;
                    }
                }
            }
        }
    }
    return count_xmas;
}

int search_mas(char matrix[SIZE][SIZE]) {
    int count_mas = 0;
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            if (matrix[i][j] == 'A') {
                if (matrix[i - 1][j - 1] == 'M' &&
                    matrix[i - 1][j + 1] == 'M' &&
                    matrix[i + 1][j - 1] == 'S' &&
                    matrix[i + 1][j + 1] == 'S') {
                    count_mas++;
                } else if (matrix[i - 1][j - 1] == 'S' &&
                           matrix[i - 1][j + 1] == 'S' &&
                           matrix[i + 1][j - 1] == 'M' &&
                           matrix[i + 1][j + 1] == 'M') {
                    count_mas++;
                } else if (matrix[i - 1][j - 1] == 'M' &&
                           matrix[i - 1][j + 1] == 'S' &&
                           matrix[i + 1][j - 1] == 'M' &&
                           matrix[i + 1][j + 1] == 'S') {
                    count_mas++;
                } else if (matrix[i - 1][j - 1] == 'S' &&
                           matrix[i - 1][j + 1] == 'M' &&
                           matrix[i + 1][j - 1] == 'S' &&
                           matrix[i + 1][j + 1] == 'M') {
                    count_mas++;
                }
            }
        }
    }
    return count_mas;
}

int main() {
    char matrix[SIZE][SIZE];

    read_matrix("input-4.txt", matrix);
    int total_xmas = search_xmas(matrix);
    int total_mas = search_mas(matrix);
    printf("Total XMAS: %d\n", total_xmas);
    printf("Total MAS: %d\n", total_mas);
    return 0;
}
