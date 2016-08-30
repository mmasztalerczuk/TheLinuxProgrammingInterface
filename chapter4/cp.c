#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

#define BUFF_SIZE 1024

int
main(int argc, char *argv[])
{
	char            buff[BUFF_SIZE];
    int fd_source, fd_target, buff_size;

    if (argc == 1)
    {
        char msg[] = "cp: missing file operand";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(EXIT_FAILURE);
    }
    else if (argc == 2)
    {
        char msg[] = "cp: missing destination file operand";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(EXIT_FAILURE);
    }
    else
    {
	    fd_source = open(argv[1], O_RDONLY, DEFFILEMODE);

        if (fd_source < 1)
        {
            perror("File Open Error Source");
            exit(EXIT_FAILURE);
        }
       
        fd_target = open(argv[2], O_WRONLY | O_CREAT, DEFFILEMODE);

	    if (fd_target < 1)
        {
            perror("File Open Error Source");
            exit(EXIT_FAILURE);
        }
    
        while (buff_size = read(fd_source, buff, BUFF_SIZE))
        {
            if (buff_size == -1)
            {
                perror("File Read Error");
                exit(EXIT_FAILURE);
            }

            if (write(fd_target, buff, buff_size) < 0)
            {
                perror("File Write Error");
                exit(EXIT_FAILURE);
            }
        }    
    
        if (close(fd_target) == -1)
        {
            perror("Target closing error");
            exit(EXIT_FAILURE);
        }
    
        if (close(fd_source) == -1)
        {
            perror("Source closing error");
            exit(EXIT_FAILURE);
        }
    }
	return 0;
}
