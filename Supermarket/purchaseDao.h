#pragma once
#include "purchaseMaster.h"
#include "purchaseDetail.h"
class purchaseDao
{
public:
	purchaseDao();
	~purchaseDao();
	CString addPurchaseMaster(purchaseMaster pm);
	bool addPurchaseDetail(purchaseDetail pd);
};

