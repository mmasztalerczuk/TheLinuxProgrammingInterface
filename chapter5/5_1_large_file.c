#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	int fd;
	off64_t off;

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
	{	
		printf("%s pathname offset\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	if (fd == -1)
		exit(EXIT_FAILURE);;
	off = atoll(argv[2]);

	if (lseek(fd, off, SEEK_SET) == -1)
		exit(EXIT_FAILURE);

	if (write(fd, "test", 4) == -1)
		exit(EXIT_FAILURE);

	exit(0);
}
