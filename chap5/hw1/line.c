#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 10
#define MAX_LENGTH 100

char savedText[MAX_LINES][MAX_LENGTH];

void loadFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) exit(1);

    char buf;
    int row = 0, col = 0;
    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
        } else {
            savedText[row][col++] = buf;
        }
        if (row >= MAX_LINES) break;
    }
    close(fd);
}

void printLine(int lineNum) {
    if (lineNum >= 0 && lineNum < MAX_LINES && savedText[lineNum][0] != '\0')
        printf("%d: %s\n", lineNum + 1, savedText[lineNum]);
}

void printLineList(char* input) {
    char* token = strtok(input, ",");
    while (token) {
        printLine(atoi(token) - 1);
        token = strtok(NULL, ",");
    }
}

void printLineRange(int start, int end) {
    for (int i = start - 1; i < end; i++)
        printLine(i);
}

void printAllLines() {
    for (int i = 0; i < MAX_LINES && savedText[i][0] != '\0'; i++)
        printLine(i);
}

int main() {
    char input[100];
    loadFile("test.txt");

    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';

    if (strcmp(input, "*") == 0) printAllLines();
    else if (strchr(input, ',') != NULL) printLineList(input);
    else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        printLineRange(start, end);
    } else printLine(atoi(input) - 1);

    return 0;
}

