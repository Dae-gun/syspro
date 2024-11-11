#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64

void execute_command(char **args, int background) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
    } else {
        if (!background) {
            wait(NULL);
        }
    }
}

void run_shell() {
    char cmd[MAX_CMD_LENGTH];
    char *args[MAX_ARGS];
    
    while (1) {
        printf("[Shell] ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            perror("fgets failed");
            break;
        }

        cmd[strcspn(cmd, "\n")] = 0;

        if (strlen(cmd) == 0) {
            continue;
        }

        char *cmd_copy = strdup(cmd);
        char *token;
        token = strtok_r(cmd_copy, ";", &cmd_copy);

        while (token != NULL) {
            char *args_copy[MAX_ARGS];
            int i = 0;
            int background = 0;

            token = strtok_r(token, " \t", &token);
            while (token != NULL) {
                if (strcmp(token, "&") == 0) {
                    background = 1;
                    break;
                }
                args_copy[i++] = token;
                token = strtok_r(NULL, " \t", &token);
            }
            args_copy[i] = NULL;

            execute_command(args_copy, background);
            token = strtok_r(cmd_copy, ";", &cmd_copy);
        }

        free(cmd_copy);
    }
}

int main() {
    run_shell();
    return 0;
}

