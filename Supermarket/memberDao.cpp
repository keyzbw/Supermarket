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
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return m;
	}
	//���ݿ��ѯ
	sql.Format(_T("SELECT * FROM member WHERE memberNo = %s"), memberNo);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return m;
	}
	MYSQL_RES *result = mysql_store_result(conn); //�õ������
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
	mysql_close(conn);      //�ر����ݿ�����
	return m;
}
