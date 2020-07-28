/*************************************************************************
	> File Name: unpack.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月28日 星期二 14时50分34秒
 ************************************************************************/

#include"chat.h"
#include"thread_pool.h"
int my_read(int conn_fd,void *buf,int len)
{
    int nleft=len;
    int nread=0;
    char *bufp=buf;
    //循环读数据
    while(nleft>0){
        if((nread=read(conn_fd,bufp,nleft))==-1){
            if(errno==EAGAIN){
                nread=0;
            }else{
                return -1;
            }
        }else if(nread==0){
            continue;
        }
        nleft-=nread;
        bufp+=nread;
    }

    return (len-nleft);
}
void *unpack(void *arg)
{
    int conn_fd=*(int *)arg;
    
    //接收数据类型
    char ty[2];
    if(my_read(conn_fd,&ty,2)<0){
        my_err("read",__LINE__);
    }
    fprintf(stderr,"数据type为%s\n",ty);
    
    //接收数据长度
    char len[2];
    if(my_read(conn_fd,&len,2)<0){
        my_err("read",__LINE__);
    }
    fprintf(stderr,"数据len为%s\n",len);
    
    //接收数据
    char recv_buf[1024];
    memset(recv_buf,0,sizeof(recv_buf));
    if(my_read(conn_fd,recv_buf,atoi(len))<0){
        my_err("read",__LINE__);
    }
    fprintf(stderr,"数据为%s\n",recv_buf);
    
    //准备参数
    char *argv=(char *)malloc(atoi(len)+2);
    sprintf(argv,"%s%d\n",recv_buf,conn_fd);
    argv[atoi(len)+1]=0;
    fprintf(stderr,"参数为%s",argv);

    //判断type，将对应处理函数放进线程池
    int type=atoi(ty);
    switch(type){
        /*case LOGIN:
        add_work(login,(void *)arg);
        break;*/
        case UREGISTER:
        add_work(uregister,(void *)argv);
        break;
        /*case FHCAT:
        add_work(fchat,(void *)arg);
        break;
        case ADDFRIEND:
        add_work(addfriend,(void *)arg);
        break;
        case DELFRIEND:
        add_work(delfriend,(void *)arg);
        break;
        case FINDFRIEN:
        add_work(findfriend,(void *)arg);
        break;
        case FRIENDLIST:
        add_work(friendlist,(void *)arg);
        break;
        case FCHATMSG:
        add_work(fchatmsg,(void *)arg);
        break;
        case BLOCKFRIEND:
        add_work(blockfriend,(void *)arg);
        break;
        case GCHAT:
        add_work(gchat,(void *)arg);
        break;
        case CREATEGROUP:
        add_work(creategroup,(void *)arg);
        break;
        case DELGROUP:
        add_work(delgroup,(void *)arg);
        break;
        case ADDGROUP:
        add_work(addgroup,(void *)arg);
        break;
        case EXITGROUP:
        add_work(exitgroup,(void *)arg);
        break;
        case GROUPMEMBER:
        add_work(groupmember,(void *)arg);
        break;
        case GCHATMSG:
        add_work(gchatmsg,(void *)arg);
        break;
        case SETSTATE:
        add_work(setstate,(void *)arg);
        break;
        case DELMEMBER:
        add_work(delmember,(void *)arg);
        break;*/
    }
}
