
// RepositoryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "Repository.h"
#include "RepositoryDlg.h"
#include "afxdialogex.h"
#include "WorkDlg.h"
#include <fstream>
#include <string>
#include <atlstr.h> // ���� CString ��ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CRepositoryDlg �Ի���



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


// CRepositoryDlg ��Ϣ�������

BOOL CRepositoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	// ���ı��ļ�����ȡ����
	std::ifstream file("yourfile.txt"); // �滻 "yourfile.txt" Ϊ��� txt �ļ�·��
	if (file.is_open()) {
		CString content;
		std::string line;
		if (std::getline(file, line)) {
			content = CString(line.c_str()); // ����ȡ�������ݴ洢�� content ��
		}
		file.close();
		// ���ñ༭�ؼ����ı�����
		GetDlgItem(IDC_EDIT1)->SetWindowText(content);
	}
	else {
		// ����޷����ļ�������һ�����ļ�
		std::ofstream outfile("yourfile.txt"); // �滻 "yourfile.txt" Ϊ��� txt �ļ�·��
		if (outfile.is_open()) {
			outfile.close();
			// ���ñ༭�ؼ����ı�����Ϊ��
			GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		}
		else {
			// ����޷������ļ������������Ϣ
			MessageBox(_T("�޷������ļ�"));
		}
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRepositoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRepositoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRepositoryDlg::OnBnClickedOk()
{
	// ��ȡ Edit �ؼ����ı�����
	WorkDlg ToWork;
	GetDlgItemText(IDC_EDIT1, theApp.g_Name);
	// �� theApp.g_Name �� ANSI ��ʽ����д�� txt �ļ���
	std::ofstream outfile("yourfile.txt"); // �滻 "yourfile.txt" Ϊ��� txt �ļ�·��
	if (outfile.is_open()) {
		std::string strAnsiContent(CW2A(theApp.g_Name, CP_ACP)); // �� CString ת��Ϊ ANSI ����� std::string
		outfile << strAnsiContent; // ������д���ļ�
		// �����ļ��е�·��
		CString strFolderPath;
		strFolderPath.Format(L".\\%s", theApp.g_Name); // �ڵ�ǰĿ¼�´����ļ��У��ļ�������Ϊ Edit �ؼ����ı�����
		// �����ļ���
		if (!CreateDirectory(strFolderPath, NULL)) {
			// ����޷������ļ��У����������Ϣ
			DWORD dwError = GetLastError();
			if (dwError == ERROR_ALREADY_EXISTS) {
				MessageBox(_T("�ļ����Ѵ���"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(_T("�޷������ļ���"), _T("����"), MB_OK | MB_ICONERROR);
			}
		}
		else
		{
			MessageBox(_T("֪ʶ�ⴴ���ɹ���"), _T("�ɹ�"), MB_OK | MB_ICONINFORMATION);

		}
		ToWork.DoModal();
		outfile.close();
	}
	else {
		// ����޷����ļ������������Ϣ
		MessageBox(_T("�޷����ļ�"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	std::ifstream file("yourfile.txt"); // �滻 "yourfile.txt" Ϊ��� txt �ļ�·��
	if (file.is_open()) {
		std::string content;
		std::getline(file, content); // ��ȡһ������
		file.close();
		theApp.g_Name = CString(content.c_str()); // ����ȡ�������ݴ洢�� theApp.g_Name ��
	}
	else {
		// ����޷����ļ������������Ϣ
		MessageBox(_T("�޷����ļ�"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
}


void CRepositoryDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
}
