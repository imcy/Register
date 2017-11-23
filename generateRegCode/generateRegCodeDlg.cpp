
// generateRegCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "generateRegCode.h"
#include "generateRegCodeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CgenerateRegCodeDlg 对话框



CgenerateRegCodeDlg::CgenerateRegCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GENERATEREGCODE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgenerateRegCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgenerateRegCodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CgenerateRegCodeDlg::OnOk)
END_MESSAGE_MAP()


// CgenerateRegCodeDlg 消息处理程序

BOOL CgenerateRegCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgenerateRegCodeDlg::OnPaint()
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
HCURSOR CgenerateRegCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CgenerateRegCodeDlg::GetCPUNum()
{
	//获取CPU序列号
	unsigned long s1, s2;

	CString CPUID1, CPUID2;
	__asm {
		mov eax, 01h // 传入功能号
		xor edx, edx // 清空结果,执行cpuid指令之后.结果会放在edx,eax中
		cpuid        // 执行指令,获取结果
		mov s1, edx  // 读取结果
		mov s2, eax  // 读取结果
	}

	CPUID1.Format("%08X%08X", s1, s2);
	__asm {
		mov eax, 03h // 传入功能号
		xor ecx, ecx // 清空结果,执行cpuid指令之后.结果会放在edx,eax中
		xor edx, edx // 同上
		cpuid        // 执行指令
		mov s1, edx  // 读取结果
		mov s2, ecx  // 读取结果
	}
	CPUID2.Format("%08X%08X", s1, s2);

	// 拼接结果
	CString CpuID = CPUID1 + CPUID2;
	return CpuID.Mid(5, 3); // 从拼接的结果中取出一段,作为返回结果

}

CString CgenerateRegCodeDlg::GetDiskNum()
{
	DWORD ser;
	char namebuf[128];
	char filebuf[128];
	//获取C盘的序列号
	::GetVolumeInformation("c:\\",   // 欲获取信息的磁盘的根路径
		namebuf,  // 用于装载磁盘名的缓冲区
		128,      // 上面缓冲区的大小
		&ser,     // 用于装载磁盘序列号的变量
		0,        // 用于装载文件名每一部分的长度
		0,        // 标志位
		filebuf,  // 用于装载文件系统的名称
		128       // 上面缓冲区的大小
	);
	CString DiskID;
	DiskID.Format("%08X", ser); 		// 格式化成字符串
	return DiskID.Mid(3, 3); 			// 返回第3个开始的3个字符
}

CString CgenerateRegCodeDlg::GetMacAddress()
{
	NCB nInfo;
	memset(&nInfo, 0, sizeof(NCB)); 					// 内容清零
	nInfo.ncb_command = NCBRESET; 					// 设置命令
	nInfo.ncb_lana_num = 0;
	Netbios(&nInfo); 									// 执行

	ADAPTER_INFO AdaINfo; //存储网卡信息
	memset(&nInfo, 0, sizeof(NCB)); 					//初始化NetBIOS
	nInfo.ncb_command = NCBASTAT;
	nInfo.ncb_lana_num = 0;
	nInfo.ncb_buffer = (unsigned char *)&AdaINfo;
	nInfo.ncb_length = sizeof(ADAPTER_INFO);
	strncpy((char *)nInfo.ncb_callname, "*", NCBNAMSZ);
	Netbios(&nInfo);

	CString MacAddr; 									// 格式化成字符串
	MacAddr.Format("%02X%02X%02X%02X%02X%02X",
		AdaINfo.nStatus.adapter_address[0],
		AdaINfo.nStatus.adapter_address[1],
		AdaINfo.nStatus.adapter_address[2],
		AdaINfo.nStatus.adapter_address[3],
		AdaINfo.nStatus.adapter_address[4],
		AdaINfo.nStatus.adapter_address[5]
	);
	return MacAddr.Mid(4, 4); 						// 返回一段字符串
}



void CgenerateRegCodeDlg::OnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;
	GetDlgItem(IDC_EDIT1)->GetWindowText(name);
	if (name.IsEmpty()) {
		MessageBox("用户名不能为空！");
		return;
	}
	//定义一个秘钥数组
	CString code[16] = {
		"ah", "tm", "ib", "nw", "rt", "vx", "zc", "gf",
		"pn", "xq", "fc", "oj", "wm", "eq", "np", "qw"
	};
	CString reg, stred;
	int num;
	stred = GetCPUNum() + GetDiskNum() + GetMacAddress();//拼接CPU,C盘和网卡
	stred.MakeLower();
	//根据十六进制数字从密钥数组中选择字符串
	for (int i = 0; i < 10; i++) {
		char p = stred.GetAt(i);				// 相当于 取第i个字符
		if (p >= 'a' && p <= 'f') {			// 如果字符为 abcdef
			num = p - 'a' + 10;				// - ‘a’ + 10 转化成数字值
		}
		else {
			num = p - '0';		// 如果是数字，则 – ‘0’ 转化为整数组
		}
		CString tmp = code[num];			// 取密钥数组中的一个元素	
		reg += tmp;					// 追加到字符串后面，最后形成注册码
	}

	// 结果转化成大写
	reg.MakeUpper();
	// 设置界面上编辑框的内容
	GetDlgItem(IDC_EDIT2)->SetWindowText(reg.Mid(0, 5));
	GetDlgItem(IDC_EDIT3)->SetWindowText(reg.Mid(5, 5));
	GetDlgItem(IDC_EDIT4)->SetWindowText(reg.Mid(10, 5));
	GetDlgItem(IDC_EDIT5)->SetWindowText(reg.Mid(15, 5));
	// 把结果写入注册表
	/*
	HKEY key;
	CString skey = "Software\\mingrisoft"; //如果没有子项就新建
	RegOpenKey(HKEY_CURRENT_USER, skey, &key);
	CString value = name + "-" + reg;
	int iret = RegSetValueEx(key, "regnum", 0, REG_SZ, (BYTE *)value.GetBuffer(0),
		value.GetLength());

	//只能写入REG_SZ型数据
	if (iret == ERROR_SUCCESS) {
		MessageBox("创建成功", "提示", MB_OK);
	}
	else {
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf,
			0,
			NULL
		);

		// Process any inserts in lpMsgBuf. 
		// ... 

		// Display the string. 
		MessageBox((LPCTSTR)lpMsgBuf);

		// Free the buffer. 
		LocalFree(lpMsgBuf);
	}
	RegSetValueEx(key, "isreg", 0, REG_SZ, (BYTE *)"0", 1);
	*/
	// 把注册号,写入"sn.txt"文件
	CFile file;
	char path[256];
	::GetCurrentDirectory(256, path);
	CString filename = path;
	filename += "\\sn.txt";
	file.Open(filename, CFile::modeCreate | CFile::modeWrite); // 使用读写模式打开文件
	CString text = name + "\r\n" + reg.Mid(0, 5) + "-" + reg.Mid(5, 5) +
		"-" + reg.Mid(10, 5) + "-" + reg.Mid(15, 5)+"\r\n"+"30";
	// 写入
	file.Write(text, text.GetLength());
	// 关闭文件
	file.Close();
}
