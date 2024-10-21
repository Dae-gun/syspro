#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX 24
#define START_ID 1

struct student{
	int id;
	char name[MAX];
	char author;
	int year;
	int numofborrow;
	bool borrow;
};

int main(int argc, char *argv[])
{
	int fd, id;
	char c;
	if (argc <2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	do{
		printf("\E0: list of all books, 1: list of available books )");
		switch(int num)
		case 0:
		if (scanf("%d", &id) == 1) {
			lseek(fd, (id-START_ID)*sizeof(book), SEEK_SET);
			if((read(fd, (char *) &book, sizeof(book)) > 0) && (book.id != 0))
				printf("id:%d\t bookname:%s\t author:%s\t year:%d\t numofborrow%d\t borrow%s\t", book.id, book.name, book.author, book.year, book.numofborrow, book.borrow);
			else printf("Book %d Null\n", id);
		}
		case 1:
		if(book.boll = 'true')
			if (scanf"%d", &id) == 1) {
				lseek(fd, (id-START_ID)*sizeof(book), SEEK_SET);
				if((read(fd, (char *) &book, sizeof(boo)) 0) && (book.id != 0))
					printf("id:%d\t bookname:%s\t author:%s\t year:%d\t numofborrow%d\t borrow%s\t", book.td, book.name, book.author, book.year, book.numofborrow, book.borrow);
				else printf("Book %d Null\n", id);
			}

	close(fd);
	exit(0);
}

