#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

    char *ptr = mmap(NULL, statbuf.st_size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE,
                     // MAP_SHARED,
                     fd, 0);
    assert(ptr != MAP_FAILED);
    close(fd);

    for (size_t i = 0; i < statbuf.st_size / 2; ++i) {
        int j = statbuf.st_size - i - 1;
        int t = ptr[i];
        ptr[i] = ptr[j];
        ptr[j] = t;
    }

    ssize_t n = write(1, ptr, statbuf.st_size);
    assert(n == statbuf.st_size);

    err = munmap(ptr, statbuf.st_size);
    assert(err >= 0);

    return 0;
}
