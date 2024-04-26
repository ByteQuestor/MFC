// WorkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Repository.h"
#include "WorkDlg.h"
#include "afxdialogex.h"
#include "Repository.h"

// WorkDlg 对话框

IMPLEMENT_DYNAMIC(WorkDlg, CDialogEx)

WorkDlg::WorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WorkDlg::IDD, pParent)
{

}

WorkDlg::~WorkDlg()
{
}

void WorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(WorkDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &WorkDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// WorkDlg 消息处理程序


void WorkDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	// 清空树控件
	m_tree.DeleteAllItems();

	// 获取当前目录
	TCHAR szCurrentDirectory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDirectory);

	// 添加当前目录及其下的文件夹和文件到树控件中
	HTREEITEM hRootItem = m_tree.InsertItem(szCurrentDirectory);
	AddFolderToTree(szCurrentDirectory, hRootItem);

	// 展开根节点
	m_tree.Expand(hRootItem, TVE_EXPAND);
}



void WorkDlg::AddFolderToTree(const CString& strFolderPath, HTREEITEM hParentItem)
{
	// 打开文件夹
	CString strSearchPath = strFolderPath + _T("\\*.*");
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(strSearchPath, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			CString strFileName = FindFileData.cFileName;

			// 如果是文件夹，则递归处理
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				strFileName != _T(".") && strFileName != _T(".."))
			{
				CString strSubFolderPath = strFolderPath + _T("\\") + strFileName;
				HTREEITEM hItem = m_tree.InsertItem(strFileName, hParentItem);
				AddFolderToTree(strSubFolderPath, hItem);
			}
			else
			{
				// 如果是文件，则添加到树控件中
				m_tree.InsertItem(strFileName, hParentItem);
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
}


BOOL WorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_static.SubclassDlgItem(IDC_STATIC, this);
	m_font.CreatePointFont(200, _T("楷体"));
	m_static.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
