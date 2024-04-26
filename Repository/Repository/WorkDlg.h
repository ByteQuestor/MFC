#pragma once
#include "afxcmn.h"


// WorkDlg �Ի���

class WorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WorkDlg)

public:
	WorkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WorkDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CTreeCtrl m_tree;
	void AddFolderToTree(const CString& strFolderPath, HTREEITEM hParentItem);
private:
	CFont m_font;
	CStatic m_static;
public:
	virtual BOOL OnInitDialog();
};
