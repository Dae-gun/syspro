#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

void print_env_variable(char *var_name) {
    char *value = getenv(var_name);
    if (value != NULL) {
        printf("%s=%s\n", var_name, value);
    } else {
        printf("Environment variable %s not found.\n", var_name);
    }
}

void print_all_env_variables() {
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void print_user_ids() {
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    printf("Real UID: %d\n", real_uid);
    printf("Effective UID: %d\n", effective_uid);
}

void print_group_ids() {
    gid_t real_gid = getgid();
    gid_t effective_gid = getegid();
    printf("Real GID: %d\n", real_gid);
    printf("Effective GID: %d\n", effective_gid);
}

void print_process_id() {
    pid_t pid = getpid();
    printf("Process ID: %d\n", pid);
}

void print_parent_process_id() {
    pid_t ppid = getppid();
    printf("Parent Process ID: %d\n", ppid);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-e<var_name> | -u | -g | -i | -p]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'e': 
                    if (argv[i][2] != '\0') {
                        print_env_variable(&argv[i][2]);
                    } else {
                        print_all_env_variables();
                    }
                    break;

                case 'u':
                    print_user_ids();
                    break;

                    break;

                case 'i':
                    print_process_id();
                    break;

                case 'p':
                    print_parent_process_id();
                    break;

                default:
                    fprintf(stderr, "Invalid option: %s\n", argv[i]);
                    return 1;
            }
        } else {
            fprintf(stderr, "Invalid argument format: %s\n", argv[i]);
            return 1;
        }
    }

    return 0;
}

