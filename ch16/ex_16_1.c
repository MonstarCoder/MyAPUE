#include <stdio.h>

int main()
{
    int a = 1;
    char* test = (char*)&a;

    if (*test)
        printf("little-endian\n");
    else
        printf("big-endian\n");

    return 0;
}
