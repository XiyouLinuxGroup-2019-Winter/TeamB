/*************************************************************************
	> File Name: msgbox.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月30日 星期四 17时42分32秒
 ************************************************************************/

#include"client.h"
void *msgbox(void *arg)
{
    //printf("msgbox is running\n");
    while(exit_flag!=1){
        //接收数据类型
        //printf("msgbox is while\n");
        read_len=0;
        char ty[3];
        memset(ty,0,sizeof(3));
        if(my_read(connfd,ty,2)<0){
            my_err("read",__LINE__);
        }
        fprintf(stderr,"数据type为%s\n",ty);
    
        //接收数据长度
        char len[3];
        memset(len,0,sizeof(len));
        if(my_read(connfd,len,2)<0){
            my_err("read",__LINE__);
        }
        fprintf(stderr,"数据len为%s\n",len);
        
        //接收数据
        char recv_buf[1024];
        memset(recv_buf,0,sizeof(recv_buf));
        if(my_read(connfd,recv_buf,atoi(len))<0){
            my_err("read",__LINE__);
        }
        fprintf(stderr,"数据为%s\n",recv_buf);
        
        //判断type，分别处理
        int type=atoi(ty);
        printf("msgbox type is %d\n",type);
        switch(type){
        case ADDFRIEND:{
            char flag[2];
            memset(flag,0,sizeof(flag));
            if(get_arg(recv_buf,flag,sizeof(flag))<0){
                my_err("read",__LINE__);
            }
            if(flag[0]=='0'){
                P_LOCK;
                printf("\t\t\t\t\t好友不存在\n");
                P_UNLOCK;
            }
            else if(flag[0]=='1'){
                char fid[10];
                memset(fid,0,sizeof(fid));
                if(get_arg(recv_buf,fid,sizeof(fid))<0){
                    my_err("read",__LINE__);
                }
                P_LOCK;
                printf("\t\t\t\t\t%s申请添加您为好友\n",fid);
                printf("\t\t\t\t\t同意请向%s发送好友申请\n\t\t\t\t\t拒绝则忽略\n",fid);
                P_UNLOCK;
                /*
                int ch;
                S_LOCK;
                scanf("%d",&ch);
                S_UNLOCK;
                printf("ch is %d\n",ch);
                if(ch==1){
                    char send_buf[1024];
                    memset(send_buf,0,sizeof(send_buf));
                    sprintf(send_buf,"%s\n%s\n",user_id,fid);
                    printf("addfriend send_buf is %s",send_buf);//
                    if(send_pack(connfd,ADDFRIEND,strlen(send_buf),send_buf)<0){
                        my_err("write",__LINE__);
                    }
                }
                else(chose==2){
                    
            }*/
            }
            else if(flag[0]=='2'){
                char fid[10];
                memset(fid,0,sizeof(fid));
                if(get_arg(recv_buf,fid,sizeof(fid))<0){
                    my_err("read",__LINE__);
                }
                P_LOCK;
                printf("\t\t\t\t\t%s已同意您的好友请求\n",fid);
                P_UNLOCK;
            }
            else if(flag[0]=='3'){
                P_LOCK;
                printf("\t\t\t\t\t请勿重复添加好友\n");
                P_UNLOCK;
            }
            break;
        }
        case FRIENDLIST:{
            char fid[10];
            memset(fid,0,sizeof(fid));
            if(get_arg(recv_buf,fid,sizeof(fid))<0){
                my_err("read",__LINE__);
            }
            if(fid[0]=='0'){
                P_LOCK;
                printf("\t\t\t\t\t您没有好友\n");
                P_UNLOCK;
                break;
            }
            char name[32];
            memset(name,0,sizeof(name));
            if(get_arg(recv_buf,name,sizeof(name))<0){
                my_err("read",__LINE__);
            }
            char state[2];
            memset(state,0,sizeof(state));
            if(get_arg(recv_buf,state,sizeof(state))<0){
                my_err("read",__LINE__);
            }
            P_LOCK;
            printf("\t\t\t\t\tid:%s  name:%s  state:%s\n",fid,name,state);
            P_UNLOCK;
            break;
        }
        case FINDFRIEND:{
            char fid[10];
            memset(fid,0,sizeof(fid));
            if(get_arg(recv_buf,fid,sizeof(fid))<0){
                my_err("read",__LINE__);
            }
            char name[32];
            memset(name,0,sizeof(name));
            if(get_arg(recv_buf,name,sizeof(name))<0){
                my_err("read",__LINE__);
            }
            char state[2];
            memset(state,0,sizeof(state));
            if(get_arg(recv_buf,state,sizeof(state))<0){
                my_err("read",__LINE__);
            }
            P_LOCK;
            printf("\t\t\t\t\tid:%s  name:%s  state:%s\n",fid,name,state);
            P_UNLOCK;
            break;
        }
        case DELFRIEND:{
            char flag[2];
            memset(flag,0,sizeof(flag));
            if(get_arg(recv_buf,flag,sizeof(flag))<0){
                my_err("read",__LINE__);
            }
            printf("flag is %c\n",flag[0]);//
            if(flag[0]=='0'){
                P_LOCK;
                printf("\t\t\t\t\t好友不存在\n");
                P_UNLOCK;
            }
            else if(flag[0]=='1'){
                P_LOCK;
                printf("\t\t\t\t\t删除成功\n");
                P_UNLOCK;
            }
            break;
        }
        case BLOCKFRIEND:{
            char flag[2];
            memset(flag,0,sizeof(flag));
            if(get_arg(recv_buf,flag,sizeof(flag))<0){
                my_err("read",__LINE__);
            }
            printf("flag is %c\n",flag[0]);//
            if(flag[0]=='0'){
                P_LOCK;
                printf("\t\t\t\t\t好友不存在\n");
                P_UNLOCK;
            }
            else if(flag[0]=='1'){
                P_LOCK;
                printf("\t\t\t\t\t拉黑成功\n");
            }
            break;
        }
        case FRIEND:{
            char flag[2];
            memset(flag,0,sizeof(flag));
            if(get_arg(recv_buf,flag,sizeof(flag))<0){
                my_err("read",__LINE__);
            }
            printf("flag is %c\n",flag[0]);//
            if(flag[0]=='0'){
                P_LOCK;
                printf("\t\t\t\t\t好友不存在\n");
                P_UNLOCK;
                C_SIGNAL;
                break;
            }
            else if(flag[0]=='1'){
                chat_flag=1;
                C_SIGNAL;
                break;
            }
        }
        case FCHAT:{
            char send_id[10];
            memset(send_id,0,sizeof(send_id));
            if(get_arg(recv_buf,send_id,sizeof(send_id))<0){
                my_err("read",__LINE__);
            }
            char recv_id[10];
            memset(recv_id,0,sizeof(recv_id));
            if(get_arg(recv_buf,recv_id,sizeof(recv_id))<0){
                my_err("read",__LINE__);
            }
            char msg[500];
            memset(msg,0,sizeof(msg));
            if(get_arg(recv_buf,msg,sizeof(msg))<0){
                my_err("read",__LINE__);
            }
            if(chat_flag==1 && strcmp(send_id,chat_id)==0){
                P_LOCK;
                printf("\t\t\t%s--->%s:%s\n",send_id,recv_id,msg);
                P_UNLOCK;
            }
            else{
                P_LOCK;
                printf("\t\t\t\t\t您有一条新消息!!!\n");
                //printf("\t\t\t%s--->%s:%s\n",send_id,recv_id,msg);
                P_UNLOCK;
                addnode(send_id,recv_id,msg);
            }
            break;
        }
        case CREATEGROUP:{
            char gid[10];
            memset(gid,0,sizeof(gid));
            if(get_arg(recv_buf,gid,sizeof(gid))<0){
                my_err("read",__LINE__);
            }
            if(gid[0]=='0'){
                P_LOCK;
                printf("群名重复，请重新创建群\n");
                P_UNLOCK;
                break;
            }
            P_LOCK;
            printf("您所创建的群ID为%s\n",gid);
            P_UNLOCK;
            break;
        }
        }
    }
}
