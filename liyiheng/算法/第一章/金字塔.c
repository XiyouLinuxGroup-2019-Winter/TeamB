#include <stdio.h>

void pyramid( int n  );

int main()
{    
    int n;

    scanf("%d", &n);
    pyramid(n);

    return 0;
}

void pyramid(int n)
{
    int i,j,k,m;
    m = n;

    
    for(i = 1;i <= m;i++)
    {
       for(j = m - i;j > 0;j--)
        
           printf(" ");
        
        for(k = 1;k <= i;k++)
        {
            printf("%d",i);
        }
      printf("\n");    
    }
    
}

