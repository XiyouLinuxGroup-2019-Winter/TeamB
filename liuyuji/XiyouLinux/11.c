/*************************************************************************
	> File Name: 11.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月02日 星期日 21时22分19秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    int a;
    int b = 2,c = 5;
    for(a = 1; a < 4; a++)
        {
            b=99;
            switch(a)
	        	{
                case 2:
                    printf("c is %d\n", c);
                    break;
                default:
                    printf("a is %d\n", a);
                case 1:
                    printf("b is %d\n", b);
                    break;
                }
        }
    return 0;
}
