#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct course_information
{
    char name[20];
    int number;
    char teacher[20];
    int time;
    int classroom;
    struct course_information *next;
}course_information,*course;



typedef struct student_information
{
    int number;
    char name[20];
    char sex[20];
    struct course_information *choices;
    struct student_information *next;
}student_information,*student;




student creat_stu(student stu_head);
student find_stu(student stu_head,int number);
course  creat_cou (course  cou_head); 
void  out_cou(course cou_head);
course find_cou(course cou_head,int number);
course delete_cou(course cou_head,course del_point);
course add_cou(course cou_head,course new_cou);
student add_stu(student stu_head,student new_stu);
void  out_stu(student stu_head);
student delete_stu(student stu_head,student del_point);
student choice_cou(student stu_head,int number1,course cou_head);
void out_choice(student stu_head);

void  Interface()
{
    printf("\t---------欢迎使用学生选课系统----------\n");
    printf("                                         \n"); 
    printf("\t---------   1.输入课程信息  -----------\n");
    printf("\t---------   2.浏览课程信息  -----------\n");
    printf("\t---------   3.删除课程信息  -----------\n");
    printf("\t---------   4.输入学生信息  -----------\n");
    printf("\t---------   5.浏览学生信息  -----------\n");
    printf("\t---------   6.删除学生信息  -----------\n");
    printf("\t---------    7.学生选课     -----------\n");
    printf("\t--------- 8.所有学生选课信息-----------\n");
    printf("\t-------------9.退出程序     -----------\n");
    printf("\t---------                  ------------\n");
}


int main()
{
    int a,i,n = 0;
    int number = 0;
    int number1 = 0;
    course cou_head = NULL;
    student stu_head = NULL;
    course new_cou = NULL;
    student new_stu = NULL;
    course del_point = NULL;
    char choice[20];
    do
     {
         Interface();
         printf("请在1-9中选择：");
         scanf("%d",&a);
         switch(a)
          {
              case 1:
              system("cls");
              new_cou = creat_cou(cou_head);
              cou_head = add_cou(cou_head,new_cou);
              break;
              case 2:
              system("cls");
              printf("\t\t---------  全部课程信息  ---------\n");
              printf("\t课程名称\t课程序号\t课程老师姓名\t课程课时\t课程教室\n");
              out_cou(cou_head);
              system("pause");
              break;
              case 3:
              system("cls");
              printf("\t课程名称\t课程序号\t课程老师姓名\t课程课时\t课程教室\n");
              out_cou(cou_head);
              printf("请输入打算删除的课程序号：");
              scanf("%d",&number);
              cou_head = delete_cou(cou_head,find_cou(cou_head,number));
              printf("删除成功！\n");
              system("pause");
              break;
              case 4:
              system("cls");
              new_stu = creat_stu(stu_head);
              stu_head = add_stu(stu_head,new_stu);
              break;
              case 5:
              system("cls");
              printf("\t\t--------  全部学生信息  ---------\n");
              printf("\t学生姓名\t学生学号\t学生性别\n");
              out_stu(stu_head);
              system("pause");
              break;
              case 6:
              system("cls");
              printf("请输入打算删除的学生的学号：\n");
              scanf("%d",&number);
              stu_head = delete_stu(stu_head,find_stu(stu_head,number));
              printf("删除成功\n");
              system("pause");
              break;
              case 7:
              system("cls");
              printf("\t学生姓名\t学生学号\t学生性别\n");
              out_stu(stu_head);
              printf("请输入选课学生学号：");
              scanf("%d",&number1);
              choice_cou(stu_head,number1,cou_head);
              system("pause");
              break;
              case 8:
              system("cls");
              printf("\t\t\t---------  全部选课信息  ---------\n");
              printf("\n");
              printf("\t学生姓名\t学生学号\t学生性别\t课程名称\t课程序号\t课程老师姓名\t课程课时\t课程教室\n");
              out_choice(stu_head);
              system("pause");
              break;
              case 9:
              return 0;
              break;
          }
     }
          
     
    while(a!=0);
    return 0;
}


course  creat_cou(course cou_head)
{
    course new_cou = (course)malloc(sizeof(course_information));
    printf("\n");
    printf("\t\t---------  请输入课程信息  ---------\n");
    printf("\n");
    printf("请输入课程名称：");
    scanf("%s",new_cou -> name);
    printf("请输入课程序号：");
    scanf("%d",&new_cou -> number);
    printf("请输入课程课时：");
    scanf("%d",&new_cou -> time);
    printf("请输入课程教室：");
    scanf("%d",&new_cou -> classroom);
    while(find_cou(cou_head,new_cou ->number)!=NULL)
      {
        printf("此序号已经有数据，请重新输入。");
        scanf("%d",&new_cou -> number);
      }
    new_cou -> next = NULL;
    return new_cou;
}
 
 course find_cou(course cou_head,int number)
 {
     if(cou_head == NULL)
     return NULL;
     if(cou_head ->number == number)
     return cou_head;
     return find_cou(cou_head -> next,number);
 }


course add_cou(course cou_head,course new_cou)
{
    if(cou_head == NULL)
    return  new_cou;
    new_cou -> next = cou_head;
    return new_cou;
}

void out_cou(course cou_head)
{
    while(cou_head)
     {
         printf("\t%s\t\t%d\t\t%s\t\t%d\t\t%d\n",cou_head -> name,cou_head -> number,cou_head -> teacher,cou_head -> time,cou_head -> classroom);
     }
}

course delete_cou(course cou_head,course  del_point)
{
    course point;
    if(del_point == NULL)
     {
         printf("没有此序号信息，请重新输入！\n");
         return  cou_head;
     }

    point = NULL;
    if(del_point == cou_head)
     {
         point = cou_head -> next;
         free(cou_head);
         return point;
     }
    point = cou_head;
    while(point)
    {
        if(point-> next == del_point)
        {
            point -> next = del_point ->next;
            free(del_point);
            return cou_head;
        }
        point = point -> next;
    }
   
}

student creat_stu(student stu_head)
{
    student new_stu = (student)malloc(sizeof(student_information));
    printf("\n");
    printf("\t\t---------  输入学生信息  ---------\n");
    printf("\n");
    printf("请输入学生姓名：");
    scanf("%s",new_stu -> name);
    printf("请输入学生学号：");
    scanf("%d",&new_stu -> number);
    printf("请输入学生性别：");
    scanf("%s",new_stu ->sex);
    while(find_stu(stu_head,new_stu -> number)!=NULL)
    {
        printf("此学号已经有数据，请重新输入。");
        scanf("%d",&new_stu -> number);
    }
    new_stu -> choices = NULL;
    new_stu -> next = NULL;
    return new_stu;
}

student find_stu(student stu_head,int number)
{
    if(stu_head == NULL)
    return NULL;
    if(stu_head -> number == number)
    return stu_head;
    return find_stu(stu_head ->next,number);
}

student add_stu(student stu_head,student new_stu)
{
    if(stu_head == NULL)
     return new_stu;
    new_stu-> next = stu_head;
    return new_stu;
}

void out_stu(student stu_head)
{
    while(stu_head)
    {
       printf("\t%s\t%d\t\t%s\n",stu_head -> name,stu_head -> number,stu_head -> sex);
    stu_head = stu_head -> next;
    }
}


student delete_stu(student stu_head,student del_point)
{
    student point;
    if(del_point == NULL)
    {
        printf("没有此学号信息，请重新输入！\n");
        return stu_head;
    }
    point = NULL;
    if(del_point == stu_head)
    {
        point = stu_head -> next;
        free(stu_head);
        return point;
    }
    point = stu_head -> next;
    while(point)
    {
       if(point -> next == del_point)
        {
            point -> next = del_point -> next;
            free(del_point);
            return stu_head;
        }
      point = point -> next;
    }
}


student choice_cou(student stu_head,int number1,course cou_head)
{
    int number;
    course point = NULL,point1 = NULL;
    course choice_point = NULL;
    student stu_point = find_stu(stu_head,number1);
    if(stu_point !=NULL)
    {
        printf("\t课程名称\t 课程序号\t 课程老师姓名\t 课程课时\t 课程教室\n");
        out_cou(cou_head);
        printf("请输入所选课程学号：");
        scanf("%d",&number);
        point = find_cou(cou_head,number);
        if(point!=NULL)
        {
            choice_point = (course)malloc(sizeof(course_information));
            memcpy(choice_point,point,sizeof(course_information));
            choice_point -> next = NULL;
            if(stu_point -> choices ==NULL)
            {
                stu_point -> choices = choice_point;
            }
            else
            {
                choice_point -> next = stu_point -> choices;
                stu_point -> choices = choice_point;
            }
            printf("恭喜你！选课成功！\n");
            return stu_head;
        }
        else
        {
            printf("没有所选学号！1");
            return stu_head;
        }
    }

    void out_choice(student stu_head)
    {
        course point = NULL;
        while(stu_head)
        {
            printf("\t\t\t\t\t\t%s\t%d\t\t%s\t\t%d\t\t%d\n",point -> name,point -> number,point -> teacher,point -> time,point -> classroom);
            point = point ->next;
        }
        stu_head = stu_head -> next;
    }
}

