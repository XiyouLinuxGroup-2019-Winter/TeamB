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
    
    Menu();
    

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
    
    if(recv(sock_fd,&recv_registe,sizeof(PACK),MSG_WAITALL) < 0)
	{
        my_err("recv",__LINE__);
    }
    printf("接收成功\n");
    recv_registe_flag = recv_registe.data.mes[0] - '0';
    printf("%d\n",recv_registe_flag);
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
    int login_flag;
    int i = 0;

    printf("\t\t请输入账号名称：");
    scanf("%s",login_name);
    getchar();                          
    printf("\t\t请输入账号密码：");
    scanf("%s",login_passwd);
    system("clear");
    send_pack(flag, login_name, "server", login_passwd);
    if(recv(sock_fd, &recv_login, sizeof(recv_login),0) < 0)
        my_err("recv", __LINE__);
        
    login_flag = recv_login.data.mes[0] - '0';
    if(login_flag == 1)
    {
        printf("\t\t登陆成功!\n");
        return 1;
    }
    else 
    {
	    printf("\t\t登陆失败!\n");
    }
	return 0;
}

void Menu()
{
    int choice;
    int flag;
    do
    {
        printf("\n\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t\033[;34m\33[1m*\033[0m        1.好友管理           \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        2.群管理             \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        3.发送文件           \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        4.未读消息           \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        0.退出               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t请选择：");
        scanf("%d",&choice);
        
        switch(choice)
        {
        case 1:
            Menu_friends();
            break;
        
            
        default:
            break;
        }
    }while(choice != 0);
    flag = EXIT;
    send_pack(flag, user, "server", " ");
}

void Menu_friends()
{
    int choice;
    do
    {
        printf("\n\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t\033[;34m\33[1m*\033[0m        1.查看好友            \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        2.添加好友            \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        3.删除好友            \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        4.屏蔽好友            \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        5.解除屏蔽好友        \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        6.私聊                \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        7.聊天记录            \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        0.退出                \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t请选择：");
        scanf("%d",&choice);
        
        switch(choice)
        {
        	case 1:
            look_fri();
            break;

        case 2:
            add_fri();
            break;
           
        case 3:
            del_fri();
            break;

        case 4:
            shi_fri();
            break;
            
        case 5:
        	rel_fri();
        	break;

        case 6:
            chat_one();
            break; 
            
        case 7:
            check_mes_fri();
            break;

        default:
            break;
        }
    }while(choice != 0);
}

void look_fri()
{
    int flag = LOOK_FRI;
    char mes[MAX_CHAR];
    bzero(mes, MAX_CHAR);
    memset(&fri_info, 0, sizeof(fri_info));
    int i;

    pthread_mutex_lock(&mutex);
    send_pack(flag, user, "server", "1");
    pthread_cond_wait(&cond, &mutex);
    printf("%d\n",fri_info.friends_num);
    printf("\n\t\t\e[1;34m***********朋友列表***********\e[0m\n");
    if(fri_info.friends_num == 0)
        printf("\t\t暂无好友!\n");
    else
    {
        for(i = 0; i < fri_info.friends_num; i++)
        {
            if(fri_info.friends_status[i] == 1)
            {
                flag = GET_FRI_STA;
                send_pack(flag, fri_info.friends[i], "server", mes);
                pthread_cond_wait(&cond, &mutex);
            }
            else if(fri_info.friends_status[i] == 2)
                printf("\t\t\e[1;31m        ***%s***\e[0m\n",fri_info.friends[i]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void add_fri()
{
    int i;
    int flag = ADD_FRI;
    pthread_mutex_lock(&mutex);
    char friend[MAX_CHAR];
    printf("\t\t你想要添加的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, friend, "0");
    pthread_mutex_unlock(&mutex);
}

void del_fri()
{
    int flag = DEL_FRI;
    char friend[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要删除的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, "server", friend);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void shi_fri()
{
    int flag = SHI_FRI;
    char friend[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要屏蔽的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, "server", friend);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void rel_fri()
{
	int flag = REL_FRI;
    char friend[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要解除屏蔽的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, "server", friend);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void chat_one()
{
    int flag = CHAT_ONE;
    char chat_name[MAX_CHAR];
    char mes[MAX_CHAR];
    int i = 0;
    memset(mes, 0, sizeof(mes));
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].messages[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入聊天对象的名字 ");
    scanf("%s",chat_name);
    mes[0] = '1';
    send_pack(flag, user, chat_name, mes);
    
    pthread_cond_wait(&cond, &mutex);
    if(ffflag == 1)
    {
        ffflag = 0;
        pthread_mutex_unlock(&mutex);
        return;
    }
    printf("\n\t\t\e[1;34m***********消息***********\e[0m\n");
    if(rec_info[0].messages[0] == '0')
        printf("\t\t暂无未读消息\n");
    else
    {
        while(rec_info[i].messages[0] != '0')
        {
            printf("\t\t\e[1;35m%s-->%s: \e[0m%s\n",rec_info[i].send_user, rec_info[i].recv_user, rec_info[i].messages);
            i++;
        }
    }
    printf("\n\t\t\e[1;33m按q退出聊天\e[0m\n");
    getchar();
    do
    {
        memset(mes, 0, sizeof(mes));
        printf("\t\t\e[1;34m%s:\e[0m ", user);
        scanf("%s", mes);
        scanf("%[^\n]", mes);
        getchar();
        send_pack(flag, user, chat_name, mes);
    }while(strcmp(mes, "q") != 0);

    pthread_mutex_unlock(&mutex);
}

void check_mes_fri()
{
    int i = 0;
    int flag = CHECK_MES_FRI;
    char mes_fri[MAX_CHAR];
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].messages[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入要查看聊天记录的好友");
    scanf("%s",mes_fri);
    send_pack(flag, user, "server", mes_fri);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

