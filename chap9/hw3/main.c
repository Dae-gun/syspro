#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64

int parse_command(char *cmd, char **args) {
    int i = 0;
    char *token = strtok(cmd, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return i;
}

void execute_command(char **args) {
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
        wait(NULL);
    }
}

void execute_background(char **args) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
    }
}

void handle_redirection(char **args) {
    int i = 0;
    int input_redirect = -1, output_redirect = -1;
    char *input_file = NULL, *output_file = NULL;

    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0) {
            input_redirect = i;
            input_file = args[i + 1];
            args[i] = NULL;
        } else if (strcmp(args[i], ">") == 0) {
            output_redirect = i;
            output_file = args[i + 1];
            args[i] = NULL;
        }
        i++;
    }

    if (input_redirect != -1) {
        int fd = open(input_file, O_RDONLY);
        if (fd == -1) {
            perror("input file open failed");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (output_redirect != -1) {
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("output file open failed");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void run_shell() {
    char cmd[MAX_CMD_LENGTH];
    char *args[MAX_ARGS];
    
    while (1) {
        printf("[shell] ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            perror("fgets failed");
            break;
        }

        cmd[strcspn(cmd, "\n")] = 0;

        if (strlen(cmd) == 0) {
            continue;
        }

        char *cmd_copy = strdup(cmd);
        char *token = strtok(cmd_copy, ";");
        while (token != NULL) {
            parse_command(token, args);

            int background = 0;
            int len = 0;
            while (args[len] != NULL) {
                if (strcmp(args[len], "&") == 0) {
                    background = 1;
                    args[len] = NULL;
                    break;
                }
                len++;
            }

            handle_redirection(args);

            if (background) {
                execute_background(args);
            } else {
                execute_command(args);
            }

            token = strtok(NULL, ";");
        }
        free(cmd_copy);
    }
}

int main() {
    run_shell();
    return 0;
}

