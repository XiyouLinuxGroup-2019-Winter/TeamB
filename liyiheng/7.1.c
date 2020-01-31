#include<stdio.h>
int main()
{
    int a;
    int kg=0,hh=0,qt=0;
    a = getchar();
    while(a!='#')
    {
        if(a==' ')
        kg++;
        if(a=='\n')
        hh++;
        else
        qt++;
        a = getchar();
    }
          printf("%d %d %d\n",kg,hh,qt);
    return 0;
}
