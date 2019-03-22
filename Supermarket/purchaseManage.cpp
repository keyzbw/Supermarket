// purchaseManage.cpp : 实现文件
//

#include "stdafx.h"
#include "Supermarket.h"
#include "purchaseManage.h"
#include "afxdialogex.h"


// purchaseManage 对话框

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


// purchaseManage 消息处理程序


BOOL purchaseManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化列表
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 插入列并设置每一列的宽度
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, 75);
	m_list.InsertColumn(1, _T("采购单号"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(2, _T("采购金额"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(3, _T("采购员"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(4, _T("采购时间"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(5, _T("供应商"), LVCFMT_CENTER, 75);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
