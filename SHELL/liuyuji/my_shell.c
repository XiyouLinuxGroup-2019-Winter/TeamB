/*************************************************************************
	> File Name: my_shell.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月09日 星期四 21时33分47秒
 ************************************************************************/

#include<stdio.h>
#include"my_shell.h"
int main(char argc,char **argv)
{
    char *buf=NULL;
    buf=(char *)malloc(256);
    if(buf==NULL){
        printf("malloc failed");
        exit(-1);
    }
    int argcount=0;
    char arglist[100][256];
    while(1){
        print_shell();
        memset(buf,0,256);
        get_input(&buf);
        if(strcmp(buf,"exit\n")==0 || strcmp(buf,"logout\n")){
            break;
        }
        argcount=0;
        for(int i=0;i<100;i++){
            arglist[i][0]=0;
        }
        explain_input(buf,&argcount,arglist);
        do_cmd(argcount,arglist);
    }
}
void print_shell()
{
    printf("my_shell $$: ");
}
void get_input(char *buf)
{
    int ch=getchar();
    int len=0;
    while(len<256 && ch!="\n"){
        buf[len++]=ch;
        ch=getchar();
    }
    if(len==256){
        printf("cmd too long\n");
        exit(-1);
    }
    buf[len++]="\n";
    buf[len]=0;
}
void explain_input(char *buf,int *argcount,char arglist[100][256])
{
    
}
