#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	char sno[9] = "\0";
	char cno[9] = "\0";
	char grade[4] ="\0";

	int status = 0;

  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	fprintf(cgiOut, "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <title>学生信息管理系统</title> <link href=\"https://cdn.bootcss.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\">\n<style type=\"text/css\"> \nbody {height: 100%%;      background-color: lightblue;text-align: center;} ul li {list-style: none;}\n.header {        margin-bottom: 50px;}.operation>div {padding: 15px;}\n.operation.row.text-center button {outline-style: none;}.forms li {display: none; }.forms li button { margin-right: 30px;}</style></head>	<body><h1 class=\"header text-center\">学生信息管理系统</h1>\n");
	
	status = cgiFormString("sno",  sno, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}

	status = cgiFormString("cno", cno, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("grade",  grade, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get grade error!\n");
		return 1;
	}

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	mysql_options(db,MYSQL_SET_CHARSET_NAME,"utf8");
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

	strcpy(sql, "create table Score(ino int(9), cno int(9), grade int(4), foreign key(ino) references Information(ino), foreign key(cno) references Course(cno),primary key(ino,cno))character set = utf8;");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}

	sprintf(sql, "insert into Score values(%d, %d, %d)", atoi(sno), atoi(cno), atoi(grade));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add Score ok!\n");
	mysql_close(db);
	return 0;
}
