/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月27日 星期一 19时34分13秒
 ************************************************************************/

#include"client.h"
void my_err(const char *str,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(str);
    exit(1);
}
int main(int argc,char **argv)
{
    struct sockaddr_in serv_addr;
    int conn_fd,ret;
    int serv_port;
    char recv_buf[1024];
    memset(recv_buf,0,sizeof(recv_buf));
    //检查参数个数
    if(argc!=5){
        printf("Usage: [-p] [serv_port] [-a] [serv_addr]\n");
        exit(1);
    }
    //初始化服务器地址
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family=AF_INET;
    //解析参数，获取服务器地址以及端口号
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-p")==0){
            serv_port=atoi(argv[i+1]);
            //检查参数合法性并记录
            if(serv_port<0 || serv_port>65535){
                printf("invalid serv_port\n");
                exit(1);
            }
            else{
                serv_addr.sin_port=htons(serv_port);
            }
            continue;
        }
        if(strcmp(argv[i],"-a")==0){
            if(inet_aton(argv[++i],&serv_addr.sin_addr)==0){
                printf("invaild serv_addr\n");
                exit(1);
            }
            continue;
        }
    }
    //再次检查参数是否正确
    if(serv_addr.sin_port==0 || serv_addr.sin_addr.s_addr==0){
        printf("Usage: [-p] [serv_port] [-a] [serv_addr]\n");
        exit(1);
    }
    int chose=print_main();
    switch(chose){
        case 1:
        //创建TCP套接字
        conn_fd=socket(AF_INET,SOCK_STREAM,0);
        if(conn_fd<0){
            my_err("socket",__LINE__);
        }
        //链接服务器
        if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in))<0){
            my_err("connect",__LINE__);
        }

        break;
        case 2:
        //创建TCP套接字
        conn_fd=socket(AF_INET,SOCK_STREAM,0);
        if(conn_fd<0){
            my_err("socket",__LINE__);
        }
        //链接服务器
        if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in))<0){
            my_err("connect",__LINE__);
        }
        uregister(conn_fd);
        break;
        case 3:
        break;
    }
    //创建TCP套接字
    conn_fd=socket(AF_INET,SOCK_STREAM,0);
    if(conn_fd<0){
        my_err("socket",__LINE__);
    }
    //链接服务器
    if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in))<0){
        my_err("connect",__LINE__);
    }

}
