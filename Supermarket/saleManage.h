#pragma once
#include "afxcmn.h"


// saleManage �Ի���

class saleManage : public CDialogEx
{
	DECLARE_DYNAMIC(saleManage)

public:
	saleManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~saleManage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SALEMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
};
