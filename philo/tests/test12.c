#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#define STRING "ottffssent\n"

int main()
{
    int i;
    struct timeval start;
    struct timeval end;
    struct timeval start2;
    struct timeval end2;
    struct timeval start3;
    struct timeval end3;

    i = 10000;
    gettimeofday(&start, NULL);
    while (i--)
        printf("%s", STRING);
    gettimeofday(&end, NULL);

    i = 10000;
    gettimeofday(&start2, NULL);
    while (i--)
        printf("%s", "ottffssent\n");
    gettimeofday(&end2, NULL);

    i = 10000;
    gettimeofday(&start3, NULL);
    while (i--)
        write (1, "ottffssent\n", 11);
    gettimeofday(&end3, NULL);

    printf ("%ld\n", (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
    printf ("%ld\n", (end2.tv_sec * 1000000 + end2.tv_usec) - (start2.tv_sec * 1000000 + start2.tv_usec));
    printf ("%ld\n", (end3.tv_sec * 1000000 + end3.tv_usec) - (start3.tv_sec * 1000000 + start3.tv_usec));
}