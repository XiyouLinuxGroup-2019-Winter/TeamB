#include<stdio.h>
int main()
{
    char str[1000000];
    char *p[5000];
    int i=0,p=0,q,h=0;
    while((scanf("%c",&str[i]))!=EOF);
    i++;
    for(q=0;q<i;q++)
    {
        if(str[q]!=' ')
        {
        p[p][h]==str[q];
        h++;
        printf("%c",p[p][h]);
        }
        else
        {
        h=0;
        p++;
        }
    }
    for(q=0;q<p;q++)
    printf("%s\n",p[q]);
}

