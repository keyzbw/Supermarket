// purchase.cpp : 实现文件
//

#include "stdafx.h"
#include "Supermarket.h"
#include "purchase.h"
#include "afxdialogex.h"
#include "productDao.h"
#include "purchaseDao.h"


// purchase 对话框

IMPLEMENT_DYNAMIC(purchase, CDialogEx)

purchase::purchase(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PURCHASE, pParent)
	, productNo(_T(""))
	, quantity(0)
	, price(0)
	, Amount(0)
	, supplierNo(_T(""))
{

}

purchase::~purchase()
{
}

void purchase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT11, productNo);
	DDX_Text(pDX, IDC_EDIT12, quantity);
	DDX_Text(pDX, IDC_EDIT14, price);
	DDX_Text(pDX, IDC_EDIT13, Amount);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT15, supplierNo);
}


BEGIN_MESSAGE_MAP(purchase, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &purchase::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &purchase::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &purchase::OnBnClickedButton3)
END_MESSAGE_MAP()


// purchase 消息处理程序

BOOL purchase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化列表
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 插入列并设置每一列的宽度
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, 75);
	m_list.InsertColumn(1, _T("商品编号"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(2, _T("商品名称"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(3, _T("数量"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(4, _T("单价"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(5, _T("计量单位"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(6, _T("金额"), LVCFMT_CENTER, 75);

	//设置初始数据
	UpdateData(FALSE);//数据更新至窗口

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//添加商品
void purchase::OnBnClickedButton1()
{
	UpdateData(TRUE);//从窗口获取数据

	productDao pDao;
	product p;
	double sum;
	CString cnum, cprice,csum;
	p = pDao.getProduct(productNo);//获取商品信息

	//列表显示
	m_list.InsertItem(0, _T(""));
	m_list.SetItemText(0, 1, p.productNo);
	m_list.SetItemText(0, 2, p.proName);
	cnum.Format(_T("%7.2f"), quantity);
	m_list.SetItemText(0, 3, cnum);
	cprice.Format(_T("%7.2f"), price);
	m_list.SetItemText(0, 4, cprice);
	m_list.SetItemText(0, 5, p.unit);
	sum = price*quantity;//计算单项金额
	csum.Format(_T("%7.2f"), sum);
	m_list.SetItemText(0, 6, csum);
	Amount += sum;//计算总金额

	nItem++;//商品项数加一
	productNo = "";	quantity = 0; price = 0;//清除输入框数据
	UpdateData(FALSE);//数据更新至窗口
}

void purchase::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//从窗口获取数据
	purchaseMaster pm;
	purchaseDao purDao;
	productDao proDao;
	purchaseDetail pd;
	//获取订单主表数据
	pm.employeeNo = employeeNo;
	pm.supplierNo = supplierNo;
	pm.purAmount.Format(_T("%7.2f"), Amount);
	//获取当前时间
	CTime tm;
	tm = CTime::GetCurrentTime();
	pm.purDate = tm.Format(_T("%Y-%m-%d %X"));

	pd.purchaseNo = purDao.addPurchaseMaster(pm);//提交订单细节
	for (int i = 0; i < nItem; i++) {
		pd.productNo = m_list.GetItemText(i, 1);
		pd.purQuantity = m_list.GetItemText(i, 3);
		pd.purPrice = m_list.GetItemText(i, 4);
		purDao.addPurchaseDetail(pd); //插入数据库
		proDao.store(pd.productNo, _ttof(pd.purQuantity));
	}

	MessageBox(_T("采购完成！"));
	//清除数据
	m_list.DeleteAllItems();
	nItem = 0;
	Amount = 0;
	UpdateData(FALSE);//数据更新至窗口
}

//取消订单
void purchase::OnBnClickedButton3()
{
	//清除数据
	m_list.DeleteAllItems();
	nItem = 0;
	Amount = 0;
	UpdateData(FALSE);//数据更新至窗口
}
