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
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return p;
	}
	//数据库查询
	sql.Format(_T("SELECT * FROM product WHERE productNo = %s"), productNo);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return p;
	}
	MYSQL_RES *result = mysql_store_result(conn); //得到结果集
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
	mysql_close(conn);      //关闭数据库连接
	return p;
}

bool productDao::sell(CString productNo, float num)
{
	float stockNum;
	CString cstockNum;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return 0;
	}
	//数据库查询
	sql.Format(_T("SELECT stockNum FROM product WHERE productNo = %s"), productNo);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return 0;
	}
	MYSQL_RES *result = mysql_store_result(conn); //得到结果集
	if (mysql_num_rows(result) == 0)
		return 0;
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	cstockNum= row[0];

	stockNum = _ttof(cstockNum);
	stockNum = stockNum - num;//算出剩余数量
	cstockNum.Format(_T("%7.2f"), stockNum);

	//修改库存数量
	sql.Format(_T("UPDATE product set stockNum=%s WHERE productNo = %s"),cstockNum, productNo);      //SQL查询语句
	csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return 0;
	}
	return 1;
}

bool productDao::store(CString productNo, float num)
{
	float stockNum;
	CString cstockNum;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return 0;
	}
	//数据库查询
	sql.Format(_T("SELECT stockNum FROM product WHERE productNo = %s"), productNo);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return 0;
	}
	MYSQL_RES *result = mysql_store_result(conn); //得到结果集
	if (mysql_num_rows(result) == 0)
		return 0;
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	cstockNum = row[0];

	stockNum = _ttof(cstockNum);
	stockNum = stockNum + num;//算出剩余数量
	cstockNum.Format(_T("%7.2f"), stockNum);

	//修改库存数量
	sql.Format(_T("UPDATE product set stockNum=%s WHERE productNo = %s"), cstockNum, productNo);      //SQL查询语句
	csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return 0;
	}
	return 1;
}

bool productDao::addProduct(product p)
{
	CString cprice, cstockNum, cdiscount;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//数据库查询
	cstockNum.Format(_T("%7.2f"), p.num);
	cdiscount.Format(_T("%7.2f"), p.discount);
	cprice.Format(_T("%7.2f"),p.price);
	sql.Format(_T("INSERT INTO product values('%s','%s','%s','%s','%s','%s','%s','%s')"), p.productNo,p.proName,p.category,cstockNum,cprice,p.unit,cdiscount,p.supplierNo);//SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return false;
	}

	mysql_close(conn);      //关闭数据库连接
	return true;
}

bool productDao::updateProduct(product p)
{
	CString cprice, cstockNum, cdiscount;
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}

	//数据库查询
	cstockNum.Format(_T("%7.2f"), p.num);
	cdiscount.Format(_T("%7.2f"), p.discount);
	cprice.Format(_T("%7.2f"), p.price);
	sql.Format(_T("Update product set proName='%s',category='%s',stockNum='%s',price='%s',unit='%s',discount='%s',supplierNo='%s' WHERE productNo='%s'"),p.proName, p.category, cstockNum, cprice, p.unit, cdiscount, p.supplierNo,p.productNo);//SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return false;
	}

	mysql_close(conn);      //关闭数据库连接
	return true;
}

bool productDao::deleteProduct(CString productNo)
{
	//连接数据库
	CString sql;
	MYSQL* conn;
	conn = mysql_init(NULL);//初始化数据库对象
	if (!mysql_real_connect(conn, "localhost", "root", "123456", "supermarket", 3306, NULL, 0)) {
		return false;
	}
	//数据库查询
	sql.Format(_T("DELETE FROM product WHERE productNo='%s'"), productNo);      //SQL查询语句
	USES_CONVERSION;
	char* csql = T2A(sql);    //CString转char*
	mysql_query(conn, "SET NAMES 'GB2312'");//设置数据库字符格式，解决中文乱码问
	if (mysql_query(conn, csql)) {//对数据库进行查询
		return false;
	}

	mysql_close(conn);      //关闭数据库连接
	return true;
}

