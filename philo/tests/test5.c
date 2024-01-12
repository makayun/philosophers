#include <stdio.h>

// DOESN'T WORK LIKE THIS!!!

typedef struct test5
{
	int one;
	int two;
	int three;
}				t_test5;


int main()
{
	int i = 0;
	struct test5 test;

	while (i < 3)
	{
		test[i] = i;
		printf ("%d %d\n", test[i], i);
 	}
}
