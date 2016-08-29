#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

#define BUFF_SIZE 1024

int
main(int argc, char *argv[])
{
	char            buff[BUFF_SIZE];
	int             fd, buff_size, app, opt, counter;

	app = 0;

	while ((opt = getopt(argc, argv, "a?")) != -1) {
		switch (opt) {
		case 'a':
			app = 1;
			break;
		case '?':
		default:
			fprintf(stderr, "Usage: %s [-a] file_name", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	fd = open(argv[optind],
		  app ? O_WRONLY | O_APPEND | O_CREAT : O_WRONLY | O_CREAT | O_TRUNC,
		  DEFFILEMODE);

    if (fd < 0) {
		perror("File Open Error");
		exit(EXIT_FAILURE);
	}

	while (buff_size = read(STDIN_FILENO, buff, BUFF_SIZE)) {
		if (buff_size == -1) {
			perror("File Read Error");
			exit(EXIT_FAILURE);
		}

		if (write(fd, buff, buff_size) < 0) {
			perror("File Write Error");
			exit(EXIT_FAILURE);
		}

		write(STDOUT_FILENO, buff, buff_size);
	}

	return 0;
}
