#pragma once
#include "afxcmn.h"


// purchaseManage �Ի���

class purchaseManage : public CDialogEx
{
	DECLARE_DYNAMIC(purchaseManage)

public:
	purchaseManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~purchaseManage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PURCHASEMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
};
