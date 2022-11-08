#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>
#ifndef MAX_READ
#define MAX_READ 20
#endif

int main() {
    char buffer[MAX_READ + 1];
    ssize_t numRead;
    // int fd = open("t1", O_RDONLY);
    numRead = read(STDIN_FILENO, buffer, MAX_READ);
    if (numRead==-1) {
        errExit("read");
    }

    buffer[numRead] = '\0';

    printf("the input data was: %s\n", buffer);

    // close(fd);

}