#include <stdio.h>
#include <string.h>

#define MAXLINES 5
#define MAXLEN 100

int main() {
	char lines[MAXLINES][MAXLEN];
	int i = 0, j = 0;
	
	while (i < MAXLINES) {
		fgets(lines[i], MAXLEN, stdin);
		lines[i][strcspn(lines[i], "\n")] = '\0';
		i++;
	}

	for (i = 0; i < MAXLINES - 1; i++) {
		for (j = 0; j < MAXLINES -i -1; j++) {
			if (strlen(lines[j]) < strlen(lines[j + 1])) {
				char temp[MAXLEN];
				strcpy(temp, lines[j]);
				strcpy(lines[j], lines[j + 1]);
				strcpy(lines[j + 1], temp);
			}
		}
	}

	for (i = 0; i < MAXLINES; i++) {
		printf("%s\n", lines[i]);
	}

	return 0;
}


