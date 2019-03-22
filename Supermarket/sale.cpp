// sale.cpp : 实现文件
//

#include "stdafx.h"
#include "Supermarket.h"
#include "sale.h"
#include "afxdialogex.h"
#include "productDao.h"
#include "memberDao.h"
#include "orderDao.h"
#include <time.h>

// sale 对话框

IMPLEMENT_DYNAMIC(sale, CDialogEx)

sale::sale(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SALE, pParent)
	, employeeNo(_T(""))
	, invoiceNo(_T(""))
	, productNo(_T(""))
	, num(0)
	, shouldPay(0)
	, truePay(0)
	, change(0)
	, discount(0)
	, memName(_T(""))
	, memberNo(_T(""))
	, memLevel(_T(""))
	, allSum(0)
{

}

sale::~sale()
{
}

void sale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT2, employeeNo);
	DDX_Text(pDX, IDC_EDIT3, invoiceNo);
	DDX_Text(pDX, IDC_EDIT11, productNo);
	DDX_Text(pDX, IDC_EDIT12, num);
	DDX_Text(pDX, IDC_EDIT8, shouldPay);
	DDX_Text(pDX, IDC_EDIT10, truePay);
	DDX_Text(pDX, IDC_EDIT5, change);
	DDX_Text(pDX, IDC_EDIT7, discount);
	DDX_Text(pDX, IDC_EDIT9, memName);
	DDX_Text(pDX, IDC_EDIT4, memberNo);
	DDX_Text(pDX, IDC_EDIT6, memLevel);
	DDX_Text(pDX, IDC_EDIT13, allSum);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
}


BEGIN_MESSAGE_MAP(sale, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &sale::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &sale::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &sale::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &sale::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &sale::OnBnClickedButton4)
END_MESSAGE_MAP()


// sale 消息处理程序


BOOL sale::OnInitDialog()
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
	m_list.InsertColumn(7, _T("折扣%"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(8, _T("折扣后金额"), LVCFMT_CENTER, 75);

	//设置combobox选项
	m_combo.InsertString(0, _T("现金"));
	m_combo.InsertString(1, _T("支付宝"));
	m_combo.InsertString(2, _T("微信"));
	m_combo.InsertString(3, _T("信用卡"));
	m_combo.SetCurSel(0);

	//设置初始数据
	allSum = 0;
	discount = 100 ;
	invoiceNo = "0000000009";
	num = 1;
	UpdateData(FALSE);//数据更新至窗口

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//添加商品
void sale::OnBnClickedButton1()
{
	UpdateData(TRUE);//从窗口获取数据

	productDao pDao;
	product p;
	double sum,trueSum;
	CString cnum,cprice,cdiscount,csum,ctrueSum;
	p = pDao.getProduct(productNo);//获取商品信息

	//列表显示
	m_list.InsertItem(0, _T(""));
	m_list.SetItemText(0, 1, p.productNo);
	m_list.SetItemText(0, 2, p.proName);
	cnum.Format(_T("%7.2f"), num);
	m_list.SetItemText(0, 3, cnum);
	cprice.Format(_T("%7.2f"), p.price);
	m_list.SetItemText(0, 4, cprice);
	m_list.SetItemText(0, 5, p.unit);
	sum = p.price*num;//计算单项金额
	csum.Format(_T("%7.2f"), sum);
	m_list.SetItemText(0, 6, csum);
	cdiscount.Format(_T("%7.2f"), p.discount * 100);
	m_list.SetItemText(0, 7, cdiscount);
	trueSum = sum*p.discount;//计算折扣后金额
	ctrueSum.Format(_T("%7.2f"), trueSum);
	m_list.SetItemText(0, 8, ctrueSum);

	allSum += trueSum;	//计算总金额
	shouldPay = allSum*discount/100;	//计算应付金额

	itemNum++;//商品项数加一
	productNo = "";	num = 1;//清除输入框数据
	UpdateData(FALSE);//数据更新至窗口
}

//会员查询
void sale::OnBnClickedButton2()
{
	UpdateData(TRUE);//从窗口获取数据
	memberDao mDao;
	member m=mDao.getMember(memberNo);//获取会员信息
	memName = m.memName;
	memLevel = m.memLevel;
	discount = m.discount*100;
	shouldPay = allSum*discount/100;	//计算应付金额
	UpdateData(FALSE);//数据更新至窗口
}


void sale::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//从窗口获取数据
	change = truePay - shouldPay;
	UpdateData(FALSE);//数据更新至窗口
}

//提交订单
void sale::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//从窗口获取数据
	orderDao oDao;
	orderMaster om;
	orderDetail od;
	productDao pDao;

	//获取订单主表数据
	om.employeeNo = employeeNo;
	om.invoiceNo = invoiceNo;
	if (memberNo == "")//当顾客没有会员号时，设为普通用户
		om.memberNo = "100000";
	else
	    om.memberNo = memberNo;
	om.tolAmtReceive.Format(_T("%7.2f"), allSum);
	om.tolPaidAmt.Format(_T("%7.2f"), truePay);
	int nIndex = m_combo.GetCurSel();
	m_combo.GetLBText(nIndex, om.payWay);

	//获取当前时间
	CTime tm;
	tm = CTime::GetCurrentTime();
	om.orderDate = tm.Format(_T("%Y-%m-%d %X"));

	od.orderNo=oDao.addOrder(om);//提交订单细节
	CString cquantity;
	for (int i = 0; i < itemNum; i++) {
		od.productNo= m_list.GetItemText(i, 1);
		cquantity=m_list.GetItemText(i,3);
		od.quantity = _ttof(cquantity);
		oDao.addOrderDetail(od); //插入数据库
		pDao.sell(od.productNo, od.quantity);//库存售出
	}

	//发票号+1
	int ino = _ttoi(invoiceNo);
	ino++;
	CString cino;
	cino.Format(_T("%d"), ino);//int转Cstring
	invoiceNo.Format(_T("%08s"), cino);//数字前补0

	MessageBox(_T("收款完成！"));
	//清除表单数据
	m_list.DeleteAllItems();
	itemNum = 0;
	memberNo = ""; memLevel = ""; memName = ""; discount = 100;
	allSum = shouldPay = truePay = change = 0;
	UpdateData(FALSE);//数据更新至窗口
}

//取消订单
void sale::OnBnClickedButton4()
{
	m_list.DeleteAllItems();
	itemNum = 0;
	memberNo = ""; memLevel = ""; memName = ""; discount = 100;
	allSum = shouldPay = truePay = change = 0;
	UpdateData(FALSE);//数据更新至窗口
}
