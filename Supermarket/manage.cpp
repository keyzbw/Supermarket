// manage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Supermarket.h"
#include "manage.h"
#include "afxdialogex.h"


// manage �Ի���

IMPLEMENT_DYNAMIC(manage, CDialogEx)

manage::manage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANAGE, pParent)
{

}

manage::~manage()
{
}

void manage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(manage, CDialogEx)
	ON_COMMAND(ID_32772, &manage::productManage)
	ON_COMMAND(ID_32773, &manage::employeeManage)
	ON_COMMAND(ID_32774, &manage::saleManage)
	ON_COMMAND(ID_32775, &manage::purchaseManage)
END_MESSAGE_MAP()


// manage ��Ϣ�������

BOOL manage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//�����Ӵ���
	pro_dlg.Create(IDD_PRODUCTMANAGE, this);
	e_dlg.Create(IDD_EMPLOYEEMANAGE, this);
	pur_dlg.Create(IDD_PURCHASEMANAGE, this);
	s_dlg.Create(IDD_SALEMANAGE, this);

	e_dlg.ShowWindow(SW_SHOW);//��ʾ��Ʒ����ҳ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//��ʾ��Ʒ����ҳ��
void manage::productManage()
{
	pro_dlg.ShowWindow(SW_SHOW);
	e_dlg.ShowWindow(SW_HIDE);
	pur_dlg.ShowWindow(SW_HIDE);
	s_dlg.ShowWindow(SW_HIDE);
}

//��ʾԱ������ҳ��
void manage::employeeManage()
{
	pro_dlg.ShowWindow(SW_HIDE);
	e_dlg.ShowWindow(SW_SHOW);
	pur_dlg.ShowWindow(SW_HIDE);
	s_dlg.ShowWindow(SW_HIDE);
}

//��ʾ���۹���ҳ��
void manage::saleManage()
{
	pro_dlg.ShowWindow(SW_HIDE);
	e_dlg.ShowWindow(SW_HIDE);
	pur_dlg.ShowWindow(SW_HIDE);
	s_dlg.ShowWindow(SW_SHOW);
}

//��ʾ�ɹ�����ҳ��
void manage::purchaseManage()
{
	pro_dlg.ShowWindow(SW_HIDE);
	e_dlg.ShowWindow(SW_HIDE);
	pur_dlg.ShowWindow(SW_SHOW);
	s_dlg.ShowWindow(SW_HIDE);
}
