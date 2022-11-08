/*
The tee command reads its standard input until end-of-file, writing a copy of 
the input to standard output and to the file named in its command-line argument. 
(We show an example of the use of this command when we discuss FIFOs in Section 44.7.) 
Implement tee using I/O system calls. By default, tee overwrites any existing 
file with the given name. Implement the -a command-line option (tee -a file), 
which causes tee to append text to the end of a file if it already exists. (Refer 
to Appendix B for a description of the getopt() function, which can be used to 
parse command-line options.)
*/

/*
Things to do:
    1. optional arg for file (if not specified)
        1. return std out from std in
        2. loop forever until exit signal
    2. 2 args -> 2nd is file name
        1. create file if not exist, trunc
    3. 3 args -> a flag
        1. create file if not exist, just append
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../../tlpi-dist/lib/tlpi_hdr.h"
#ifndef MAX_SIZE
#define MAX_SIZE 1024
#endif


int main(int argc, char *argv[]) {

    int fd, openFlags; /* file descriptor of target file*/
    mode_t filePerms;
    ssize_t numRead;
    char buffer[MAX_SIZE + 1]; /* store stdin */


    /* check number of args */
    if (argc > 3 || strcmp(argv[1], "--help")==0) {
        usageErr("%s {{-a} file}...\n", argv[0]);
    }

    if (argc==2) {
        if (argv[1][0]=='-') {
            usageErr("%s {{-a} file}...\n", argv[0]);
        }
        /* open file -> create if not & overwrite */
        openFlags = O_CREAT | O_WRONLY | O_TRUNC | O_APPEND;
        filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw*/
        fd = open(argv[1], openFlags, filePerms);            
    }

    if (argc==3) {
        if (strcmp(argv[1],"-a")!=0) {
            usageErr("%s {{-a} file}...\n", argv[0]);
        }
        openFlags = O_CREAT | O_WRONLY | O_APPEND;
        filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw*/
        fd = open(argv[2], openFlags, filePerms);         
    }

    

    while (1) {
        /* read input, store in buffer*/
        numRead = read(STDIN_FILENO, buffer, MAX_SIZE);
        buffer[numRead] = '\n';

        /* write buffer to stdout*/
        
        if (write(STDOUT_FILENO, buffer, numRead)!=numRead) {
            fatal("partial write to stdout");
        }

        if (argc>1) {
            if (write(fd, buffer, numRead)!=numRead) {
                fatal("partial write to file");
            }
        }

    }
    close(fd);
    exit(EXIT_SUCCESS); 

}

