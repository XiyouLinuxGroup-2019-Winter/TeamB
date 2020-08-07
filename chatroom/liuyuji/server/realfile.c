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
    //获取文件数据
    char buffer[1024];
    sprintf(buffer,"%s",(char *)arg+len+1);
    /*if((lenth=get_arg(arg,buffer,1024))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    buffer[lenth]=0;*/
    printf("filedata is %s\n",buffer);
    FILE *fp=fopen(filename,"a");
    if(fwrite(buffer,sizeof(char),strlen(buffer),fp) < strlen(buffer))
    {
        printf("File:\t%s Write Failed\n", filename);
    }
    fclose(fp);
    free(arg);
    printf("realfile over\n");
}
