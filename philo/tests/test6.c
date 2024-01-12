#include <stdio.h>

long change_me(long i)
{
	i = 52;
	return (i);
}

int main()
{
	long i = 42;

	int j = change_me(i);
	printf("%d", j);
}
