#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int num, int argc, char *argv[])
{
	int fd1, fd2, n;
	char but[BUFSIZ];

	FILE *fd1 = fopen(argc, "r");
	FILE *fd2 = fopen(*argv, "w");
	char c;
	switch(num){
		case 0:
			if(argc != 3){
				fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
				exit(1);
			}
			if((fd1 = open(argv[1], O_RDONLY)) == -1){
				perror(argv[1]);
				exit(2);
			}
			if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
				perror(argv[2]);
				exit(3);
			}
		case 1:
			while(1)
			{
				c = fgetc(fd1);
				if ( c == EOF)
					break;
				fputc(tolower(c), fd2);
			if (argc != 3){
         		fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
         		exit(1);
			}
     		if ((fd1 = open(argv[1], O_RDONLY)) == -1){
        		 perror(argv[1]);
         		exit(2);
    		}
     		if ((fd2 = open(argv[2], O_WRONLY | O_CREAT|O_TRUNC, 0644)) == -1){
        	 perror(argv[2]);
         	exit(3);
    		}
				fclose(fd1);
				fclose(fd2);
			}
		
		case 2:
			while(1)
			{
				c = fgetc(fd1);
				if (c == EOF)
					break;
				fputc(toupper(c), fd2);
			if (argc != 3){
         		fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
         		exit(1);
     		}
     		if ((fd1 = open(argv[1], O_RDONLY)) == -1){
         		perror(argv[1]);
         		exit(2);
     		}
     		if ((fd2 = open(argv[2], O_WRONLY | O_CREAT|O_TRUNC, 0644)) == -1){
         		perror(argv[2]);
         		exit(3);
     		}
				fclose(fd1);
				fclose(fd2);
}
