
// MSVMainFrm.h : MSVMainFrm Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMSVMainFrmApp:
// �йش����ʵ�֣������ MSVMainFrm.cpp
//

class CMSVMainFrmApp : public CWinAppEx
{
public:
	CMSVMainFrmApp();

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnFileNewFrame();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CMSVMainFrmApp theApp;
