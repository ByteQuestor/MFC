
// Repository.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRepositoryApp: 
// �йش����ʵ�֣������ Repository.cpp
//

class CRepositoryApp : public CWinApp
{
public:
	CRepositoryApp();
// ��д
public:
	virtual BOOL InitInstance();
	CString g_Name;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRepositoryApp theApp;