#pragma once
#include "afxcmn.h"


// purchase �Ի���

class purchase : public CDialogEx
{
	DECLARE_DYNAMIC(purchase)

public:
	purchase(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~purchase();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PURCHASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int nItem=0;
	CString employeeNo;
	CString productNo;
	float quantity;
	float price;
	float Amount;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	CString supplierNo;
};
