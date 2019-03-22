#include "stdafx.h"
#include "productDao.h"


productDao::productDao()
{
}


productDao::~productDao()
{
}

product productDao::getProduct(CString productNo)
{
	product p;
	CString cnum, cprice, cdiscount;
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return p;
	}
	//���ݿ��ѯ
	sql.Format(_T("SELECT * FROM product WHERE productNo = %s"), productNo);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return p;
	}
	MYSQL_RES *result = mysql_store_result(conn); //�õ������
	if (mysql_num_rows(result) == 0)
		return p;
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	p.productNo = row[0];
	p.proName = row[1];
	p.category = row[2];
	cnum = row[3];
	p.num = _ttof(cnum);
	cprice = row[4];
	p.price = _ttof(cprice);
	p.unit = row[5];
	cdiscount = row[6];
	p.discount = _ttof(cdiscount);
	p.supplierNo = row[7];
	mysql_free_result(result);
	mysql_close(conn);      //�ر����ݿ�����
	return p;
}

bool productDao::sell(CString productNo, float num)
{
	float stockNum;
	CString cstockNum;
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return 0;
	}
	//���ݿ��ѯ
	sql.Format(_T("SELECT stockNum FROM product WHERE productNo = %s"), productNo);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return 0;
	}
	MYSQL_RES *result = mysql_store_result(conn); //�õ������
	if (mysql_num_rows(result) == 0)
		return 0;
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	cstockNum= row[0];

	stockNum = _ttof(cstockNum);
	stockNum = stockNum - num;//���ʣ������
	cstockNum.Format(_T("%7.2f"), stockNum);

	//�޸Ŀ������
	sql.Format(_T("UPDATE product set stockNum=%s WHERE productNo = %s"),cstockNum, productNo);      //SQL��ѯ���
	csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return 0;
	}
	return 1;
}

bool productDao::store(CString productNo, float num)
{
	float stockNum;
	CString cstockNum;
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return 0;
	}
	//���ݿ��ѯ
	sql.Format(_T("SELECT stockNum FROM product WHERE productNo = %s"), productNo);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return 0;
	}
	MYSQL_RES *result = mysql_store_result(conn); //�õ������
	if (mysql_num_rows(result) == 0)
		return 0;
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	cstockNum = row[0];

	stockNum = _ttof(cstockNum);
	stockNum = stockNum + num;//���ʣ������
	cstockNum.Format(_T("%7.2f"), stockNum);

	//�޸Ŀ������
	sql.Format(_T("UPDATE product set stockNum=%s WHERE productNo = %s"), cstockNum, productNo);      //SQL��ѯ���
	csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return 0;
	}
	return 1;
}

bool productDao::addProduct(product p)
{
	CString cprice, cstockNum, cdiscount;
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//���ݿ��ѯ
	cstockNum.Format(_T("%7.2f"), p.num);
	cdiscount.Format(_T("%7.2f"), p.discount);
	cprice.Format(_T("%7.2f"),p.price);
	sql.Format(_T("INSERT INTO product values('%s','%s','%s','%s','%s','%s','%s','%s')"), p.productNo,p.proName,p.category,cstockNum,cprice,p.unit,cdiscount,p.supplierNo);//SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return false;
	}

	mysql_close(conn);      //�ر����ݿ�����
	return true;
}

bool productDao::updateProduct(product p)
{
	CString cprice, cstockNum, cdiscount;
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//���ݿ��ѯ
	cstockNum.Format(_T("%7.2f"), p.num);
	cdiscount.Format(_T("%7.2f"), p.discount);
	cprice.Format(_T("%7.2f"), p.price);
	sql.Format(_T("Update product set proName='%s',category='%s',stockNum='%s',price='%s',unit='%s',discount='%s',supplierNo='%s' WHERE productNo='%s'"),p.proName, p.category, cstockNum, cprice, p.unit, cdiscount, p.supplierNo,p.productNo);//SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return false;
	}

	mysql_close(conn);      //�ر����ݿ�����
	return true;
}

bool productDao::deleteProduct(CString productNo)
{
	//�������ݿ�
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}
	//���ݿ��ѯ
	sql.Format(_T("DELETE FROM product WHERE productNo='%s'"), productNo);      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) {//�����ݿ���в�ѯ
		return false;
	}

	mysql_close(conn);      //�ر����ݿ�����
	return true;
}

