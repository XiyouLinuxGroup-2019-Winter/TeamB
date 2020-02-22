/*************************************************************************
	> File Name: my_test.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月22日 星期六 17时23分35秒
 ************************************************************************/

#include<stdio.h>
int main(int argc,char* argv[])
{
    for(int i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    return 0;
}
