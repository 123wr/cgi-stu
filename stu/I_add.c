#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname = "head.html";
char * footname = "footer.html";

int cgiMain()
{

	FILE * fd;

	char ino[9] = "\0";
	char iname[9] = "\0";
	char sex[4] = "\0";
	char age[4] = "\0";
	char sid[9] = "\0";
	char ch;
	int status = 0;

  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname,"r"))){
		fprintf(cgiOut,"Cannot open file, %s\n",headname);
		return -1;
	}
	ch =fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
	}
	fclose(fd);

	status = cgiFormString("ino",  ino, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get ino error!\n");
		return 1;
	}

	status = cgiFormString("iname",  iname, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get iname error!\n");
		return 1;
	}

	status = cgiFormString("sex",  sex, 4);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}

	status = cgiFormString("age",  age, 4);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get age error!\n");
		return 1;
	}

	status = cgiFormString("sid",  sid, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sid error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	strcpy(sql, "create table Information(ino int not null primary key, iname varchar(9) not null, sex char(4) not null, age int not null,sid int)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}

	sprintf(sql, "insert into Information values(%d, '%s', '%s', %d, %d)", atoi(ino), iname, sex, atoi(age), atoi(sid));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
