/*************************************************************************
	> File Name: realfile.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月06日 星期四 23时32分39秒
 ************************************************************************/

#include"chat.h"
void *realfile(void *arg)
{
    printf("realfile start\n");
    int len=0;
    int lenth=0;
    //获取文件名
    char filename[256];
    if((len=get_arg(arg,filename,256))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    filename[len]=0;
    printf("filename is %s\n",filename);//
    //获取用户socket
    char fd[4];
    if((len=get_arg(arg,fd,4))<0){
        fprintf(log,"get_arg failed\n");
    }
    fd[len]=0;
    printf("fd is %s\n",fd);
    epoll_ctl(epfd,EPOLL_CTL_DEL,atoi(fd),NULL);
    /*//获取文件数据
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"%s",(char *)arg+len+1);
    if((lenth=get_arg(arg,buffer,1024))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    buffer[lenth]=0;*/
    //printf("filedata is %s\n",buffer);
    FILE *fp=fopen(filename,"w");
    int length = 0;
    setblock(atoi(fd));
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    while((length=recv(atoi(fd),buffer,sizeof(buffer),0))>0)
    {
        if(fwrite(buffer,sizeof(char),length,fp)<length)
        {
            printf("File:\t%s Write Failed\n", filename);
            break;
        }
        memset(buffer,0,sizeof(buffer));
    }
    struct epoll_event ev;
    ev.events=EPOLLIN | EPOLLRDHUP | EPOLLET;
    ev.data.fd=atoi(fd);
    epoll_ctl(epfd,EPOLL_CTL_ADD,atoi(fd),&ev);
    fclose(fp);
    free(arg);
    printf("realfile over\n");
}
