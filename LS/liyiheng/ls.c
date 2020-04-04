#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include<pthread.h>


void read_dir(char *dir);
void file(char *name);

void read_dir(char * dir)
{
    char path[256];
    DIR *dp;
    struct dirent *sdp;
    dp = opendir(dir);
    if(dp == NULL)
    {
        perror("open file\n");
        exit(1);
    }

    while((sdp = readdir(dp)) != NULL)
    {
        if(strcmp(sdp -> d_name,".") == 0||strcmp(sdp ->d_name,"..") == 0)
        {
            continue;
        }
         sprintf(path,"%s/%s",dir,sdp -> d_name);
         file(path);
    }
    closedir(dp);
    return;
}


void file(char *name)
{    
     int ret = 0;
     struct stat buf;
     ret = stat(name,&buf);
     if(ret == -1)
    {
        perror("stat error\n");
    }
    if(S_ISDIR(buf.st_mode))
    {
      read_dir(name);
    }
    printf("%10s\t%ld\n",name,buf.st_size);

}
    

    




int main(int argc,char * argv[])
{  
    if(argc == 1)
    file(".");
    else
    file(argv[1]);
    return 0;
}
