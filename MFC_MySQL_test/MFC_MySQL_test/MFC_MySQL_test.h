
// MFC_MySQL_test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_MySQL_testApp:
// �йش����ʵ�֣������ MFC_MySQL_test.cpp
//

class CMFC_MySQL_testApp : public CWinApp
{
public:
	CMFC_MySQL_testApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_MySQL_testApp theApp;