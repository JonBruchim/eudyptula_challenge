#include "stdio.h"

struct x {
	int a;
	int b;
	int c;
};

void main()
{
	struct x a;
	struct x b;
	a.a = 1;
	a.b = 2;
	a.c = 3;

	b.a = 7;
	b.b = 8;
	b.c = 9;

	printf("%d - %d - %d\n", a.a, a.b, a.c);
	printf("%d - %d - %d\n", b.a, b.b, b.c);
	b = a;
	printf("%d - %d - %d\n", b.a, b.b, b.c);

}