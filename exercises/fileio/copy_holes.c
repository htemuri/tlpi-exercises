/*
Write a program like cp that, when used to copy a regular file
that contains holes (sequences of null bytes), also creates 
corresponding holes in the target file.
*/

/*

copy file1 to file2

1. read f1
2. create file2 if not already exists with rw-rw-rw
3. get length of read f1 using getLong()
if isprint(byte) -> write to file else seek right one
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../../tlpi-dist/lib/tlpi_hdr.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif


int main(int argc, char *argv[]) {

    int fd, openFlags, wd;
    char buffer[BUFFER_SIZE];
    mode_t filePerms;
    size_t numRead;

    if (argc!=3 || strcmp(argv[1], "--help")==0) {
        usageErr("%s {file1} {file2}", argv[0]);
    }

    fd = open(argv[1], O_RDONLY); /* file 1 */
    if (fd==-1) {
        errExit("cant read %s", argv[1]);
    }

    /* open file 2 for write */
    openFlags = O_CREAT | O_WRONLY | O_TRUNC | O_APPEND;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    wd = open(argv[2], openFlags, filePerms);

    /* read file 1 and write to f2 as buffer fills up */
    // trueLength = getLong(fd)
    while ((numRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(wd, buffer, numRead);
    }
    close(fd);
    close(wd);
    exit(EXIT_SUCCESS);
}
