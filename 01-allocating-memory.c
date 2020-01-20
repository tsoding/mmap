#include <assert.h>
#include <stdio.h>

#include <sys/mman.h>

#define N 10

int main(int argc, char *argv[])
{
    int *xs = mmap(NULL, N * sizeof(int),
                   PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS,
                   0, 0);
    assert(xs != MAP_FAILED);

    assert(N >= 2);
    xs[0] = 0;
    xs[1] = 1;

    for (int i = 2; i < N; ++i) {
        xs[i] = xs[i - 1] + xs[i - 2];
    }

    int err = munmap(xs, N * sizeof(int));
    assert(err >= 0);

    return 0;
}
