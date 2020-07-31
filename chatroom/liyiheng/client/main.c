#include"client.h"

typedef struct msg_from{
    char password[30];//密码
    char password1[30];//确认密码
    char nikename[30];//昵称
    char nikename1[30];//发件人姓名
    char text[1024];//聊天内容
    char state[20];//判断是否在线
    char filedes;//文件描述符
    int num;
    int seg;
    int count;
}recv_package;


int main()
{
    printf("请输入主机名：");
    char name[50];
    scanf("%s",name);

    struct hostent *h = gethostbyname(name);

    if(h == NULL)
    {
        perror("gethostbyname error");
        exit(1);
    }


    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
        perror("socket");
        exit(2);
    }

    struct sockaddr_in  server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnum);
    server_addr.sin_addr = *((struct in_addr*)h -> h_addr);

    if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in)) == -1)
    {
        perror("connect")
        exit(3);
    }

    printf("请输入号码:\n");

    close(sockfd);
    
    return 0;

}
