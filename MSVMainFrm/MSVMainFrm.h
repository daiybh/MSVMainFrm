
// MSVMainFrm.h : MSVMainFrm 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMSVMainFrmApp:
// 有关此类的实现，请参阅 MSVMainFrm.cpp
//

class CMSVMainFrmApp : public CWinAppEx
{
public:
	CMSVMainFrmApp();

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// 重写
public:
	virtual BOOL InitInstance();

// 实现

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
