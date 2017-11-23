// SelectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "SelectDlg.h"
#include "afxdialogex.h"
#include "RegisterNumDlg.h"

// CSelectDlg 对话框

IMPLEMENT_DYNAMIC(CSelectDlg, CDialogEx)

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECT, pParent)
	, m_Radio(0)
{

}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_RADIO1, m_Radio);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
}

void CSelectDlg::OnPaint()
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

		/******************************************************/
		/** StretchBlt()                                     **/
		/** 参数x、y位图目标矩形左上角x、y的坐标值 居中      **/
		/** nWidth、nHeigth位图目标矩形的逻辑宽度和高度      **/
		/** pSrcDC表示源设备CDC指针                          **/
		/** xSrc、ySrc表示位图源矩形的左上角的x、y逻辑坐标值 **/
		/** dwRop表示显示位图的光栅操作方式                  **/
		/** SRCCOPY用于直接将位图复制到目标环境中            **/
		/******************************************************/
	}
}



BEGIN_MESSAGE_MAP(CSelectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CSelectDlg::OnOk)
END_MESSAGE_MAP()


// CSelectDlg 消息处理程序


BOOL CSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 读取注册表
	HKEY key;
	char data[4];
	DWORD size = 4;
	DWORD type = REG_SZ;
	string filename = "F://c++//generateRegCode//generateRegCode//sn.txt";
	ifstream in(filename);//打开文件。
	int i;
	string str;
	for (i = 0; i< 3; i++)
		getline(in,str, '\n');//读取数据。

	int count = atoi(str.c_str());
	if (count != 0) {
		CString strTime;
		// 在界面上显示试用次数
		strTime.Format("你还可以使用%d次",count);
		GetDlgItem(IDC_STATICTIME)->SetWindowText(strTime);
	}
	else {
		// 界面上的控件设置为不可用
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		// 提示不可以试用软件
		GetDlgItem(IDC_STATICTIME)->SetWindowText("你已经不可以再试用本软件了！");
	}
	/*
	CString skey = "Software\\mingrisoft";
	LSTATUS iret = RegOpenKeyEx(HKEY_CURRENT_USER, skey,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &key);
	if (iret == 0) {
		CString value;
		// 读取试用次数
		iret = RegQueryValueEx(key, "tryout", 0, &type, (BYTE *)data, &size);
		if (iret == 0) {
			if (data != 0) {
				CString strTime;
				// 在界面上显示试用次数
				strTime.Format("你还可以使用%s次", data);
				GetDlgItem(IDC_STATICTIME)->SetWindowText(strTime);
			}
			else {
				// 界面上的控件设置为不可用
				GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
				// 提示不可以试用软件
				GetDlgItem(IDC_STATICTIME)->SetWindowText("你已经不可以再试用本软件了！");
			}
		}
		else {
			// 设置试用次数为30
			RegSetValueEx(key, "tryout", 0, REG_SZ, (BYTE *)"30", 2);
			OnCancel();
		}
	}
	*/
	// 设置"ok"按钮的图片
	m_OK.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPOK)));
	// 设置"cancel"按钮的图片
	m_Cancel.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPOFF)));
	m_Radio = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CSelectDlg::OnOk()
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	// 选择了"注册"
	if (m_Radio == 0) {
		CDialog::OnOK();
		CRegisterNumDlg dlg;
		dlg.DoModal();
	}
	// 选择了"试用"
	else if (m_Radio == 1) {
		// 打开注册表中 关于试用次数的键值,准备写入
		HKEY key;
		CString skey = "Software\\mingrisoft";
		long iret = RegOpenKeyEx(HKEY_CURRENT_USER,
			skey,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			&key);
		if (iret == 0) {
			// 从界面上获得试用次数相关文字
			CString str;
			GetDlgItem(IDC_STATICTIME)->GetWindowText(str);
			CString num;
			// 次试用次数转换为整型数字
			int run = atoi(str.Mid(12, str.GetLength() - 14));
			num.Format("%d", run - 1);
			// 写入注册表
			RegSetValueEx(key, "tryout", 0, REG_SZ, (BYTE *)num.GetBuffer(0)
				, num.GetLength());
			// 设置全局标志位
			//Flag = TRUE;
			CDialog::OnOK();
		}
	}
}
