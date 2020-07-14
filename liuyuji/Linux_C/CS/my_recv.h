/*************************************************************************
	> File Name: my_recv.h
	> Author: 
	> Mail: 
	> Created Time: 2020年07月14日 星期二 14时34分02秒
 ************************************************************************/

#ifndef _MY_RECV_H
#define _MY_RECV_H

void my_err(const char *str,int line);
int my_recv(int conn_fd,char *date_buf,int len);

#endif
