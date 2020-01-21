/*************************************************************************
	> File Name: 16.1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月19日 星期日 15时45分41秒
 ************************************************************************/

#include<stdio.h>
#define psqr(x) printf("the square of "#x" is %d.\n",((x)*(x)))

int main()
{
    int y = 5;

    psqr(y);
    psqr(y + 2);

    return 0;
}
