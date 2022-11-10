/*
This exercise is designed to demonstrate why the atomicity 
guaranteed by opening a file with the O_APPEND flag is necessary. 
Write a program that takes up to three command-line arguments:

    $ atomic_append filename num-bytes [x]

This program should open the specified filename (creating it if 
necessary) and append num-bytes bytes to the file by using write()
to write a byte at a time. By default, the program should open 
the file with the O_APPEND flag, but if a third command-line 
argument (x) is supplied, then the O_APPEND flag should be omitted, 
and instead the program should perform an lseek(fd, 0, SEEK_END) 
call before each write(). Run two instances of this program at 
the same time without the x argument to write 1 million bytes 
to the same file:

    $ atomic_append f1 1000000 & atomic_append f1 1000000

Repeat the same steps, writing to a different file, but this time 
specifying the x argument:
    
    $ atomic_append f2 1000000 x & atomic_append f2 1000000 x

List the sizes of the files f1 and f2 using ls -l and explain the difference.
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char *argv[])
{

    int fd, numBytes;

    if (argc < 3 || strcmp(argv[1], "--help")==0) {
        usageErr("%s <file> <num-bytes>", argv[0]);
    }

    numBytes = atol(argv[2]);

    if (argc == 3) {
        fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY, 
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        for (int i=0; i<numBytes; i++) {
            write(fd, "x", 1);
        }
    } else if (argc == 4) {
        fd = open(argv[1], O_CREAT | O_WRONLY,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        lseek(fd, 0, SEEK_END);
        for (int i=0; i<numBytes; i++) {
            write(fd, "x", 1);
        }
    }

    exit(EXIT_SUCCESS);

}