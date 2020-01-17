/*************************************************************************
	> File Name: 14.1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月17日 星期五 21时08分59秒
 ************************************************************************/

#include<stdio.h>
struct day{
    int m;
    int d;
};
int days(struct day *p);
void main()
{
    struct day y;
    scanf("%d.%d",&y.m,&y.d);
    struct day* p = &y;
    printf("%d",days(p));
}
int days(struct day *p)
{
    int n;
    if(p->m==2){
        n=31+p->d;
        return n;
    }
}
