#pragma once
#include "afxcmn.h"


// purchaseManage 对话框

class purchaseManage : public CDialogEx
{
	DECLARE_DYNAMIC(purchaseManage)

public:
	purchaseManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~purchaseManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PURCHASEMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
};
