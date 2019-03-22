#pragma once


// productManage 对话框

class productManage : public CDialogEx
{
	DECLARE_DYNAMIC(productManage)

public:
	productManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~productManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRODUCTMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton6();
	CString productNo;
	CString proName;
	CString category;
	float stockNum;
	float price;
	CString unit;
	float discount;
	CString supplier;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
