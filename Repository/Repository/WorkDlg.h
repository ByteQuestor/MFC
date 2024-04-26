#pragma once
#include "afxcmn.h"


// WorkDlg 对话框

class WorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WorkDlg)

public:
	WorkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WorkDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
