#include"client.h"

void login(int sockfd)  
{
    recv_package send;
    printf("请输入昵称\n");
    scanf("%s",send.nikename);
    printf("请输入密码\n");
    scanf("%s",send.password);

    if(write(sockfd,&send,sizeof(send)) == -1)
    {
        perror("write1");
        exit(1);
    }

    if(read(sockfd,&send,sizeof(send)) == -1)
    {
        perror("read2");
        exit(5);   
    }

    if(send.num == 1)
    {
        printf("登录成功\n");
        printf("欢迎%s进入聊天室\n",send.nikename);
    


        int pthread_id;

        if(pthread_create((pthread_t *)&pthread_id,NULL,net_thread_1,(void *)&sockfd) == -1)
        {
            perror("pthread_create");
            close(sockfd);
            exit(6);
        }
  
        memu_1(sockfd);
    }



    if(send.num == 2)
    {
        printf("密码不正确，请重新输入\n"); 
    }

    if(send.num == 3)
    {
        printf("result 输出错误\n");  
    }

    if(send.num == 4)
    {
        printf("账号为空，请检查输入\n"); 
    }


}




    
    
