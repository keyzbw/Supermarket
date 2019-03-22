#pragma once
#include "afxcmn.h"


// saleManage 对话框

class saleManage : public CDialogEx
{
	DECLARE_DYNAMIC(saleManage)

public:
	saleManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~saleManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SALEMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
};
