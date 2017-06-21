#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

  char cno[9] = "\0";
	char cname[9] = "\0";
	char sid[9] = "\0";
  char credit[4] ="\0";

	int status = 0;

  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	status = cgiFormString("cno",  cno, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("cname",  cname, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cname error!\n");
		return 1;
	}

	status = cgiFormString("sid",  sid, 9);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sid error!\n");
		return 1;
	}

  status = cgiFormString("credit",  credit, 4);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get credit error!\n");
		return 1;
	}

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

	sprintf(sql, "update Course set cname='%s', sid=%d, credit=%d where cno = %d ", cname, atoi(sid), atoi(credit), atoi(cno));
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "update Course ok!\n");
	mysql_close(db);
	return 0;
}