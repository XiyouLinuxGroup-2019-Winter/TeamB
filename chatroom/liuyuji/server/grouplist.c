/*************************************************************************
	> File Name: grouplist.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月03日 星期一 22时29分45秒
 ************************************************************************/

#include"chat.h"
void *grouplist(void *arg)
{
    printf("grouplist start\n");//
    int len=0;
    //获取用户id
    char id[10];
    if((len=get_arg(arg,id,10))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    id[len]=0;
    printf("id is %s\n",id);//
    //获取connfd
    char fd[4];
    if((len=get_arg(arg,fd,4))<0){
        fprintf(log,"get_arg failed\n");
    }
    fd[len]=0;
    printf("fd is %s\n",fd);
    char cmd[1024];
    memset(cmd,0,sizeof(cmd));
    //查询并储存所有群信息
    sprintf(cmd,"select group_id,group_name from group_member where member_id = '%s' && link = 1",id);
    printf("cmd is %s\n",cmd);//
    if(mysql_query(&mysql, cmd)<0){
        my_err("mysql_query",__LINE__);
    }
    MYSQL_RES *result=NULL;
	MYSQL_ROW row;
    char friend[100][10];
    memset(friend,0,sizeof(friend));
    result=mysql_store_result(&mysql);
}
