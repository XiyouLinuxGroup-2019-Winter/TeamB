#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>

#define  normal        0
#define  out_redirect  1
#define  in_redirect   2
#define  have_pipe     3

void print_prompt();
void get_input(char *)
void explain_input(char *,int *,char a[][]);
int  find_command(char *)

int main(int argc,char **argv)
{
    int i;
    int argcount = 0;
    char arglist[100][256];
    char **arg = NULL;
    char *buf = NULL;

    buf = (char*)malloc(256);
    if(buf == NULL)
    {
        per("malloc failed");
        exit(-1);
    }
    
    while(1)
    {
        memset(buf,0,256);
        print_prompt();
        get_input(buf);

        if(strcmp(buf,"exit\n")==0||strcmp(buf,"logout\n")==0)
        break;
        for(i = 0;i < 100;i++)
        {
            arglist[i][0]='\0';
        }
        argcount = 0;
        explain_input(buf,&argcount,arglist);
        do_cmd(argcount,arglist);
    }

    if(buf != NULL)
    {
        free(buf);
        buf = NULL;
    }
    exit(0);
}
