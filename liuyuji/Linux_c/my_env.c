/*************************************************************************
	> File Name: my_env.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月28日 星期五 20时32分25秒
 ************************************************************************/

#include<stdio.h>
int main(int argc,char **argv,char **envp)
{
    for(int i=0;envp[i]!=NULL;i++){
        printf("%s\n",envp[i]);
    }
}
