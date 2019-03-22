#include "stdafx.h"
#include "orderDao.h"


orderDao::orderDao()
{
}


orderDao::~orderDao()
{
}

CString orderDao::addOrder(orderMaster om)
{
	CString sql, orderNo, orderNo2;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0))
	{
		return _T("");
	}

	//���ݿ��ѯ
	sql.Format(_T("SELECT Max(orderNo) FROM ordermaster"));      //SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) //�����ݿ���в�ѯ
	{
		return _T("");
	}
	MYSQL_RES *result = mysql_store_result(conn); //�õ������
	if (mysql_num_rows(result) == 0)
		return _T("");
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	orderNo = row[0];      //��ȡ��󶩵���
	mysql_free_result(result);


	//���ݿ����
	int r;
	r = _ttoi(orderNo);        //Cstringתint
	r++;
	orderNo.Format(_T("%d"), r);//intתCstring
	orderNo2.Format(_T("%06s"), orderNo);//����ǰ��0
	sql.Format(_T("INSERT INTO ordermaster values('%s','%s','%s','%s','%s','%s','%s','%s')"), orderNo2,om.orderDate, om.tolAmtReceive,om.tolPaidAmt,om.payWay,om.employeeNo,om.memberNo,om.invoiceNo);//SQL��ѯ���
	csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) //�����ݿ���в�ѯ
	{
		return _T("");
	}

	mysql_close(conn);      //�ر����ݿ�����
	return orderNo2;
}

bool orderDao::addOrderDetail(orderDetail od)
{
	CString sql,cquantity;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0))
		return 0;
	//���ݿ����
	cquantity.Format(_T("%7.2f"), od.quantity);
	sql.Format(_T("INSERT INTO orderdetail values('%s','%s','%s')"),od.orderNo,od.productNo,cquantity);//SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql))  //�����ݿ���в�ѯ
		return 0;

	mysql_close(conn);      //�ر����ݿ�����
	return 1;
}
