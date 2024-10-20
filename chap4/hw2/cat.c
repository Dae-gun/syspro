#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(const char *filename, int line_numbers) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror(".");
        return;
    }

    char ch;
    int line_number = 1;

    if (line_numbers) {
        printf("%d ", line_number);
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
        if (ch == '\n') {
            if (line_numbers) {
                line_number++;
                printf("%d ", line_number);
            }
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int line_numbers = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            line_numbers = 1;
        } else {
            print_file(argv[i], line_numbers);
        }
    }

    return EXIT_SUCCESS;
}

