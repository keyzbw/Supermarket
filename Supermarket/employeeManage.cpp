// employeeManage.cpp : 实现文件
//

#include "stdafx.h"
#include "Supermarket.h"
#include "employeeManage.h"
#include "afxdialogex.h"
#include "employeeDao.h"


// employeeManage 对话框

IMPLEMENT_DYNAMIC(employeeManage, CDialogEx)

employeeManage::employeeManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EMPLOYEEMANAGE, pParent)
	, employeeNo(_T(""))
	, empName(_T(""))
	, password(_T(""))
	, salary(0)
	, telephone(_T(""))
{

}

employeeManage::~employeeManage()
{
}

void employeeManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, employeeNo);
	DDX_Text(pDX, IDC_EDIT4, empName);
	DDX_Text(pDX, IDC_EDIT5, password);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Text(pDX, IDC_EDIT8, salary);
	DDX_Text(pDX, IDC_EDIT9, telephone);
}


BEGIN_MESSAGE_MAP(employeeManage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON6, &employeeManage::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &employeeManage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &employeeManage::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &employeeManage::OnBnClickedButton3)
END_MESSAGE_MAP()


// employeeManage 消息处理程序


BOOL employeeManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_combo1.InsertString(0, _T("男"));
	m_combo1.InsertString(1, _T("女"));
	m_combo2.InsertString(0, _T("经理"));
	m_combo2.InsertString(1, _T("收银员"));
	m_combo2.InsertString(2, _T("采购员"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//查询
void employeeManage::OnBnClickedButton6()
{
	UpdateData(TRUE);
	employeeDao ed;
	employee e = ed.getEmployee(employeeNo);
	password = e.empPassword;
	empName = e.empName;
	salary = e.salary;
	telephone = e.telephone;
	if (e.sex == "男")
		m_combo1.SetCurSel(0);
	else if(e.sex=="女")
		m_combo1.SetCurSel(1);
	if(e.title=="经理")
		m_combo2.SetCurSel(0);
	else if (e.title == "收银员")
		m_combo2.SetCurSel(1);	
	else if (e.title == "采购员")
		m_combo2.SetCurSel(2);
	UpdateData(FALSE);
}

//添加
void employeeManage::OnBnClickedButton2()
{
	UpdateData(TRUE);
	employeeDao ed;
	employee e;
	e.employeeNo = employeeNo;
	e.empPassword = password;
	e.empName = empName;
	e.salary = salary;
	e.telephone = telephone;
	int nIndex;
	nIndex = m_combo1.GetCurSel();
	m_combo1.GetLBText(nIndex, e.sex);
	nIndex = m_combo2.GetCurSel();
	m_combo2.GetLBText(nIndex, e.title);
	if (ed.addEmployee(e))
		MessageBox(_T("添加成功"));
	UpdateData(FALSE);
}

//删除
void employeeManage::OnBnClickedButton4()
{
	UpdateData(TRUE);
	employeeDao ed;
	if (ed.deleteEmployee(employeeNo))
		MessageBox(_T("删除成功"));
	UpdateData(FALSE);
}

//修改
void employeeManage::OnBnClickedButton3()
{
	UpdateData(TRUE);
	employeeDao ed;
	employee e;
	e.employeeNo = employeeNo;
	e.empPassword = password;
	e.empName = empName;
	e.salary = salary;
	e.telephone = telephone;
	int nIndex;
	nIndex = m_combo1.GetCurSel();
	m_combo1.GetLBText(nIndex, e.sex);
	nIndex = m_combo2.GetCurSel();
	m_combo2.GetLBText(nIndex, e.title);
	if (ed.updateEmployee(e))
		MessageBox(_T("修改成功"));
	UpdateData(FALSE);
}
