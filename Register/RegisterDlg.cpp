
// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "SelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegisterDlg 对话框



CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序

BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 读取注册表
	/*
	HKEY key;
	char data[2];
	DWORD size = 2;
	DWORD type = REG_SZ;
	CString skey = "Software\\mingrisoft";
	
	long iret = RegOpenKeyEx(HKEY_CURRENT_USER, skey,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &key);*/
	// 打开成功
	/*
	if (iret == 0) {
		CString value;
		// 读取键值
		iret = RegQueryValueEx(key, "isreg", 0, &type, (BYTE *)data, &size);
		if (iret == 0) {
			if (data[0] == '0') {
				// 显示选择对话框 
				CSelectDlg dlg;
				if (dlg.DoModal() != IDOK) {
					// 退出
					OnCancel();
				}
				// 检查标志位
				if (!Flag) {
					// 退出
					OnCancel();
				}
			}
			else {
				return TRUE;
			}
		}
		else {
			RegSetValueEx(key, "isreg", 0, REG_SZ, (BYTE *)"0", 1);
			OnCancel();
		}
	}*/
	fstream file;
	string filename = "//reg.txt";
	file.open(filename,ios::in);
	if (!file)
	{
		CSelectDlg dlg;
		if (dlg.DoModal() != IDOK) {
			// 退出
			OnCancel();
		}
	}
	else
	{
		file.close();
		return TRUE;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRegisterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRegisterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

