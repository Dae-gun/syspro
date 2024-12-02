#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe1[2];
    int pipe2[2];
    pid_t pid;
    char parentMessage[] = "Hello from PID 100";
    char childMessage[] = "Hello from PID 1101";
    char buffer[100];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        return 1;
    }
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1], parentMessage, strlen(parentMessage) + 1);
        printf("Send: [100] %s\n", parentMessage);

        read(pipe2[0], buffer, sizeof(buffer));
        printf("Recv: [1101] %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    } else {
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], buffer, sizeof(buffer));
        printf("Recv: [100] %s\n", buffer);

        write(pipe2[1], childMessage, strlen(childMessage) + 1);
        printf("Send: [1101] %s\n", childMessage);

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}

