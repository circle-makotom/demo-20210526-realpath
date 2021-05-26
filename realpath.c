#include <stdlib.h> // where realpath is defined

#include <stdio.h>

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

int do_realpath(char *path)
{
    char real[PATH_MAX];

    printf("realpath'ing %s...\n", path);
    if (!realpath(path, real))
    {
        printf("realpath failed: %d\n", errno);
        return 1;
    }

    printf("realpath is: %s\n", real);

    return 0;
}

// wrapper to call do_realpath with intended options
int wrapper(char *path)
{
    int ret = 0;
    char path_trailing[strlen(path) + 1];

    sprintf(path_trailing, "%s/", path);

    ret += do_realpath(path);
    printf("\n");
    ret += do_realpath(path_trailing);

    return ret > 0;
}

// bootstrapping & testing arguments
int main(int argc, char *argv[])
{
    struct stat st;

    if (
        argc < 2 ||
        stat(argv[1], &st) == -1 ||
        !S_ISDIR(st.st_mode) ||
        (strlen(argv[1]) > 1 && argv[1][strlen(argv[1]) - 1] == '/')) // gimmick to accept `/` but not `/example/`
    {
        printf("pass the path to an existing directory as the first argument - without a trailing /\n");
        return 1;
    }

    return wrapper(argv[1]);
}
