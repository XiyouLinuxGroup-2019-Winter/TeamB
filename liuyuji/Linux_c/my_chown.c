/*************************************************************************
	> File Name: my_chown.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月22日 星期六 16时54分24秒
 ************************************************************************/

#include<stdio.h>
#include<sys/type.h>
#include<sys/stat.h>
#include<unistd.h>
int main()
{
    struct stat buf;
    stat(test,&buf);
    printf("mode:%d\nuid:%d\ngid:%d\nsize:%d\n",buf.st_mode,buf.st_uid,buf.st_gid,buf.st_size);
    printf("选择您要修改的内容\n1.mode\n2.uid\n3.gid\n4.size\n");
    int n;
    scanf("%d",&n);
    switch(n){
        case 1:
            printf("请输入修改之后的权限\n");
            mode_t m;
            scanf("%d",&m);
            chmod(test,m);
    }
}
