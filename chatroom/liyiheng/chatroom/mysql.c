#include "mysql.h"
#include <string.h>

int MysqlCreateTable()
{
    MYSQL *conn;
    conn = mysql_init(NULL);
    if((conn = mysql_real_connect(conn, "127.0.0.1", "root", "2219285", "test", 0, NULL, 0)) == NULL)
    {
        printf("%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "CREATE TABLE if not exists test.chat(id varchar(20), name varchar(20), passwd varchar(20), friendlist varchar(1000));"))
    {  
        printf("%s\n", mysql_error(conn)); 
        exit(1);
    }
	printf("数据库初始化成功！.................\n");
    mysql_close(conn);

    return 0;
}

int MysqlInsert(char* id, char *name, char *passwd)
{
    MYSQL *conn;
    conn = mysql_init(NULL);
	char insertSql[300] = {0};
	strcat(insertSql, "INSERT INTO test.chat(id, name, passwd) VALUES(");
	strcat(insertSql, id);
	strcat(insertSql, ",'");
	strcat(insertSql, name);
	strcat(insertSql, "',");
	strcat(insertSql, passwd);
	strcat(insertSql, ");");
    if((conn = mysql_real_connect(conn, "127.0.0.1", "root", "2219285", "test", 0, NULL, 0)) == NULL)
    {
        printf("%s\n", mysql_error(conn));
        exit(1);
    }
	
    if (mysql_query(conn, insertSql))
    {  
        printf("%s\n", mysql_error(conn)); 
        exit(1);
    }

	return 0;
}

int MysqlSelect(char* id, char *passwd, int flag, struct OnlineInfo *info)
{
    MYSQL_RES *res_ptr;
	MYSQL_ROW record;
    MYSQL *conn;
    conn = mysql_init(NULL);
	char selectSql[300] = {0};
	
	if (flag == REGIEST)
	{		
		strcat(selectSql, "SELECT * FROM test.chat where id='");
		strcat(selectSql, id);
		strcat(selectSql, "';");		
	}
	else if (flag == LOGIN)
	{
		strcat(selectSql, "SELECT * FROM test.chat where id='");
		strcat(selectSql, id);
		strcat(selectSql, "' AND ");
		strcat(selectSql, "passwd='");
		strcat(selectSql, passwd);
		strcat(selectSql, "';");
	}
	else if (flag == SHOW)
	{
		strcat(selectSql, "SELECT id FROM test.chat;");
	}
	else if (flag == FRIENDLIST)
	{
		strcat(selectSql, "SELECT friendlist FROM test.chat where id='");
		strcat(selectSql, passwd);
		strcat(selectSql, "';");
	}
	else if (flag == LOAD)
	{
		strcat(selectSql, "SELECT friendlist FROM test.chat where id='");
		strcat(selectSql, id);
		strcat(selectSql, "';");
	}
	
    if((conn = mysql_real_connect(conn, "127.0.0.1", "root", "2219285", "test", 0, NULL, 0)) == NULL)
    {
        printf("%s\n", mysql_error(conn));
        exit(1);
    }
	
    if (mysql_query(conn, selectSql))
    {  
        printf("%s\n", mysql_error(conn)); 
        exit(1);
    }

    res_ptr = mysql_store_result(conn);
	int i = 0;
	while((record = mysql_fetch_row(res_ptr))) 
	{
		if (flag == SHOW)
		{
			if (strcmp(record[0], id))
				strcpy(info->users[i++].ID, record[0]);
		}
		else if (flag == FRIENDLIST)
		{
			if (record[0])
			{
				char *p = strtok(record[0], ",");
				while (p)
				{
					if (!strcmp(p, id))
					{
						return 1;
					}
					p = strtok(NULL, ",");
				}
			}
		}
		else if (flag == LOAD)
		{
			if (record[0])
			{
				char *p = strtok(record[0], ",");
				while (p)
				{
					if (strcmp(record[0], id))
						strcpy(info->users[i++].ID, record[0]);
					p = strtok(NULL, ",");
				}
			}
		}
		else
		{
			return 1;
		}
	}

	if (flag == SHOW)
	{
		return i;
	}
	
	return 0;
}

int MysqlUpdate(char* id, char *friend, int flag)
{
    MYSQL_RES *res_ptr;
	MYSQL_ROW record;
    MYSQL *conn;
    conn = mysql_init(NULL);
	char updateSql[300] = {0};
	char list[1024] = {0};
	
	strcat(updateSql, "SELECT friendlist FROM test.chat where id='");
	strcat(updateSql, id);
	strcat(updateSql, "';");
	
    if((conn = mysql_real_connect(conn, "127.0.0.1", "root", "2219285", "test", 0, NULL, 0)) == NULL)
    {
        printf("%s\n", mysql_error(conn));
        exit(1);
    }
	
    if (mysql_query(conn, updateSql))
    {  
        printf("%s\n", mysql_error(conn)); 
        exit(1);
    }
	
    res_ptr = mysql_store_result(conn);

	if (flag == ADDING)
	{
		while((record = mysql_fetch_row(res_ptr))) 
		{
			if (record[0])
			{
				strcpy(list, record[0]);
				strcat(list, ",");
				strcat(list, friend);
			}
			else
			{
				strcpy(list, friend);
			}
		}
		
		mysql_free_result(res_ptr);
		memset(updateSql, 0, sizeof(updateSql));
		
		strcat(updateSql, "UPDATE test.chat SET friendlist='");
		strcat(updateSql, list);
		strcat(updateSql, "' where id='");
		strcat(updateSql, id);
		strcat(updateSql, "';");

		printf("%s ]]] = \n", updateSql);
		
		if (mysql_query(conn, updateSql))
	    {  
	        printf("%s\n", mysql_error(conn)); 
	        exit(1);
	    }
	}
	else if (flag == DELETE)
	{
		while((record = mysql_fetch_row(res_ptr))) 
		{
			if (record[0] == NULL)
			{
				return ERROR;
			}
			else
			{
				char *p = strtok(record[0], ",");
				while(p)
				{
					if (strcmp(p, friend))
					{
						strcpy(list, p);
						strcat(list, ",");
					}
					p = strtok(NULL, ",");
				}
				if (strlen(list) == 0)
				{
					return ERROR;
				}
				
				list[strlen(list)-1] = '\0';
				mysql_free_result(res_ptr);
				memset(updateSql, 0, sizeof(updateSql));
				
				strcat(updateSql, "UPDATE test.chat SET friendlist='");
				strcat(updateSql, list);
				strcat(updateSql, "' where id='");
				strcat(updateSql, id);
				strcat(updateSql, "';");
				
				if (mysql_query(conn, updateSql))
			    {  
			        printf("%s\n", mysql_error(conn)); 
			        exit(1);
			    }
			}
		}		
	}
	
	return 0;
}

