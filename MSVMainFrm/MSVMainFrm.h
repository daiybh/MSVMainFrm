
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


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	void OnNew(){this->OnFileNew();};
	void OnOpen(){this->OnFileOpen();};

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMSVMainFrmApp theApp;
