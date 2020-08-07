#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<signal.h>
#include<sys/epoll.h>
#include"chat.h"

#define SERV_PORT 8848  

#define PASSIVE 0
#define ACTIVE 1

void *get_back(void *arg);
int login_menu();       
int login();            
void registe();
void Menu();    
void Menu_friends();
void look_fri();
void add_fri();
void del_fri();
void shi_fri();
void rel_fri();
void chat_one();
void check_mes_fri();
void Menu_groups();
void check_grp_menu();
void check_grp();
void check_mem_grp();
void cre_grp();
void add_grp();
void out_grp();
void power_grp_menu(); 
void set_grp_adm();
void del_grp();
void kick_grp();
void chat_many();
void check_mes_grp();
void Menu_files();
void recv_file(PACK *recv_pack);
int get_file_size(char *send_file_name);
void send_file();
void Menu_mes_box();
void send_pack(int type, char *send_name, char *recv_name, char *mes);


int sock_fd;
pthread_mutex_t mutex;
pthread_cond_t cond;
char user[MAX_CHAR];
char grp_name[MAX_CHAR];
FRI_INFO fri_info;
GROUP_INFO grp_info;
RECORD_INFO rec_info[55];
char mes_file[MAX_CHAR * 3];
int ffflag;  //检测好友是否被屏蔽 

char name[100][MAX_CHAR];
char mes_box[100][MAX_CHAR];
int mes_box_inc[100];
int sign;
int sign_ive[100];


int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    pthread_t pid;

    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        my_err("socket",__LINE__);

    if(connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0)
        my_err("connect",__LINE__);
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    if(login_menu() == 0)
    {
        close(sock_fd);
        return 0;
    }

    pthread_create(&pid, NULL, get_back, NULL);
    

    close(sock_fd);

    return 0;
}

void *get_back(void *arg)
{
	pthread_mutex_t mutex_g;
    pthread_mutex_init(&mutex_g, NULL);
    while(1)
    {
    	int flag;
        PACK recv_pack;
        int i = 0;
        int fd;
        int ret = recv(sock_fd, &recv_pack, sizeof(PACK), MSG_WAITALL);
        if(ret < 0)
            my_err("recv", __LINE__);
                     
        switch(recv_pack.type)
        {
        	case LOOK_FRI:
                memcpy(&fri_info, &recv_pack.fri_info, sizeof(FRI_INFO));
                pthread_cond_signal(&cond);           
                break;

            case GET_FRI_STA:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\t\t        ***%s***\n",recv_pack.data.recv_user);
                else if(flag == 1)
                    printf("\t\t\e[1;32m        ***%s***\e[0m\n",recv_pack.data.recv_user);
            
                pthread_cond_signal(&cond);
                break;
  
		}
	}
}

void send_pack(int type, char *send_name, char *recv_name, char *mes)
{
    PACK pack_send;
    memset(&pack_send, 0, sizeof(PACK));
    pack_send.type = type;
    pack_send.data.recv_fd = sock_fd;
    strcpy(pack_send.data.send_user, send_name);
    strcpy(pack_send.data.recv_user, recv_name);
    strcpy(pack_send.data.mes, mes);
    if(send(sock_fd, &pack_send, sizeof(PACK), 0) < 0)
        my_err("send",__LINE__);
}

int login_menu()
{
    int choice;
    int flag;
    do
    {
        printf("\n\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t\033[;34m\33[1m*\033[0m        1.登陆               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        2.注册               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        0.退出               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\tchoice：");
        scanf("%d",&choice);
        switch(choice)
        {  
            case 1:
                if(login() == 1)
                    return 1;
                break;
            case 2:
                registe();
                break;
            default:
                return 0; 
        }
    }while(choice!=0);
    return 0;
} 

void registe()
{
    int flag = REGISTE;
    char name[MAX_CHAR];
    char passwd[MAX_CHAR];
    PACK recv_registe;
    int recv_registe_flag;
    int ret; 

    printf("\t\t输入想要注册账号的名称：");
    scanf("%s",name);
    printf("\t\t输入想要注册账号的密码：");
    scanf("%s",passwd);
    
    send_pack(flag, name, "server", passwd);
    printf("发送消息成功\n");
    ret=recv(sock_fd, &recv_registe, sizeof(recv_registe), MSG_DONTWAIT);
    printf("返回的字节数：%d\n",ret);
    while(ret < 0)
        my_err("recv", __LINE__);
    printf("接收成功\n");
    recv_registe_flag = recv_registe.data.mes[0] - '0';
    printf("你收到的信息：%s\n",recv_registe.data.mes[0]);
    if(recv_registe_flag == 1)
        printf("\t\t注册成功!\n");
    else
    {
        printf("\t\t注册失败\n");
    } 
}

int login()
{
    int flag = LOGIN;
    char login_name[MAX_CHAR];
    char login_passwd[MAX_CHAR];
    PACK recv_login;
    int recv_login_flag;
    int i = 0;

    printf("\t\t请输入账号名称：");
    scanf("%s",login_name);
    getchar();                          
    printf("\t\t请输入账号密码：");
    scanf("%s",login_passwd);
    system("clear");
    send_pack(flag, login_name, "server", login_passwd);
    printf("\t\t发送成功：\n");
    if(recv(sock_fd, &recv_login, sizeof(recv_login), MSG_WAITALL) < 0)
        my_err("recv", __LINE__);
        
    printf("\t\t接收成功：\n");
    printf("你收到的的信息：%s\n",recv_login.data.mes);
    recv_login_flag = recv_login.data.mes[0] - '0';
    printf("%d\n",recv_login_flag);
    if(recv_login_flag == 1)
    {
        printf("\t\t登陆成功!\n");
        strncpy(user, login_name, strlen(login_name));
        return 1;
    }
    else 
    {
	    printf("\t\t登陆失败!\n");
    } 
	return 0;
}
