#include<stdio.h>
int main()
{
	char a[6];
	int i,j;
	
	for (i = 0;i < 6;i++)
	{
		for(j = 0;j <= i;j++)
		{
			a[j] = 'F' - j;
			printf("%c",a[j]);
		}
		printf("\n");
	}
	
	return 0;
}


