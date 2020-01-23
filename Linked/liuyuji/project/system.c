/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 19时42分37秒
 ************************************************************************/
 #include<stdio.h>
 #include"list.h"
 int main()
{
	FILE* creat=fopen("2.0","a");//第一次打开程序创建文件保存信息
	fclose(creat);
	FILE* fp=fopen("2.0","r");//打开文件加载文件内容用链表储存
	int try;
	if((try = getc(fp)) != EOF){
        while(1){
	operate=(stu*)malloc(sizeof(stu));
        if(head==NULL){
                head = operate;
		record = operate;
        }
        else{
                record->next=operate;
        }
        int k=fscanf(fp,"%s",operate->num);
	if(k==EOF){
		record->next=NULL;
		free(operate);
		break;
	}
        fscanf(fp,"%s",operate->name);
        fscanf(fp,"%s",operate->age);
        fscanf(fp,"%s",operate->sex);
        fscanf(fp,"%s",operate->bir);
        fscanf(fp,"%s",operate->place);
        fscanf(fp,"%s",operate->pn);
        operate->next=NULL;
        record=operate;}}
	fclose(fp);
	while(1){
	int a;
	printf("----------学生信息管理系统 1.0----------\n");//程序开始
	printf("1.录入学生信息\n");
	printf("2.浏览学生信息\n");
	printf("3.查询学生信息\n");
	printf("4.修改学生信息\n");
	printf("5.删除学生信息\n");
	printf("6.退出        \n");
	printf("请选择您要进行的操作：\n");
	scanf("%d",&a);
	switch(a){
		case 1:input();break;
		case 2:look();break;
		case 3:seek();break;
		case 4:modify();break;
		case 5:del();break;
		case 6:fr();exit(0);break;
		}
	}
    return 0;
}
void input()
{
	//确保指针所指节点为最后一项内容
    if(record != NULL){
	if(record->next != NULL){
		while(record->next != NULL){
		record=record->next;
		}
	}
	}
	//录入信息
    do{
	operate=(stu*)malloc(sizeof(stu));
	if(head==NULL){
		head = operate;
	}
	else{
		record->next=operate;
	}
	printf("请输入学生学号");
	scanf("%s",operate->num);
	printf("请输入学生姓名");
	scanf("%s",operate->name);
	printf("请输入学生年龄");
	scanf("%s",operate->age);
	printf("请输入学生性别");
	scanf("%s",operate->sex);
	printf("请输入学生出生年月");
	scanf("%s",operate->bir);
	printf("请输入学生生源地");
	scanf("%s",operate->place);
	printf("请输入学生联系电话");
	scanf("%s",operate->pn);
	operate->next=NULL;
	record=operate;
	printf("是否继续输入？\n1.继续2.放弃\n");
	scanf("%d",&n);
		FILE* fp1=fopen("2.0","a");
fprintf(fp1,"%-12s  %-12s  %-12s  %-12s  %-12s  %-12s  %-12s\n",operate->num,operate->name,operate->age,operate->sex,operate->bir,operate->place,operate->pn);
		fclose(fp1);
	}while(n==1);
}
void look()
{
	//遍历打印所有学生信息
    FILE* fp1=fopen("2.0","r");
	char ch;
	while((ch = getc(fp1)) != EOF){
		putchar(ch);
	}
	fclose(fp1);
}
void seek()
{
	//遍历查找
    operate=head;
	char number[10];
	char name1[10];
	printf("请选择您的查询方式\n");
	int n;
	printf("1.按学号查询\n2.按姓名查询\n");
	scanf("%d",&n);
	switch(n){
		case 1: scanf("%s",number);
			while(operate != NULL){
				if(strcmp(operate->num,number)==0){
printf("%-12s  %-12s  %-12s  %-12s  %-12s  %-12s  %-12s\n",operate->num,operate->name,operate->age,operate->sex,operate->bir,operate->place,operate->pn);break;}
                		record=operate;
                		operate=operate->next;
        		}break;
		case 2: scanf("%s",name1);
			while(operate != NULL){
                                if(strcmp(operate->name,name1)==0){
printf("%-12s  %-12s  %-12s  %-12s  %-12s  %-12s  %-12s\n",operate->num,operate->name,operate->age,operate->sex,operate->bir,operate->place,operate->pn);break;}
                                record=operate;
                                operate=operate->next;
			}break;
	}
}
void modify()
{
	//找到所要修改内容进行修改
    do{seek();
	int mi;
	printf("请输入您要修改的内容\n");
	printf("1.修改学号\n");
	printf("2.修改姓名\n");
	printf("3.修改年龄\n");
	printf("4.修改性别\n");
	printf("5.修改出生年月\n");
	printf("6.修改生源地\n");
	printf("7.修改电话\n");
	scanf("%d",&mi);
	switch(mi){
		case 1: printf("请输入您更改的新内容\n");
			char m1[10];
			scanf("%s",m1);
			strcpy(operate->num,m1);break;
		case 2: printf("请输入您更改的新内容\n");
                        char m2[10];
                        scanf("%s",m2);
                        strcpy(operate->name,m2);break;
		case 3: printf("请输入您更改的新内容\n");
                        char m3[10];
                        scanf("%s",m3);
                        strcpy(operate->age,m3);break;
		case 4: printf("请输入您更改的新内容\n");
                        char m4[5];
                        scanf("%s",m4);
                        strcpy(operate->sex,m4);break;
		case 5: printf("请输入您更改的新内容\n");
                        char m5[7];
                        scanf("%s",m5);
			strcpy(operate->bir,m5);break;
		case 6: printf("请输入您更改的新内容\n");
                        char m6[10];
                        scanf("%s",m6);
			strcpy(operate->place,m6);break;
		case 7: printf("请输入您更改的新内容\n");
                        char m7[12];
                        scanf("%s",m7);
			strcpy(operate->pn,m7);break;
		  }
	printf("您是否需要继续修改？\n");
	printf("1.继续  2.放弃\n");
	scanf("%d",&n);
	}while(n==1);
	FILE* fp1=fopen("2.0","w");
	operate=head;
	while(operate != NULL){
	fprintf(fp1,"%-12s  %-12s  %-12s  %-12s  %-12s  %-12s  %-12s\n",operate->num,operate->name,operate->age,operate->sex,operate->bir,operate->place,operate->pn);
	operate=operate->next;}
	fclose(fp1);
}
void del()
{
	//查找所要删除节点，并删除
    seek();
	printf("您是否要删除此列内容？\n1.确定  2.取消\n");
	scanf("%d",&n);
	if(n==1){
		if(operate==head){
			head=operate->next;
			free(operate);
		}
		else{
			record->next=operate->next;
			free(operate);
		}
	}
	FILE* fp1=fopen("2.0","w");
        operate=head;
	while(operate != NULL){
        fprintf(fp1,"%-12s  %-12s  %-12s  %-12s  %-12s  %-12s  %-12s\n",operate->num,operate->name,operate->age,operate->sex,operate->bir,operate->place,operate->pn);
        operate=operate->next;}
        fclose(fp1);
}
void fr()
{
	//退出时同时清空链表，归还内存
    operate=head;
	while(operate != NULL){
		record=operate;
		free(operate);
		operate=record->next;
	}
}
