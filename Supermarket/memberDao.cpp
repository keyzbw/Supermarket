#include "stdafx.h"
#include "memberDao.h"


memberDao::memberDao()
{
}


memberDao::~memberDao()
{
}

member memberDao::getMember(CString memberNo)
{
	member m;
	CString cnum, cprice, cdiscount;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return m;
	}
	//数据库查询
	sql.Format(_T("SELECT * FROM member WHERE memberNo = %s"), memberNo);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return m;
	}
	MYSQL_RES *result = mysql_store_result(conn); //得到结果集
	if (mysql_num_rows(result) == 0)
		return m;
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	m.memberNo = row[0];
	m.memPassword = row[1];
	m.memName = row[2];
	m.sex = row[3];
	m.telephone = row[4];
	m.memLevel = row[5];
	cdiscount = row[6];
	m.discount = _ttof(cdiscount);
	mysql_free_result(result);
	mysql_close(conn);      //关闭数据库连接
	return m;
}
