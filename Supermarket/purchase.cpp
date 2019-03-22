// purchase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Supermarket.h"
#include "purchase.h"
#include "afxdialogex.h"
#include "productDao.h"
#include "purchaseDao.h"


// purchase �Ի���

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


// purchase ��Ϣ�������

BOOL purchase::OnInitDialog()
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

	//���ó�ʼ����
	UpdateData(FALSE);//���ݸ���������

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


//�����Ʒ
void purchase::OnBnClickedButton1()
{
	UpdateData(TRUE);//�Ӵ��ڻ�ȡ����

	productDao pDao;
	product p;
	double sum;
	CString cnum, cprice,csum;
	p = pDao.getProduct(productNo);//��ȡ��Ʒ��Ϣ

	//�б���ʾ
	m_list.InsertItem(0, _T(""));
	m_list.SetItemText(0, 1, p.productNo);
	m_list.SetItemText(0, 2, p.proName);
	cnum.Format(_T("%7.2f"), quantity);
	m_list.SetItemText(0, 3, cnum);
	cprice.Format(_T("%7.2f"), price);
	m_list.SetItemText(0, 4, cprice);
	m_list.SetItemText(0, 5, p.unit);
	sum = price*quantity;//���㵥����
	csum.Format(_T("%7.2f"), sum);
	m_list.SetItemText(0, 6, csum);
	Amount += sum;//�����ܽ��

	nItem++;//��Ʒ������һ
	productNo = "";	quantity = 0; price = 0;//������������
	UpdateData(FALSE);//���ݸ���������
}

void purchase::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//�Ӵ��ڻ�ȡ����
	purchaseMaster pm;
	purchaseDao purDao;
	productDao proDao;
	purchaseDetail pd;
	//��ȡ������������
	pm.employeeNo = employeeNo;
	pm.supplierNo = supplierNo;
	pm.purAmount.Format(_T("%7.2f"), Amount);
	//��ȡ��ǰʱ��
	CTime tm;
	tm = CTime::GetCurrentTime();
	pm.purDate = tm.Format(_T("%Y-%m-%d %X"));

	pd.purchaseNo = purDao.addPurchaseMaster(pm);//�ύ����ϸ��
	for (int i = 0; i < nItem; i++) {
		pd.productNo = m_list.GetItemText(i, 1);
		pd.purQuantity = m_list.GetItemText(i, 3);
		pd.purPrice = m_list.GetItemText(i, 4);
		purDao.addPurchaseDetail(pd); //�������ݿ�
		proDao.store(pd.productNo, _ttof(pd.purQuantity));
	}

	MessageBox(_T("�ɹ���ɣ�"));
	//�������
	m_list.DeleteAllItems();
	nItem = 0;
	Amount = 0;
	UpdateData(FALSE);//���ݸ���������
}

//ȡ������
void purchase::OnBnClickedButton3()
{
	//�������
	m_list.DeleteAllItems();
	nItem = 0;
	Amount = 0;
	UpdateData(FALSE);//���ݸ���������
}
