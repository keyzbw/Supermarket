#pragma once
#include "productManage.h"
#include "employeeManage.h"
#include "purchaseManage.h"
#include "saleManage.h"

// manage �Ի���

class manage : public CDialogEx
{
	DECLARE_DYNAMIC(manage)

public:
	manage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~manage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	productManage pro_dlg;
	employeeManage e_dlg;
	purchaseManage pur_dlg;
	saleManage s_dlg;
	CString employeeNo;
	afx_msg void productManage();
	virtual BOOL OnInitDialog();
	afx_msg void employeeManage();
	afx_msg void saleManage();
	afx_msg void purchaseManage();
};
