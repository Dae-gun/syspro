#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

char savedText[MAX_LINES][MAX_LENGTH];

void loadFile(const char* filename, int* lineCount) {
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
    *lineCount = row;
    close(fd);
}

void printReverseLines(int lineCount) {
    for (int i = lineCount - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }
}

int main() {
    int lineCount = 0;
    loadFile("test.txt", &lineCount);
    printReverseLines(lineCount);
    return 0;
}

