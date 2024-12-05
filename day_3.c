#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    FILE *file = fopen("input-3.txt", "r");

    int mul_sum = 0, domul_sum = 0;
    bool is_enabled = true;
    size_t buffer_size = 4096;
    char buffer[buffer_size];

    while (fgets(buffer, buffer_size, file)) {
        char *ptr = buffer;
        while (*ptr != '\0') {
            if (strncmp(ptr, "do()",  4) == 0) {
                ptr += 4;
                is_enabled = true;
            } else if (strncmp(ptr, "don't()", 7) == 0) {
                ptr += 7;
                is_enabled = false;
            } else if (strncmp(ptr, "mul(", 4) == 0) {
                ptr += 4;
                char num1[20], num2[20];

                char *start = ptr;
                while (*ptr && isdigit(*ptr)) ptr++;
                if (*ptr == ',' && ptr > start) {
                    strncpy(num1, start, ptr - start);
                    num1[ptr - start] = '\0';
                    ptr++;

                    start = ptr;
                    while (*ptr && isdigit(*ptr)) ptr++;
                    if (*ptr == ')' && ptr > start) {
                        strncpy(num2, start, ptr - start);
                        num2[ptr - start] = '\0';
                        ptr++;

                        printf("mul(%s, %s)\n", num1, num2);
                        mul_sum += atoi(num1) * atoi(num2);
                        if (is_enabled) {
                            domul_sum += atoi(num1) * atoi(num2);
                        }
                    }
                }
            } else {
                ptr++;
            }

        }
    }
    printf("Mul sum: %d\n", mul_sum);
    printf("Domul sum: %d\n", domul_sum);
    fclose(file);
}
