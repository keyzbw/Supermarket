// employeeManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Supermarket.h"
#include "employeeManage.h"
#include "afxdialogex.h"
#include "employeeDao.h"


// employeeManage �Ի���

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


// employeeManage ��Ϣ�������


BOOL employeeManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_combo1.InsertString(0, _T("��"));
	m_combo1.InsertString(1, _T("Ů"));
	m_combo2.InsertString(0, _T("����"));
	m_combo2.InsertString(1, _T("����Ա"));
	m_combo2.InsertString(2, _T("�ɹ�Ա"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//��ѯ
void employeeManage::OnBnClickedButton6()
{
	UpdateData(TRUE);
	employeeDao ed;
	employee e = ed.getEmployee(employeeNo);
	password = e.empPassword;
	empName = e.empName;
	salary = e.salary;
	telephone = e.telephone;
	if (e.sex == "��")
		m_combo1.SetCurSel(0);
	else if(e.sex=="Ů")
		m_combo1.SetCurSel(1);
	if(e.title=="����")
		m_combo2.SetCurSel(0);
	else if (e.title == "����Ա")
		m_combo2.SetCurSel(1);	
	else if (e.title == "�ɹ�Ա")
		m_combo2.SetCurSel(2);
	UpdateData(FALSE);
}

//���
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
		MessageBox(_T("��ӳɹ�"));
	UpdateData(FALSE);
}

//ɾ��
void employeeManage::OnBnClickedButton4()
{
	UpdateData(TRUE);
	employeeDao ed;
	if (ed.deleteEmployee(employeeNo))
		MessageBox(_T("ɾ���ɹ�"));
	UpdateData(FALSE);
}

//�޸�
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
		MessageBox(_T("�޸ĳɹ�"));
	UpdateData(FALSE);
}
