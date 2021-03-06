/*************************************************************************
	> File Name: friends.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月03日 星期一 15时10分10秒
 ************************************************************************/

#include"chat.h"
void *friends(void *arg)
{
    printf("friend start\n");
    int len=0;
    //获取用户id
    char uid[10];
    if((len=get_arg(arg,uid,10))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    uid[len]=0;
    printf("uid is %s\n",uid);//
    //获取好友id
    char fid[10];
    if((len=get_arg(arg,fid,10))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    fid[len]=0;
    printf("fid is %s\n",fid);//
    //获取用户socket
    char fd[4];
    if((len=get_arg(arg,fd,4))<0){
        fprintf(log,"get_arg failed\n");
    }
    fd[len]=0;
    printf("fd is %s\n",fd);    
    char cmd[1024];
    memset(cmd,0,sizeof(cmd));
    //查询好友是否存在
    sprintf(cmd,"select state,link from friend where (user = %s && friend = %s) || (user = %s && friend = %s)",uid,fid,fid,uid);
    printf("cmd is %s\n",cmd);//
    if(mysql_query(&mysql, cmd)<0){
        my_err("mysql_query",__LINE__);
    }
    MYSQL_RES *result=NULL;
	MYSQL_ROW row;
    char data[3];

    result=mysql_store_result(&mysql);
    row=mysql_fetch_row(result);
    if(row==NULL){
        memset(data,0,sizeof(data));
        sprintf(data,"0\n");
        if(send_pack(atoi(fd),FRIEND,strlen(data),data)<0){
            my_err("write",__LINE__);
        }
        free(arg);
        printf("friend over\n");
        return NULL;
    }
    //判断好友关系是否正常
    if(strcmp(row[0],"0")==0 || strcmp(row[1],"0")==0){
        memset(data,0,sizeof(data));
        sprintf(data,"0\n");
        if(send_pack(atoi(fd),FRIEND,strlen(data),data)<0){
            my_err("write",__LINE__);
        }
        free(arg);
        printf("friend over\n");
        return NULL;
    }
    else{
        memset(data,0,sizeof(data));
        sprintf(data,"1\n");
        if(send_pack(atoi(fd),FRIEND,strlen(data),data)<0){
            my_err("write",__LINE__);
        }
        free(arg);
        printf("friend over\n");
        return NULL;
    }
}
