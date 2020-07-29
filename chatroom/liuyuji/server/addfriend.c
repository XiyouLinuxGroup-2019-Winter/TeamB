/*************************************************************************
	> File Name: addfriend.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月29日 星期三 20时02分17秒
 ************************************************************************/

#include"chat.h"
#include"thread_pool.h"
void *addfriend(void *arg)
{
    int len=0;
    //获取用户id
    char uid[10];
    if((len=get_arg(arg,uid,10))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    fid[len]=0;
    printf("uid is %s\n",uid);//
    //获取好友id
    char fid[10];
    if((len=get_arg(arg,fid,10))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    fid[len]=0;
    printf("fid is %s\n",fid);//
    char fd[4];
    if((len=get_arg(arg,fd,4))<0){
        fprintf(log,"get_arg failed\n");
    }
    fd[len]=0;
    printf("fd is %s\n",fd);//
    
    //查询好友是否存在以及在线情况
    char cmd[1024];
    memset(cmd,0,sizeof(cmd));
    printf("sprinf cmd\n");//
    sprintf(cmd,"select state from user_data where id = '%s'",fid);
    printf("cmd is %s\n",cmd);//
    if(mysql_query(&mysql, cmd)<0){
        my_err("mysql_query",__LINE__);
    }
    MYSQL_RES *result=NULL;
	MYSQL_ROW row;
	//MYSQL_FIELD *field;
    //printf("result\n");//
    result=mysql_store_result(&mysql);
    
    //查询好友表中有几条好友关系
    memset(cmd,0,sizeof(cmd));
    printf("sprinf cmd\n");//
    sprintf(cmd,"select * from friend where (user='%s'&&friend='%s') || (user='%s'&&friend='%s')",uid,fid,fid,uid);
    printf("cmd is %s\n",cmd);//
    if(mysql_query(&mysql, cmd)<0){
        my_err("mysql_query",__LINE__);
    }
    MYSQL_RES *results=NULL;
	MYSQL_ROW rows;
    results=mysql_store_result(&mysql);
    int count=0;//好友关系数
    while(rows=mysql_fetch_row(result)){
        count++:
    }
    char msg[100];
    memset(msg,0,sizeof(msg));
    //判断好友是否存在
    row=mysql_fetch_row(result);
    if(row==NULL){
        sprintf(msg,"好友不存在\n");//好友不存在
        free(arg);
        if(send_pack(atoi(fd),ADDFRIEND,strlen(msg),msg)<0){
            my_err("write",__LINE__);
        }
        close(atoi(fd));
        return 0;
    }
    //好友存在
    memset(cmd,0,sizeof(cmd));
    //添加好友关系
    sprintf(cmd,"insert into friend(user,friend) values(%s,%s)",uid,fid);
    printf("cmd is %s\n",cmd);//
    if(mysql_query(&mysql, cmd)<0){
        my_err("mysql_query",__LINE__);
    }
    if(count==0){
        memset(cmd,0,sizeof(cmd));
        //添加好友申请消息
        sprintf(cmd,"insert into friend_request(send_id,recv_id) values(%s,%s)",uid,fid);
        if(mysql_query(&mysql, cmd)<0){
            my_err("mysql_query",__LINE__);
        }
    }
    if(row[0]!=NULL){
        if(strcmp("1",row[0])==0){
            //在线
            //0条好友关系
            if(count==0){
                //发送消息
                memset(cmd,0,sizeof(cmd));
                sprintf(cmd,"select socket from user_data where id = %s",fid);
                if(mysql_query(&mysql, cmd)<0){
                    my_err("mysql_query",__LINE__);
                }
                results=mysql_store_result(&mysql);
                rows=mysql_fetch_row(result);
                sprintf(msg,"%s\n%s\n",uid,fid);
                if(send_pack(atoi(rows[0]),ADDFRIEND,strlen(msg),msg)<0){
                    my_err("write",__LINE__);
                }
                memset(cmd,0,sizeof(cmd));
                sprintf(cmd,"update friend_request set state = 1 where user='%s' && friend='%s'",uid,fid);
                if(mysql_query(&mysql, cmd)<0){
                    my_err("mysql_query",__LINE__);
                }
            }
            else if(count==1){
                //将link改为1
                memset(cmd,0,sizeof(cmd));
                sprintf(cmd,"update friend set link = 1 where (user='%s' && friend='%s')||(user='%s' && friend='%s')",uid,fid,fid,uid);
                if(mysql_query(&mysql, cmd)<0){
                    my_err("mysql_query",__LINE__);
                }
                //查询好友fd
                memset(cmd,0,sizeof(cmd));
                sprintf(cmd,"select socket from user_data where id = %s",fid);
                if(mysql_query(&mysql, cmd)<0){
                    my_err("mysql_query",__LINE__);
                }
                results=mysql_store_result(&mysql);
                rows=mysql_fetch_row(result);
                //发送成功消息
                memset(msg,0,sizeof(msg));
                sprintf(msg,"%s已同意您的好友请求\n",uid);
                if(send_pack(atoi(rows[0]),ADDFRIEND,strlen(msg),msg)<0){
                    my_err("write",__LINE__);
                }
            }
            
        }
        else{
            //不在线
            if(count==1){
                //将link改为1
                memset(cmd,0,sizeof(cmd));
                sprintf(cmd,"update friend set link = 1 where (user='%s' && friend='%s')||(user='%s' && friend='%s')",uid,fid,fid,uid);
                if(mysql_query(&mysql, cmd)<0){
                    my_err("mysql_query",__LINE__);
                }
            }
        }
    }
    free(arg);
    close(atoi(fd));
    return 0;
}

