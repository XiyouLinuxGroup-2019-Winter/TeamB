/*************************************************************************
	> File Name: 6.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月01日 星期六 15时01分09秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]) {
FILE *fp = fopen("Linux.txt", "wb");
    long long a = 0x78756e694c;
 fwrite(&a, sizeof(a), 1, fp);
 fclose(fp);
 return 0;
}
