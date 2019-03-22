
#include "stdafx.h"
#include "Supermarket.h"
#include "productManage.h"
#include "afxdialogex.h"
#include "productDao.h"


// productManage 对话框

IMPLEMENT_DYNAMIC(productManage, CDialogEx)

productManage::productManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRODUCTMANAGE, pParent)
	, productNo(_T(""))
	, proName(_T(""))
	, category(_T(""))
	, stockNum(0)
	, price(0)
	, unit(_T(""))
	, discount(0)
	, supplier(_T(""))
{

}

productManage::~productManage()
{
}

void productManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, productNo);
	DDX_Text(pDX, IDC_EDIT4, proName);
	DDX_Text(pDX, IDC_EDIT5, category);
	DDX_Text(pDX, IDC_EDIT6, stockNum);
	DDX_Text(pDX, IDC_EDIT7, price);
	DDX_Text(pDX, IDC_EDIT8, unit);
	DDX_Text(pDX, IDC_EDIT9, discount);
	DDX_Text(pDX, IDC_EDIT10, supplier);
}


BEGIN_MESSAGE_MAP(productManage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON6, &productManage::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &productManage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &productManage::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &productManage::OnBnClickedButton3)
END_MESSAGE_MAP()


// productManage 消息处理程序

//查询
void productManage::OnBnClickedButton6()
{
	UpdateData(TRUE);
	productDao pd;
	product p=pd.getProduct(productNo);
	proName = p.proName;
	price = p.price;
	stockNum = p.num;
	discount = p.discount;
	unit = p.unit;
	supplier = p.supplierNo;
	category = p.category;
	UpdateData(FALSE);
}

//添加
void productManage::OnBnClickedButton2()
{
	UpdateData(TRUE);
	productDao pd;
	product p;
	p.productNo = productNo;
	p.proName = proName;
	p.price = price;
	p.num= stockNum;
	p.discount = discount;
	p.unit = unit;
	p.supplierNo = supplier;
	p.category = category;
	if (pd.addProduct(p))
		MessageBox(_T("添加成功！"));
	UpdateData(FALSE);
}

//删除
void productManage::OnBnClickedButton4()
{
	UpdateData(TRUE);
	productDao pd;
	if (pd.deleteProduct(productNo))
		MessageBox(_T("删除成功！"));
	UpdateData(FALSE);
}


void productManage::OnBnClickedButton3()
{
	UpdateData(TRUE);
	productDao pd;
	product p;
	p.productNo = productNo;
	p.proName = proName;
	p.price = price;
	p.num = stockNum;
	p.discount = discount;
	p.unit = unit;
	p.supplierNo = supplier;
	p.category = category;
	if (pd.updateProduct(p))
		MessageBox(_T("修改成功！"));
	UpdateData(FALSE);
}
