#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
     if (argc < 2) {
        fprintf(stderr, "%s: error: Wrong number of arguments. Expecting 3 arguments, red, green, and blue\n", argv[0]);
        abort();
    }
}