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
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)){
		return e;
	}

	//���ݿ��ѯ
	sql.Format(_T("SELECT * FROM employee WHERE employeeNo = %s"), employeeNo);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return e;
	}
	MYSQL_RES *result = mysql_store_result(conn); //�õ������
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

	mysql_close(conn);      //�ر����ݿ�����
	return e;
}

bool employeeDao::addEmployee(employee e)
{
	CString csalary;
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//���ݿ��ѯ
	csalary.Format(_T("%7.2f"), e.salary);
	sql.Format(_T("INSERT INTO employee values('%s','%s','%s','%s','%s','%s','%s')"),e.employeeNo,e.empPassword,e.empName,e.sex,e.title,csalary,e.telephone);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return false;
	}

	mysql_close(conn);      //�ر����ݿ�����
	return true;
}

bool employeeDao::updateEmployee(employee e)
{
	CString csalary;
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//���ݿ��ѯ
	csalary.Format(_T("%7.2f"), e.salary);
	sql.Format(_T("UPDATE employee set empPassword='%s',empName='%s',sex='%s',title='%s',salary='%s',telephone='%s' WHERE employeeNo='%s'"),e.empPassword, e.empName, e.sex, e.title, csalary, e.telephone,e.employeeNo);//SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return false;
	}

	mysql_close(conn);      //�ر����ݿ�����
	return true;
}

bool employeeDao::deleteEmployee(CString employeeNo)
{
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}
	//���ݿ��ѯ
	sql.Format(_T("DELETE FROM employee WHERE employeeNo='%s'"), employeeNo);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return false;
	}

	mysql_close(conn);      //�ر����ݿ�����
	return true;
}
