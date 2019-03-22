#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// sale 对话框

class sale : public CDialogEx
{
	DECLARE_DYNAMIC(sale)

public:
	sale(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~sale();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CString employeeNo;
	CString invoiceNo;
	CString productNo;
	float num;
	int itemNum=0;
	afx_msg void OnBnClickedButton1();
	float shouldPay;
	float truePay;
	float change;
	float discount;
	CString memName;
	CString memberNo;
	afx_msg void OnBnClickedButton2();
	CString memLevel;
	float allSum;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton3();
	CComboBox m_combo;
	afx_msg void OnBnClickedButton4();
};
