
// RepositoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "Repository.h"
#include "RepositoryDlg.h"
#include "afxdialogex.h"
#include "WorkDlg.h"
#include <fstream>
#include <string>
#include <atlstr.h> // 包含 CString 的头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRepositoryDlg 对话框



CRepositoryDlg::CRepositoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRepositoryDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRepositoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRepositoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRepositoryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CRepositoryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CRepositoryDlg 消息处理程序

BOOL CRepositoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	// 打开文本文件并读取内容
	std::ifstream file("yourfile.txt"); // 替换 "yourfile.txt" 为你的 txt 文件路径
	if (file.is_open()) {
		CString content;
		std::string line;
		if (std::getline(file, line)) {
			content = CString(line.c_str()); // 将读取到的内容存储到 content 中
		}
		file.close();
		// 设置编辑控件的文本内容
		GetDlgItem(IDC_EDIT1)->SetWindowText(content);
	}
	else {
		// 如果无法打开文件，创建一个空文件
		std::ofstream outfile("yourfile.txt"); // 替换 "yourfile.txt" 为你的 txt 文件路径
		if (outfile.is_open()) {
			outfile.close();
			// 设置编辑控件的文本内容为空
			GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		}
		else {
			// 如果无法创建文件，输出错误信息
			MessageBox(_T("无法创建文件"));
		}
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRepositoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRepositoryDlg::OnPaint()
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
HCURSOR CRepositoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRepositoryDlg::OnBnClickedOk()
{
	// 获取 Edit 控件的文本内容
	WorkDlg ToWork;
	GetDlgItemText(IDC_EDIT1, theApp.g_Name);
	// 将 theApp.g_Name 以 ANSI 格式重新写入 txt 文件中
	std::ofstream outfile("yourfile.txt"); // 替换 "yourfile.txt" 为你的 txt 文件路径
	if (outfile.is_open()) {
		std::string strAnsiContent(CW2A(theApp.g_Name, CP_ACP)); // 将 CString 转换为 ANSI 编码的 std::string
		outfile << strAnsiContent; // 将内容写入文件
		// 创建文件夹的路径
		CString strFolderPath;
		strFolderPath.Format(L".\\%s", theApp.g_Name); // 在当前目录下创建文件夹，文件夹名称为 Edit 控件的文本内容
		// 创建文件夹
		if (!CreateDirectory(strFolderPath, NULL)) {
			// 如果无法创建文件夹，输出错误信息
			DWORD dwError = GetLastError();
			if (dwError == ERROR_ALREADY_EXISTS) {
				MessageBox(_T("文件夹已存在"), _T("提示"), MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(_T("无法创建文件夹"), _T("错误"), MB_OK | MB_ICONERROR);
			}
		}
		else
		{
			MessageBox(_T("知识库创建成功！"), _T("成功"), MB_OK | MB_ICONINFORMATION);

		}
		ToWork.DoModal();
		outfile.close();
	}
	else {
		// 如果无法打开文件，输出错误信息
		MessageBox(_T("无法打开文件"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	std::ifstream file("yourfile.txt"); // 替换 "yourfile.txt" 为你的 txt 文件路径
	if (file.is_open()) {
		std::string content;
		std::getline(file, content); // 读取一行内容
		file.close();
		theApp.g_Name = CString(content.c_str()); // 将读取到的内容存储到 theApp.g_Name 中
	}
	else {
		// 如果无法打开文件，输出错误信息
		MessageBox(_T("无法打开文件"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
}


void CRepositoryDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
}
