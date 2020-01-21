#include<stdio.h>
int main()
{
    int a,b,c;
   
    
         printf("This program computes moduli.\n");
         printf("Enter an integer to serve as the second operand:\n");
         scanf("%d",&a);
         printf("Now enter the first operand:\n");
         scanf("%d",&b);
         c=b%a;
         printf("%d %% %d is %d\n",b,a,c);
         printf("Enter next number for first operand (<= 0 to quit): \n");
         scanf("%d",&b);
       while(b>0)
         {
             
			printf("%d %% %d is %d\n",b,a,c);
			printf("Enter next number for first operand (<= 0 to quit): \n");
			scanf("%d",&first_operand);
		}

	printf("Done\n");
         
}
