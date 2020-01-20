#include <assert.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    assert(argc >= 2);
    const char *filepath = argv[1];

    int fd = open(filepath, O_RDWR);
    assert(fd >= 0);

    struct stat statbuf;
    int err = fstat(fd, &statbuf);
    assert(err >= 0);

    void *ptr = mmap(NULL, statbuf.st_size,
                     PROT_EXEC,
                     MAP_PRIVATE,
                     fd, 0);
    assert(ptr != MAP_FAILED);
    close(fd);

    ((void (*)(void))ptr)();

    printf("We are back!\n");

    return 0;
}
