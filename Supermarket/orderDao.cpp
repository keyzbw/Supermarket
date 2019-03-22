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
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0))
	{
		return _T("");
	}

	//数据库查询
	sql.Format(_T("SELECT Max(orderNo) FROM ordermaster"));      //SQL查询语句
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
	orderNo = row[0];      //获取最大订单号
	mysql_free_result(result);


	//数据库插入
	int r;
	r = _ttoi(orderNo);        //Cstring转int
	r++;
	orderNo.Format(_T("%d"), r);//int转Cstring
	orderNo2.Format(_T("%06s"), orderNo);//数字前补0
	sql.Format(_T("INSERT INTO ordermaster values('%s','%s','%s','%s','%s','%s','%s','%s')"), orderNo2,om.orderDate, om.tolAmtReceive,om.tolPaidAmt,om.payWay,om.employeeNo,om.memberNo,om.invoiceNo);//SQL查询语句
	csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) //对数据库进行查询
	{
		return _T("");
	}

	mysql_close(conn);      //关闭数据库连接
	return orderNo2;
}

bool orderDao::addOrderDetail(orderDetail od)
{
	CString sql,cquantity;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0))
		return 0;
	//数据库插入
	cquantity.Format(_T("%7.2f"), od.quantity);
	sql.Format(_T("INSERT INTO orderdetail values('%s','%s','%s')"),od.orderNo,od.productNo,cquantity);//SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql))  //对数据库进行查询
		return 0;

	mysql_close(conn);      //关闭数据库连接
	return 1;
}
