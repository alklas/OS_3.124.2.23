#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd, result;
	size_t size;
	char string[] = "Gr.3.124.2.23", resstring[13];
	char name[] = "fifo.fifo";
	/*
	if(mknod(name, S_IFIFO | 0666, 0) < 0) {
		printf("Не удаётся создать FIFO\n");
		exit(-1);
	}
	*/
	if((result = fork()) < 0) {
		printf("Не удалось создать дочерний процесс\n");
		exit(-1);
	}
	else if (result > 0) {
		if((fd = open(name, O_WRONLY)) < 0) {
			printf("Не удалось открыть FIFO на запись\n");
			exit(-1);
		}
		size = write(fd, string, 13);
		if(size != 13) {
			printf("Не удалось записать строку целиком\n");
			exit(-1);
		}
		close(fd);
		printf("Строка записана в FIFO, процесс-родитель завершает работу\n");
	}
	else {
		if((fd = open(name, O_RDONLY)) < 0) {
			printf("Не удаётся открыть FIFO на чтение\n");
			exit(-1);
		}
		size = read(fd, resstring, 13);
		if (size != 13) {
			printf("Не удалось прочитать всю строку\n");
			exit(-1);
		}
		printf("Дочерний процесс прочитал строку: %s\n", resstring);
		close(fd);
	}
	return 0;
}
