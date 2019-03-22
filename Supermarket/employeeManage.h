#pragma once


// employeeManage 对话框

class employeeManage : public CDialogEx
{
	DECLARE_DYNAMIC(employeeManage)

public:
	employeeManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~employeeManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMPLOYEEMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton6();
	CString employeeNo;
	CString empName;
	CString password;
	CComboBox m_combo1;
	CComboBox m_combo2;
	float salary;
	CString telephone;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
