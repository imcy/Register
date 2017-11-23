
// generateRegCodeDlg.h : 头文件
//

#pragma once
#include "nb30.h"
#pragma comment(lib,"netapi32.lib")

// CgenerateRegCodeDlg 对话框
class CgenerateRegCodeDlg : public CDialogEx
{
// 构造
public:
	CgenerateRegCodeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENERATEREGCODE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CString GetCPUNum();//获取CPU序列号从第五个字符起的3个字符
	CString GetDiskNum();//获取C盘序列号中从第三个字符起三个字符
	//网卡信息结构体
	struct ADAPTER_INFO
	{
		ADAPTER_STATUS nStatus;
		NAME_BUFFER nBuffer;
	};
	CString GetMacAddress();//获取网卡地址从第4个字符起的4个字符
public:
	afx_msg void OnOk();
};
