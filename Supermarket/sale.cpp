// sale.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Supermarket.h"
#include "sale.h"
#include "afxdialogex.h"
#include "productDao.h"
#include "memberDao.h"
#include "orderDao.h"
#include <time.h>

// sale �Ի���

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


// sale ��Ϣ�������


BOOL sale::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��ʼ���б�
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// �����в�����ÿһ�еĿ��
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, 75);
	m_list.InsertColumn(1, _T("��Ʒ���"), LVCFMT_CENTER, 75);  
	m_list.InsertColumn(2, _T("��Ʒ����"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(3, _T("����"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(4, _T("����"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(5, _T("������λ"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(6, _T("���"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(7, _T("�ۿ�%"), LVCFMT_CENTER, 75);
	m_list.InsertColumn(8, _T("�ۿۺ���"), LVCFMT_CENTER, 75);

	//����comboboxѡ��
	m_combo.InsertString(0, _T("�ֽ�"));
	m_combo.InsertString(1, _T("֧����"));
	m_combo.InsertString(2, _T("΢��"));
	m_combo.InsertString(3, _T("���ÿ�"));
	m_combo.SetCurSel(0);

	//���ó�ʼ����
	allSum = 0;
	discount = 100 ;
	invoiceNo = "0000000009";
	num = 1;
	UpdateData(FALSE);//���ݸ���������

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


//�����Ʒ
void sale::OnBnClickedButton1()
{
	UpdateData(TRUE);//�Ӵ��ڻ�ȡ����

	productDao pDao;
	product p;
	double sum,trueSum;
	CString cnum,cprice,cdiscount,csum,ctrueSum;
	p = pDao.getProduct(productNo);//��ȡ��Ʒ��Ϣ

	//�б���ʾ
	m_list.InsertItem(0, _T(""));
	m_list.SetItemText(0, 1, p.productNo);
	m_list.SetItemText(0, 2, p.proName);
	cnum.Format(_T("%7.2f"), num);
	m_list.SetItemText(0, 3, cnum);
	cprice.Format(_T("%7.2f"), p.price);
	m_list.SetItemText(0, 4, cprice);
	m_list.SetItemText(0, 5, p.unit);
	sum = p.price*num;//���㵥����
	csum.Format(_T("%7.2f"), sum);
	m_list.SetItemText(0, 6, csum);
	cdiscount.Format(_T("%7.2f"), p.discount * 100);
	m_list.SetItemText(0, 7, cdiscount);
	trueSum = sum*p.discount;//�����ۿۺ���
	ctrueSum.Format(_T("%7.2f"), trueSum);
	m_list.SetItemText(0, 8, ctrueSum);

	allSum += trueSum;	//�����ܽ��
	shouldPay = allSum*discount/100;	//����Ӧ�����

	itemNum++;//��Ʒ������һ
	productNo = "";	num = 1;//������������
	UpdateData(FALSE);//���ݸ���������
}

//��Ա��ѯ
void sale::OnBnClickedButton2()
{
	UpdateData(TRUE);//�Ӵ��ڻ�ȡ����
	memberDao mDao;
	member m=mDao.getMember(memberNo);//��ȡ��Ա��Ϣ
	memName = m.memName;
	memLevel = m.memLevel;
	discount = m.discount*100;
	shouldPay = allSum*discount/100;	//����Ӧ�����
	UpdateData(FALSE);//���ݸ���������
}


void sale::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//�Ӵ��ڻ�ȡ����
	change = truePay - shouldPay;
	UpdateData(FALSE);//���ݸ���������
}

//�ύ����
void sale::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//�Ӵ��ڻ�ȡ����
	orderDao oDao;
	orderMaster om;
	orderDetail od;
	productDao pDao;

	//��ȡ������������
	om.employeeNo = employeeNo;
	om.invoiceNo = invoiceNo;
	if (memberNo == "")//���˿�û�л�Ա��ʱ����Ϊ��ͨ�û�
		om.memberNo = "100000";
	else
	    om.memberNo = memberNo;
	om.tolAmtReceive.Format(_T("%7.2f"), allSum);
	om.tolPaidAmt.Format(_T("%7.2f"), truePay);
	int nIndex = m_combo.GetCurSel();
	m_combo.GetLBText(nIndex, om.payWay);

	//��ȡ��ǰʱ��
	CTime tm;
	tm = CTime::GetCurrentTime();
	om.orderDate = tm.Format(_T("%Y-%m-%d %X"));

	od.orderNo=oDao.addOrder(om);//�ύ����ϸ��
	CString cquantity;
	for (int i = 0; i < itemNum; i++) {
		od.productNo= m_list.GetItemText(i, 1);
		cquantity=m_list.GetItemText(i,3);
		od.quantity = _ttof(cquantity);
		oDao.addOrderDetail(od); //�������ݿ�
		pDao.sell(od.productNo, od.quantity);//����۳�
	}

	//��Ʊ��+1
	int ino = _ttoi(invoiceNo);
	ino++;
	CString cino;
	cino.Format(_T("%d"), ino);//intתCstring
	invoiceNo.Format(_T("%08s"), cino);//����ǰ��0

	MessageBox(_T("�տ���ɣ�"));
	//���������
	m_list.DeleteAllItems();
	itemNum = 0;
	memberNo = ""; memLevel = ""; memName = ""; discount = 100;
	allSum = shouldPay = truePay = change = 0;
	UpdateData(FALSE);//���ݸ���������
}

//ȡ������
void sale::OnBnClickedButton4()
{
	m_list.DeleteAllItems();
	itemNum = 0;
	memberNo = ""; memLevel = ""; memName = ""; discount = 100;
	allSum = shouldPay = truePay = change = 0;
	UpdateData(FALSE);//���ݸ���������
}
