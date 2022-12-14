/*
Modify the program in Example 5-3 to use standard file I/O system calls 
(open() and lseek()) and the off_t data type. Compile the program with 
the _FILE_OFFSET_BITS macro set to 64, and test it to show that a large 
file can be successfully created.

Listing 5-3

    large_file.c

    Demonstrate the use of the (obsolete) Large File System API.

    This program is Linux-specific.
*/

/*
#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd;
    off64_t off;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname offset\n", argv[0]);

    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open64");

    off = atoll(argv[2]);
    if (lseek64(fd, off, SEEK_SET) == -1)
        errExit("lseek64");

    if (write(fd, "test", 4) == -1)
        errExit("write");
    exit(EXIT_SUCCESS);
}
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "../../tlpi-dist/lib/tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd;
    off_t off;

    if (argc!=3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s pathname offset\n", argv[0]);
    }

    fd = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd==-1) {
        errExit("open");
    }

    off = atoll(argv[2]);
    if (lseek(fd, off, SEEK_SET)==-1) {
        errExit("lseek");
    }

    if (write(fd, "test", 4) == -1) {
        errExit("write");
    }
       
    exit(EXIT_SUCCESS);
}