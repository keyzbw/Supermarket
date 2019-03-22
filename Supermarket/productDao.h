#pragma once
#include "product.h" 
class productDao
{
public:
	productDao();
	~productDao();
	product getProduct(CString productNo);
	bool sell(CString productNo,float num);
	bool store(CString productNo, float num);
	bool addProduct(product p);
	bool updateProduct(product p);
	bool deleteProduct(CString productNo);
};

