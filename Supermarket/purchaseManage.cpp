// purchaseManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Supermarket.h"
#include "purchaseManage.h"
#include "afxdialogex.h"


// purchaseManage �Ի���

IMPLEMENT_DYNAMIC(purchaseManage, CDialogEx)

purchaseManage::purchaseManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PURCHASEMANAGE, pParent)
{

}

purchaseManage::~purchaseManage()
{
}

void purchaseManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(purchaseManage, CDialogEx)
END_MESSAGE_MAP()


// purchaseManage ��Ϣ�������


BOOL purchaseManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��ʼ���б�
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// �����в�����ÿһ�еĿ��
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, 75);
	m_list.InsertColumn(1, _T("�ɹ�����"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(2, _T("�ɹ����"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(3, _T("�ɹ�Ա"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(4, _T("�ɹ�ʱ��"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(5, _T("��Ӧ��"), LVCFMT_CENTER, 75);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
