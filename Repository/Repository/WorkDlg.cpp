// WorkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Repository.h"
#include "WorkDlg.h"
#include "afxdialogex.h"
#include "Repository.h"

// WorkDlg �Ի���

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


// WorkDlg ��Ϣ�������


void WorkDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ������ؼ�
	m_tree.DeleteAllItems();

	// ��ȡ��ǰĿ¼
	TCHAR szCurrentDirectory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDirectory);

	// ��ӵ�ǰĿ¼�����µ��ļ��к��ļ������ؼ���
	HTREEITEM hRootItem = m_tree.InsertItem(szCurrentDirectory);
	AddFolderToTree(szCurrentDirectory, hRootItem);

	// չ�����ڵ�
	m_tree.Expand(hRootItem, TVE_EXPAND);
}



void WorkDlg::AddFolderToTree(const CString& strFolderPath, HTREEITEM hParentItem)
{
	// ���ļ���
	CString strSearchPath = strFolderPath + _T("\\*.*");
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(strSearchPath, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			CString strFileName = FindFileData.cFileName;

			// ������ļ��У���ݹ鴦��
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				strFileName != _T(".") && strFileName != _T(".."))
			{
				CString strSubFolderPath = strFolderPath + _T("\\") + strFileName;
				HTREEITEM hItem = m_tree.InsertItem(strFileName, hParentItem);
				AddFolderToTree(strSubFolderPath, hItem);
			}
			else
			{
				// ������ļ�������ӵ����ؼ���
				m_tree.InsertItem(strFileName, hParentItem);
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
}


BOOL WorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_static.SubclassDlgItem(IDC_STATIC, this);
	m_font.CreatePointFont(200, _T("����"));
	m_static.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
