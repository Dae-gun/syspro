#include <stdio.h>
#include <stdlib.h>

void append_to_file(const char *source_file, const char *dest_file) {
    FILE *source, *dest;
    char ch;
    source = fopen(source_file, "r");
    if (source == NULL) {
        perror("open fail");
        exit(EXIT_FAILURE);
    }

    dest = fopen(dest_file, "a");
    if (dest == NULL) {
        perror("open fail¨");
        fclose(source);
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    printf("'..\n", source_file, dest_file);
    fclose(source);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, ".\n", argv[0]);
        return EXIT_FAILURE;
    }

    append_to_file(argv[1], argv[2]);
    return EXIT_SUCCESS;
}

