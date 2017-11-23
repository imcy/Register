#pragma once
#include "afxwin.h"


// CRegisterNumDlg 对话框

class CRegisterNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterNumDlg)

public:
	CRegisterNumDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegisterNumDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGNUM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_Name;
	afx_msg void OnAdvance();
	afx_msg void OnBackoff();
	CString m_strRegisterCode;
	CButton m_Advance;
	CButton m_Backoff;
};
