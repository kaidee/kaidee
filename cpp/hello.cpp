#include<stdio.h>
// #include "square.h"

int square(int x)
{
	return x*x;
}

int main(void)
{
	printf("Hello, SConse!\n");
	printf("Five squared is: %i\n", square(5));
	return 0;
}
