#include<stdio.h>
int main()
{
    int m,n,a[10000],h,b[10000],c[10000],q,w,e,k,i;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    for(i=0,h=10;i<m;h*=10,i++)
    {
    for(k=0;k<n;k++)
    {
        b[k]=(a[k]%h)/(h/10);
    }
    for(q=0;q<n;q++)
        for(w=q+1;w<n;w++)
        if(b[q]<b[w])
        {
            e=b[q];
            b[q]=b[w];
            b[w]=e;
        }
    for(q=0;q<n;q++)
        if(b[q]!=b[q+1])
           break;
          for(w=0;w<q;w++)
            c[w]=c[w];
    }
        for(i=0;i<n;i++)
          printf("%d",c[i]);
}

