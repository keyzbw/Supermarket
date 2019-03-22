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
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)){
		return _T("");
	}
	//数据库查询
	sql.Format(_T("SELECT Max(purchaseNo) FROM purchasemaster"));      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) //对数据库进行查询
	{
		return _T("");
	}
	MYSQL_RES *result = mysql_store_result(conn); //得到结果集
	if (mysql_num_rows(result) == 0)
		return _T("");
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	purchaseNo = row[0];      //获取最大订单号
	mysql_free_result(result);

	//数据库插入
	int r;
	r = _ttoi(purchaseNo);        //Cstring转int
	r++;
	purchaseNo.Format(_T("%d"), r);//int转Cstring
	purchaseNo2.Format(_T("%06s"), purchaseNo);//数字前补0
	sql.Format(_T("INSERT INTO purchasemaster values('%s','%s','%s','%s','%s')"), purchaseNo2,pm.purDate,pm.purAmount,pm.employeeNo,pm.supplierNo);//SQL查询语句
	csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) //对数据库进行查询
	{
		return _T("");
	}

	mysql_close(conn);      //关闭数据库连接
	return purchaseNo2;
}

bool purchaseDao::addPurchaseDetail(purchaseDetail pd)
{
	CString sql, cquantity;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0))
		return 0;
	//数据库插入
	sql.Format(_T("INSERT INTO purchasedetail values('%s','%s','%s','%s')"), pd.purchaseNo,pd.productNo,pd.purQuantity,pd.purPrice);//SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql))  //对数据库进行查询
		return 0;
	mysql_close(conn);      //关闭数据库连接
	return 1;
}
