#ifndef _CLIENT_H
#define _CLIENT_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<termios.h>
#include<assert.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#define EXIT           -1
#define REGISTE         1
#define LOGIN           2
#define CHECK_FRI       3
#define GET_FRI_STA     4
#define ADD_FRI         5
#define DEL_FRI         6
#define SHI_FRI         7
#define REL_FRI         8 
#define CRE_GRP         9 
#define ADD_GRP         10 
#define OUT_GRP         11 
#define DEL_GRP         12 
#define SET_GRP_ADM     13 
#define KICK_GRP        14 
#define CHECK_GRP       15 
#define CHECK_MEM_GRP   16 
#define CHAT_ONE        17 
#define CHAT_MANY       18 
#define CHECK_MES_FRI   19 
#define CHECK_MES_GRP   20
#define SEND_FILE       21 
#define RECV_FILE       22 

#define BUFSIZE 1024
#define MAX_CHAR 100
#define FRI_MAX 100
#define MAX_FILE 10000

#define SERV_PORT 8848

#define PASSIVE 0
#define ACTIVE 1

typedef struct _user
{
    char name[MAX_CHAR];
    char passwd[MAX_CHAR];
    int statu_s;
    int fd;
    char chat[MAX_CHAR];
    struct _user *next;
}User;

typedef struct _relation
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    int statu_s;
    struct _relation *next;
}Relation;

typedef struct _recordinfo
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    char message[BUFSIZE];
    struct _recordinfo *next;
}Recordinfo;

typedef struct _friends
{
    char friends[FRI_MAX][MAX_CHAR];
    int friends_status[FRI_MAX];
    int friends_num;
}FRI_INFO;

typedef struct _group
{
    char groups[FRI_MAX][MAX_CHAR];
    int grp_num;
}GROUP_INFO;

typedef struct _record
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    char message[MAX_CHAR];
}RECORD_INFO;

typedef struct _data
{
    int send_fd;
    int recv_fd;
    char send_name[MAX_CHAR];
    char recv_name[MAX_CHAR];    
    char mes[MAX_CHAR * 3];
}DATA;

typedef struct file
{
    int size;
    char mes[MAX_FILE];
}FIle;

typedef struct _pack
{
    int type;
    DATA data;
    FIle file;
    FRI_INFO fri_info;
    GROUP_INFO grp_info;
    RECORD_INFO rec_info[55];
}PACK;

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

void *recv_back(void *arg);
int login_menu();       
int login();            
void registe();
void Menu();    
void Menu_friends();
void check_fri();
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
int get_choice(char *choice_t);
char *s_gets(char *s, int n);

int sock_fd;
char user[MAX_CHAR];
char grp_name[MAX_CHAR];
FRI_INFO fri_info;
GROUP_INFO grp_info;
RECORD_INFO rec_info[50];
char mes_file[MAX_CHAR * 3];
int ffflag;

char name[100][MAX_CHAR];    
char mes_box[100][MAX_CHAR];
int mes_box_inc[100];
int sign;
int sign_ive[100];

pthread_mutex_t mutex;
pthread_cond_t cond;

#endif
