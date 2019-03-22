// saleManage.cpp : 实现文件
//

#include "stdafx.h"
#include "Supermarket.h"
#include "saleManage.h"
#include "afxdialogex.h"


// saleManage 对话框

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


// saleManage 消息处理程序


BOOL saleManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化列表
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 插入列并设置每一列的宽度
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, 75);
	m_list.InsertColumn(1, _T("订单编号"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(2, _T("应收金额"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(3, _T("实收金额"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(4, _T("收银员"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(5, _T("时间"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(6, _T("支付方式"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(7, _T("会员号"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(8, _T("发票号"), LVCFMT_CENTER, 75);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
