// saleManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Supermarket.h"
#include "saleManage.h"
#include "afxdialogex.h"


// saleManage �Ի���

IMPLEMENT_DYNAMIC(saleManage, CDialogEx)

saleManage::saleManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SALEMANAGE, pParent)
{

}

saleManage::~saleManage()
{
}

void saleManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(saleManage, CDialogEx)
END_MESSAGE_MAP()


// saleManage ��Ϣ�������


BOOL saleManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��ʼ���б�
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// �����в�����ÿһ�еĿ��
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, 75);
	m_list.InsertColumn(1, _T("�������"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(2, _T("Ӧ�ս��"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(3, _T("ʵ�ս��"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(4, _T("����Ա"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(5, _T("ʱ��"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(6, _T("֧����ʽ"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(7, _T("��Ա��"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(8, _T("��Ʊ��"), LVCFMT_CENTER, 75);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
