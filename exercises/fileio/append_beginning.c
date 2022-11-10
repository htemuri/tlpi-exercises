/*
Write a program that opens an existing file for writing 
with the O_APPEND flag, and then seeks to the beginning 
of the file before writing some data. Where does the 
data appear in the file? Why?
*/

/*
sample input: ./append_beginning t1
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd;
    off_t origOffset;

    if (argc!=2 || strcmp(argv[1], "--help")==0) {
        usageErr("%s <file>", argv[0]);
    }

    fd = open(argv[1], O_RDWR | O_APPEND);

    if (fd==-1) {
        errExit("open");
    }
    origOffset = lseek(fd, 0, SEEK_CUR);
    printf("%ldd before\n", origOffset);
    /* seek to the zero offset*/
    if (lseek(fd, 0, SEEK_SET)==-1) {
        errExit("seek");
    }
    origOffset = lseek(fd, 0, SEEK_CUR);
    printf("%ldd after\n", origOffset);


    if (write(fd, "appendTest\0", 12)==-1) {
        errExit("write");
    }

    if (close(fd)==-1) {
        errExit("close");
    }

    exit(EXIT_SUCCESS);

}