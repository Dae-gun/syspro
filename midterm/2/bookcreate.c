#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX 24
#define START_ID 1

struct book {
	int id;
	char bookname[MAX];
	char author;
	int year;
	int numofborrow;
	bool borrow;

	int main(int argc, char *argv[])
	{
		int fd;
		if(argc <2) {
			fprintf(stderr, "How to use: %s file\n", argv[0]);
			exit(1);
		}
		if((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1){
			perror(argv[1]);
			exit(2);
		}
		printf("%-2s %-20s %-20s %-4s %-2s %s\n", "id", "bookname", "author", "year", "numofborrow", "borrow", boow ? "true" : "false");
		while (scanf("%d %s %s %s %d %s", &book.id, &book.bookname, &book.author, &book.year, &book.numofborrow, &book.borrow) == 7){
			lseek(fd, (book.id - START_ID) * sizeof(book), SEEK_SET);
			write(fd, (char *) &book, sizeof(book));
		}
		close(fd);
		exit(0);
	}

