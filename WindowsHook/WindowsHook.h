// WindowsHook.h : WindowsHook DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWindowsHookApp
// �йش���ʵ�ֵ���Ϣ������� WindowsHook.cpp
//

class CWindowsHookApp : public CWinApp
{
public:
	CWindowsHookApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
