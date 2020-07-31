/*************************************************************************
	> File Name: msgbox.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月30日 星期四 17时42分32秒
 ************************************************************************/

#include"client.h"
void *msgbox(void *arg)
{
    printf("msgbox is running\n");
    while(1){
        //接收数据类型
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
        char flag[2];
        switch(type){
            case ADDFRIEND:
            memset(flag,0,sizeof(flag));
            if(get_arg(recv_buf,flag,sizeof(flag))<0){
                my_err("read",__LINE__);
            }
            if(flag[0]=='0'){
                printf("\t\t\t\t\t好友不存在\n");
            }
            else if(flag[0]=='1'){
                char fid[10];
                memset(fid,0,sizeof(fid));
                if(get_arg(recv_buf,fid,sizeof(fid))<0){
                    my_err("read",__LINE__);
                }
                printf("\t\t\t\t\t%s申请添加您为好友\n",fid);
                printf("\t\t\t\t\t1.同意\n\t\t\t\t\t2.丑拒\n");
                int ch;
                scanf("%d",&ch);
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
                /*else(chose==2){
                    
            }*/
            }
            else if(flag[0]=='2'){
                char fid[10];
                memset(fid,0,sizeof(fid));
                if(get_arg(recv_buf,fid,sizeof(fid))<0){
                    my_err("read",__LINE__);
                }
                printf("\t\t\t\t\t%s已同意您的好友请求\n",fid);
            }
            break;
        }
    }
}
