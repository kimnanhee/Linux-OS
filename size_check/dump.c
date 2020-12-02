#include <stdio.h>
#include <string.h>
void dumpMsg(char *X, int size)
{
	printf("================\n");
	printf("0123456701234567 0123456701234567\n");
	printf("----------------\n");

	for(int k=0; k<size; k++)
	{
		if(k%16 == 0) printf("\n");
		printf("%02X", (int)*X);
		if((k+1)%8 == 0) printf(" ");
	}
	printf("\n==================\n");
}
struct abc
{
	char c;
	long l;
	int i;
};
int main()
{
	struct abc a;
	memset((char*)&a, 0, sizeof(struct abc));
	a.c = 0x01;
	a.l = 0x0102030405060708;
	a.i = 0x01020304;
	dumpMsg((char*)&a, sizeof(struct abc));
	printf("%ld\n", sizeof(struct abc));
	return 0;
}
