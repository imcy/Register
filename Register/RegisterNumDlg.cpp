// RegisterNumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "RegisterNumDlg.h"
#include "afxdialogex.h"
#include "SelectDlg.h"

// CRegisterNumDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterNumDlg, CDialogEx)

CRegisterNumDlg::CRegisterNumDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGNUM, pParent)
	, m_strRegisterCode(_T(""))
{

}

CRegisterNumDlg::~CRegisterNumDlg()
{
}

void CRegisterNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT3, m_strRegisterCode);
	DDX_Control(pDX, IDC_ADVANCE, m_Advance);
	DDX_Control(pDX, IDC_BACKOFF, m_Backoff);
}

void CRegisterNumDlg::OnPaint()
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
	}
	else
	{
		//添加代码对话框背景贴图  
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);                                 //获取对话框长宽         
		CDC   dcBmp;                                           //定义并创建一个内存设备环境  
		dcBmp.CreateCompatibleDC(&dc);                         //创建兼容性DC  
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);                 //载入资源中的IDB_BITMAP1图片  
		BITMAP   m_bitmap;                                     //图片变量                  
		bmpBackground.GetBitmap(&m_bitmap);                    //将图片载入位图中  
		CBitmap   *pbmpOld = dcBmp.SelectObject(&bmpBackground); //将位图选入临时内存设备环境    
																 //调用函数显示图片 StretchBlt显示形状可变  
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0,
			m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}


BEGIN_MESSAGE_MAP(CRegisterNumDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADVANCE, &CRegisterNumDlg::OnAdvance)
	ON_BN_CLICKED(IDC_BACKOFF, &CRegisterNumDlg::OnBackoff)
END_MESSAGE_MAP()


// CRegisterNumDlg 消息处理程序


BOOL CRegisterNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 注册按钮显示图片
	m_Advance.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_ADVANCE)));
	// 后退按钮显示图片
	m_Backoff.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPOFF)));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CRegisterNumDlg::OnAdvance()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 判断用户名和注册破是否输入了
	if (m_Name.IsEmpty() || m_strRegisterCode.IsEmpty()) {
		MessageBox("用户名或注册码错误！");
		return;
	}
}


void CRegisterNumDlg::OnBackoff()
{
	// 调用父类的OnOk()方法
	CDialog::OnOK();
	// 显示模态对话框:选择试用? or 注册
	CSelectDlg dlg;
	dlg.DoModal();
}
