#ifndef   __MYSQL_H_
#define   __MYSQL_H_

#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include "main.h"

#define   LOGIN     0
#define   REGIEST   1
#define   SHOW      2
#define   FRIENDLIST       3
#define   DELETE     4
#define   ADDING     5
#define   ERROR      -999

int MysqlCreateTable();
int MysqlInsert(char* id, char *name, char *passwd);
int MysqlSelect(char* id, char *passwd, int flag, struct OnlineInfo *info);
int MysqlUpdate(char* id, char *friend, int flag);


#endif
