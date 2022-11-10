/*
Implement dup() and dup2() using fcntl() and, where necessary, 
close(). (You may ignore the fact that dup2() and fcntl() 
return different errno values for some error cases.) For dup2(), 
remember to handle the special case where oldfd equals newfd. 
In this case, you should check whether oldfd is valid, which 
can be done by, for example, checking if fcntl(oldfd, F_GETFL) 
succeeds. If oldfd is not valid, then the function should return 
-1 with errno set to EBADF.
*/

/*
dup() duplicates the open file descriptor to the lowest available file descriptor number
dup2() duplicated the open file descriptor to a specified file descriptor if available

inner workings of dup() -> 
    flags = fcntl get flags of fd
    newfd = fcntl(fd)
*/

#include <fcntl.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

int duplicate(int fd) {
    int newFd;
    newFd = fcntl(fd, F_DUPFD);
    if (newFd==-1) {
        errExit("fcntl");
    }
    return newFd;
}

int duplicate2(int fd, int dd) {
    
}

int main(int argc, char *argv[]) {
    int fd;

    

}


