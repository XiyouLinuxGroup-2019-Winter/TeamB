/*************************************************************************
	> File Name: my_ls.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月24日 星期一 16时26分10秒
 ************************************************************************/

#include<stdio.h>//未完成！！！
#include"my_ls.h"//这是一个已经放弃的代码
int main(int argc,char *argv[])
{
    if(argc==1){
        char *name;
        if(name=getcwd(name,0)==NULL){
            my_err();
        }
        print_fname(name);
        free(name);
    }
    if(argc==2){
        if(strcmp(argv[1],"-a")==0){

        }
        if(strcmp(argv[1],"-l")==0){
            char *name;
            if(name=getcwd(name,0)==NULL){
                my_err();
            }
            print_finfo(name);
            free(name);
        }
    } 
    if(argc>2){

    }
}
void print_finfo(char *name)
{
    DIR *dir;
    if(dir=opendir(name)==NULL){
        my_err();
    }
    struct dirent *fstr;
    while(1){
        if(fstr=readdir(dir)!=NULL){
            struct stat buf;
            if(stat(fstr->d_name,&buf)<0){
                my_err();
            }
            if(S_ISLNK(buf.st_mode)){
                printf("l");
            }else if(S_ISREG(buf.st_mode)){
               printf("-");
            }else if(S_ISDIR(buf.st_mode)){
                printf("d");
            }else if(S_ISCHR(buf.st_mode)){
                printf("c");
            }else if(S_ISBLK(buf.st_mode)){
                printf("b");
            }else if(S_ISFIFO(buf.st_mode)){
                printf("f");
            }else if(S_ISSOCK(buf.st_mode)){
                printf("s")
            }
            if(buf.st_mode&S_IRUSR){
                printf("r");
            }else{
                printf("-");
            }
            if(buf.st_mode&S_IWUSR){
                printf("w");
            }else{
                printf("-");
            }
            if(buf.st_mode&S_IXUSR){
                printf("x");
            }else{
                printf("-");
            }
            if(buf.st_mode&S_IRGRP){
                printf("r");
            }else{
                printf("-");
            }
            if(buf.st_mode&S_IWGRP){
                printf("w");
            }else{
                printf("-");
            }
            if(buf.st_mode&S_IXGRP){
                printf("x");
            }else{
                printf("-");
            }
                if(buf.st_mode&S_IROTH){
                printf("r");
            }else{
                printf("-");
            }
            if(buf.st_mode&S_IWOTH){
                printf("w");
            }else{
                printf("-");
            }
            if(buf.st_mode&S_IXOTH){
                printf("x");
            }else{
                printf("-");
            }    
            printf("   ");
            struct passwd *psd;
            struct group *grp;
            psd=getpwuid(buf.st_uid);
            grp=getgrgid(buf.st_gid);
            printf("%4d ",buf.st_nlink);
            printf("%-8s",psd->pw_name);
            printf("%-8s",grp->gr_name);
            printf("%6d",buf.st_size);
            char buf_time[32];
            strcpy(buf_time,ctime(&buf.st_mtime));
            buf_time[strlen(buf_time)-1]='\0';
            printf("   %s",buf_time);
            printf("%s\n",fstr->d_name);
        }
        else{
            break;
        }
    }
    closedir(dir);
}
void print_fname(char *name)
{
    DIR *dir;
    struct dirent *fstr;
    if(dir=opendir(name)==NULL){
        my_err();
    }
    while(1){
        if(fstr=readdir(dir)!=NULL){
            printf("%s\t",fstr->d_name);
        }
        else{
            break;
        }
    }
    closedir(dir);
}
void my_err()
{
    printf("error");
    exit(0);
}
