
#define _FILE_OFFSET_BITS 32
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) 
{
    off_t offset;
    long longvar;
    long long longlongvar;

    // printf("%s",sizeof(off_t));
    printf("%i\n",sizeof(off_t));
    printf("%d\n",sizeof(long long));
    return 0;
    // exit(EXIT_SUCCESS);
}
