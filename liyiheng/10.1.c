#include<stdio.h>


void lll(double ar[], double a[],int n);
void ccc(double *a, double *b,int n);
void ddd(double *a, double *b,double *c);

int main()
{
    int i;
    double x[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double p1[5];
    double p2[5];
    double p3[5];

    lll(p1, x, 5);

    ccc(p2, x, 5);

    ddd(p3, x,x+5);

    for(i = 0; i < 5; i++)
    {
        printf("p3[%d] = %.2lf", i, p3[i]);
        printf("\n");
    }

    return 0;
}

void lll(double ar[], double a[],int n)
{
    int i;
    for(i = 0; i< n; i++)
        ar[i] = a[i];
    for(i = 0; i< n; i++)
    {
        printf("p1[%d] = %.2lf", i, ar[i]);
        printf("\n");
    }
}

void ccc(double *a, double *b,int n)
{
    int i;
    for(i = 0; i< n; i++)
        *(a+i) = *(b+i);
    for(i = 0; i< n; i++)
    {
        printf("p2[%d] = %.2lf", i, a[i]);
        printf("\n");
    }
}

void ddd(double *a, double *b,double *c)
{
    while(b<c)
    {
        *a = *b;
        b++;
        a++;
    }
}


