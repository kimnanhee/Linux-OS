#include <stdio.h>
struct a
{
	char c;
};
struct b
{
	char c;
	long l;
};
struct c
{
	char c;
	long l;
	int i;
};

int main()
{
	printf("%ld %ld %ld", sizeof(struct a), sizeof(struct b), sizeof(struct c));
	return 0;
}
