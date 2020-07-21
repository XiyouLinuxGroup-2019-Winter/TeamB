/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月21日 星期二 16时32分38秒
 ************************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <mysql/mysql.h>
int main()
{
    MYSQL mysql;
    if(mysql_init(&mysql)==NULL){
        printf("13.mysql_init\n");
    }
    if(mysql_library_init(0,NULL,NULL)<0){
        printf("16.mysql_library_init\n");
    }
    if(NULL == mysql_real_connect(&mysql,"127.0.0.1","root","Lyj011007.","test",0,NULL,0)){
		printf("19.mysql_real_connect\n");
	}
    if(mysql_set_character_set(&mysql, "utf8") < 0){
		printf("23.mysql_set_character_set\n");
	}
	printf("连接mysql数据库成功!\n");
    int                 i;
	int                 ret;
	unsigned int        num_fields;
	MYSQL_RES           *result = NULL;
	MYSQL_ROW           row;
	MYSQL_FIELD         *field;
    char *string="select * from stu";
	ret = mysql_query(&mysql, string);
	if(!ret){
		result = mysql_store_result(&mysql);
		if(result){
			num_fields = mysql_num_fields(result);
			while((field = mysql_fetch_field(result))){
				printf("%-20s", field->name);
			}
			printf("\n");

			while(row = mysql_fetch_row(result)){
				for(i = 0; i < num_fields; i++){
					if(row[i]){
						printf("%-20s", row[i]);
					}
				}
				printf("\n");
			}
		}
		mysql_free_result(result);
	}
	else{
		printf("query fail\n");
		return -1;
	}
    mysql_close(&mysql);
	mysql_library_end();
	printf("end\n");
	return 0;
}
