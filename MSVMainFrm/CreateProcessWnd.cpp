#include "stdafx.h"
#include "CreateProcessWnd.h"



CCreateProcessWnd::CCreateProcessWnd( void )
{
	m_bIsLoad= FALSE;
}


CCreateProcessWnd::~CCreateProcessWnd(void)
{
}

CCreateProcessWnd::CCreateProcess::EnumFunArg CCreateProcessWnd::CCreateProcess::CreateProcessEx( CString strExePath,CRect &rect )
{
	HWND  hExeWnd = NULL;
	STARTUPINFO sa = {0};
	sa.cb = sizeof(STARTUPINFO);
	/*
	sa.dwX= rect.left;
	sa.dwY= rect.top;
	sa.dwXSize=rect.Width();
	sa.dwYSize=rect.Height();
	/**/
	sa.wShowWindow=SW_HIDE;
	sa.dwFlags=STARTF_USEPOSITION | STARTF_USESIZE;            //設置了窗口坐标位置，窗口大小标志位有效，但是进程


	PROCESS_INFORMATION pi = {0};
	if(CreateProcess(strExePath,NULL,NULL,NULL,\
		FALSE,CREATE_NEW_PROCESS_GROUP,NULL,NULL,&sa,&pi))
	{
		if(WaitForInputIdle(pi.hProcess,INFINITE) == 0)
		{
			hExeWnd = GetWndByPID(pi.dwProcessId);                //通過GetWindowThreadProcessId()对比 dwPid,能成功；但是返回的窗口句柄 （HWND)错误，用调试语句 ::SetWindowText(hWnd,_T("1111111"));無法設置窗口標題
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);                                     
		}
	}
	EnumFunArg arg;
	arg.dwProcessId = pi.dwProcessId;
	arg.hWnd = hExeWnd;
	return arg;
}

BOOL CALLBACK CCreateProcessWnd::CCreateProcess::lpEnumFunc( HWND hwnd,LPARAM lParam )
{
	EnumFunArg * pArg =reinterpret_cast<EnumFunArg*> (lParam);
	DWORD dwProcessId;
	GetWindowThreadProcessId(hwnd,&dwProcessId);
	if(dwProcessId == pArg->dwProcessId){
		pArg->hWnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

HWND CCreateProcessWnd::CCreateProcess::GetWndByPID( DWORD dwProcessID )
{
	EnumFunArg arg;
	arg.dwProcessId = dwProcessID;
	arg.hWnd =0;
	EnumWindows(&CCreateProcessWnd::CCreateProcess::lpEnumFunc,reinterpret_cast<LPARAM>(&arg));
	return arg.hWnd;
}

BOOL CCreateProcessWnd::AttachExeToWnd( LPCTSTR lpExePath,HWND hParentWnd,BOOL bAlwaysCreateProcess )
{
	if(m_bIsLoad && !bAlwaysCreateProcess)
	{
		ShowWindow(m_hParentWnd,SW_SHOW);
		ShowWindow(m_hExeWnd,SW_SHOW);
		return TRUE;
	}
	m_hExeWnd =NULL;
	CRect rect;
	GetClientRect(hParentWnd,rect);
	CCreateProcessWnd::CCreateProcess::EnumFunArg arg=m_CreateProcess.CreateProcessEx(lpExePath,rect);

	if(arg.hWnd == NULL)
	{
		return FALSE;
	}
	CWnd *cWnd=CWnd::FromHandle(arg.hWnd);
	//隐藏标题栏
	CString strTemp;

	cWnd->GetWindowText(strTemp);
	strTitle.Format(_T("[%d]%s"),arg.dwProcessId,strTemp);
	::SetWindowText(hParentWnd,_T(""));

	::SetWindowText(hParentWnd,strTitle);

	cWnd->ModifyStyle(WS_CAPTION,0);
	//隐藏边框
	//	cWnd->ModifyStyle(WS_THICKFRAME,1);
	//MoveWindow(m_exeRect.left,m_exeRect.top,m_exeRect.Width(),m_exeRect.Height());
	//显示对话框
	::SetParent(arg.hWnd,hParentWnd);

	m_hParentWnd = hParentWnd;
	m_hExeWnd = arg.hWnd;
	m_dwProcessId = arg.dwProcessId;


	if(!m_bIsLoad)
	{
		m_bIsLoad=TRUE;
		AdjustLayout(hParentWnd);
	}

	return TRUE;
}

void CCreateProcessWnd::AdjustLayout( HWND hParentWnd )
{
	if(!m_bIsLoad)
		return;
	CRect rect;
	GetClientRect(hParentWnd,rect);

	CWnd *cWnd=CWnd::FromHandle(m_hExeWnd);
	CRect m_exeRect;
	cWnd->GetClientRect(m_exeRect);
	BOOL bRectNull=FALSE;
	if(m_exeRect.IsRectNull())
	{
		bRectNull = TRUE;
		cWnd->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), 0);
	}
	else
	{
		//			SetWindowPos(hParentWnd,NULL, m_exeRect.left+5, m_exeRect.top+5, m_exeRect.Width()+1-5, m_exeRect.Height()+10-5, 0);
		SetWindowPos(hParentWnd,NULL, 0,0, m_exeRect.Width()+10, m_exeRect.Height()+15, 0);
		SetWindowPos(m_hExeWnd,NULL, 0,0, m_exeRect.Width(), m_exeRect.Height(), 0);

	}
	CRect rect2;
	GetClientRect(hParentWnd,rect2);

	CString ss;
	ss.Format(_T("bRectNull=%d DlgWndRect[%d,%d,%d,%d][%d,%d,%d,%d] exeRect[%d,%d,%d,%d]"),
		bRectNull,
		rect.left,rect.top,rect.Width(),rect.Height(),
		rect2.left,rect2.top,rect2.Width(),rect2.Height(),
		m_exeRect.left,m_exeRect.top,m_exeRect.Width(),m_exeRect.Height());
	AfxGetMainWnd()->SendMessage( WM_USER+102,0x9898,(LPARAM)(LPCTSTR)ss);
}
