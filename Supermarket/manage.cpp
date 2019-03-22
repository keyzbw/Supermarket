// manage.cpp : 实现文件
//

#include "stdafx.h"
#include "Supermarket.h"
#include "manage.h"
#include "afxdialogex.h"


// manage 对话框

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


// manage 消息处理程序

BOOL manage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//创建子窗口
	pro_dlg.Create(IDD_PRODUCTMANAGE, this);
	e_dlg.Create(IDD_EMPLOYEEMANAGE, this);
	pur_dlg.Create(IDD_PURCHASEMANAGE, this);
	s_dlg.Create(IDD_SALEMANAGE, this);

	e_dlg.ShowWindow(SW_SHOW);//显示商品管理页面
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//显示商品管理页面
void manage::productManage()
{
	pro_dlg.ShowWindow(SW_SHOW);
	e_dlg.ShowWindow(SW_HIDE);
	pur_dlg.ShowWindow(SW_HIDE);
	s_dlg.ShowWindow(SW_HIDE);
}

//显示员工管理页面
void manage::employeeManage()
{
	pro_dlg.ShowWindow(SW_HIDE);
	e_dlg.ShowWindow(SW_SHOW);
	pur_dlg.ShowWindow(SW_HIDE);
	s_dlg.ShowWindow(SW_HIDE);
}

//显示销售管理页面
void manage::saleManage()
{
	pro_dlg.ShowWindow(SW_HIDE);
	e_dlg.ShowWindow(SW_HIDE);
	pur_dlg.ShowWindow(SW_HIDE);
	s_dlg.ShowWindow(SW_SHOW);
}

//显示采购管理页面
void manage::purchaseManage()
{
	pro_dlg.ShowWindow(SW_HIDE);
	e_dlg.ShowWindow(SW_HIDE);
	pur_dlg.ShowWindow(SW_SHOW);
	s_dlg.ShowWindow(SW_HIDE);
}
