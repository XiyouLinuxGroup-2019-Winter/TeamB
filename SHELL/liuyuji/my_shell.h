/*************************************************************************
	> File Name: my_shell.h
	> Author: 
	> Mail: 
	> Created Time: 2020年04月17日 星期五 20时10分25秒
 ************************************************************************/

#ifndef _MY_SHELL_H
#define _MY_SHELL_H

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>

#define normal 0
#define out_re 1
#define in_re 2
#define have_pipe 3

void print_shell();
void get_input(char *);
void explain_input(char *,int *,char arglist[100][256]);
void do_cmd(int,char arglist[100][256]);
int find_cmd(char *);

#endif
