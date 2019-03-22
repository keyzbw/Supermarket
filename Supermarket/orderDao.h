#pragma once
#include "orderMaster.h"
#include "orderDetail.h"
class orderDao
{
public:
	orderDao();
	~orderDao();
	CString addOrder(orderMaster om);
	bool addOrderDetail(orderDetail om);
};

