#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 256

void print_lines(char lines[][MAX_LENGTH], int total_lines, char *input) {
    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < total_lines; i++) {
            printf("%d: %s", i + 1, lines[i]);
        }
    } else {
        char *token = strtok(input, ",");
        while (token != NULL) {
            if (strchr(token, '-') != NULL) {

                int start, end;
                sscanf(token, "%d-%d", &start, &end);
                for (int i = start - 1; i < end; i++) {
                    if (i >= 0 && i < total_lines) {
                        printf("%d: %s", i + 1, lines[i]);
                    }
                }
            } else {
                
				int line_num = atoi(token);
                if (line_num > 0 && line_num <= total_lines) {
                    printf("%d: %s", line_num, lines[line_num - 1]);
                }
            }
            token = strtok(NULL, ",");
        }
    }
}

int main() {
    FILE *file;
    char lines[MAX_LINES][MAX_LENGTH];
    int total_lines = 0;

    file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("file open error");
        return 1;
    

    
		while (fgets(lines[total_lines], MAX_LENGTH, file) != NULL && total_lines < MAX_LINES) {
        total_lines++;
    }
    fclose(file);

    char input[256];

    // 사용자 입력 루프
    while (1) {
        printf(" (": 1, 3-5, *, 종료는 'exit'): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        print_lines(lines, total_lines, input);
    }

    return 0;
}

