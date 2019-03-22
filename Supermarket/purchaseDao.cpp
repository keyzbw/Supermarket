#include "stdafx.h"
#include "purchaseDao.h"


purchaseDao::purchaseDao()
{
}


purchaseDao::~purchaseDao()
{
}

CString purchaseDao::addPurchaseMaster(purchaseMaster pm)
{
	CString sql, purchaseNo, purchaseNo2;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)){
		return _T("");
	}
	//���ݿ��ѯ
	sql.Format(_T("SELECT Max(purchaseNo) FROM purchasemaster"));      //SQL��ѯ���
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
	purchaseNo = row[0];      //��ȡ��󶩵���
	mysql_free_result(result);

	//���ݿ����
	int r;
	r = _ttoi(purchaseNo);        //Cstringתint
	r++;
	purchaseNo.Format(_T("%d"), r);//intתCstring
	purchaseNo2.Format(_T("%06s"), purchaseNo);//����ǰ��0
	sql.Format(_T("INSERT INTO purchasemaster values('%s','%s','%s','%s','%s')"), purchaseNo2,pm.purDate,pm.purAmount,pm.employeeNo,pm.supplierNo);//SQL��ѯ���
	csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql)) //�����ݿ���в�ѯ
	{
		return _T("");
	}

	mysql_close(conn);      //�ر����ݿ�����
	return purchaseNo2;
}

bool purchaseDao::addPurchaseDetail(purchaseDetail pd)
{
	CString sql, cquantity;
	MYSQL* conn;
	conn = mysql_init(NULL);//��ʼ�����ݿ����
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0))
		return 0;
	//���ݿ����
	sql.Format(_T("INSERT INTO purchasedetail values('%s','%s','%s','%s')"), pd.purchaseNo,pd.productNo,pd.purQuantity,pd.purPrice);//SQL��ѯ���
	USES_CONVERSION;
	char* csql = T2A(sql);    //CStringתchar*
	mysql_query(conn, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ���������������
	if (mysql_query(conn, csql))  //�����ݿ���в�ѯ
		return 0;
	mysql_close(conn);      //�ر����ݿ�����
	return 1;
}
