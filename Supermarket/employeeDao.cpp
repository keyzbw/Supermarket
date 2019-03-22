#include "stdafx.h"
#include "employeeDao.h"


employeeDao::employeeDao()
{
}


employeeDao::~employeeDao()
{
}

employee employeeDao::getEmployee(CString employeeNo)
{
	employee e;
	CString csalary;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)){
		return e;
	}

	//数据库查询
	sql.Format(_T("SELECT * FROM employee WHERE employeeNo = %s"), employeeNo);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return e;
	}
	MYSQL_RES *result = mysql_store_result(conn); //得到结果集
	if (mysql_num_rows(result) == 0)
		return e;
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	e.employeeNo = row[0];
	e.empPassword = row[1];
	e.empName = row[2];
	e.sex = row[3];
	e.title = row[4];
	csalary = row[5];
	e.salary = _ttof(csalary);
	e.telephone = row[6];
	mysql_free_result(result);

	mysql_close(conn);      //关闭数据库连接
	return e;
}

bool employeeDao::addEmployee(employee e)
{
	CString csalary;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//数据库查询
	csalary.Format(_T("%7.2f"), e.salary);
	sql.Format(_T("INSERT INTO employee values('%s','%s','%s','%s','%s','%s','%s')"),e.employeeNo,e.empPassword,e.empName,e.sex,e.title,csalary,e.telephone);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return false;
	}

	mysql_close(conn);      //关闭数据库连接
	return true;
}

bool employeeDao::updateEmployee(employee e)
{
	CString csalary;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//数据库查询
	csalary.Format(_T("%7.2f"), e.salary);
	sql.Format(_T("UPDATE employee set empPassword='%s',empName='%s',sex='%s',title='%s',salary='%s',telephone='%s' WHERE employeeNo='%s'"),e.empPassword, e.empName, e.sex, e.title, csalary, e.telephone,e.employeeNo);//SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return false;
	}

	mysql_close(conn);      //关闭数据库连接
	return true;
}

bool employeeDao::deleteEmployee(CString employeeNo)
{
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}
	//数据库查询
	sql.Format(_T("DELETE FROM employee WHERE employeeNo='%s'"), employeeNo);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return false;
	}

	mysql_close(conn);      //关闭数据库连接
	return true;
}
