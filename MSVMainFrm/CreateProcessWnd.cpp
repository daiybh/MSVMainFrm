#include "stdafx.h"
#include "CreateProcessWnd.h"



CCreateProcessWnd::CCreateProcessWnd( void )
{
	m_bIsLoad= FALSE;
	m_bAttachWnd_created = FALSE;
	m_dwWidth = m_dwHeight = m_dwTop = m_dwLeft = 0;
	m_strExePath = _T("");
}


CCreateProcessWnd::~CCreateProcessWnd(void)
{
}

CCreateProcessWnd::CCreateProcess::EnumFunArg CCreateProcessWnd::CCreateProcess::CreateProcessEx( CString strExePath,CRect &rect )
{
	HWND  hExeWnd = NULL;
	STARTUPINFO sa = {0};
	sa.cb = sizeof(STARTUPINFO);
	sa.wShowWindow=SW_HIDE;
	sa.dwFlags=STARTF_USEPOSITION | STARTF_USESIZE;            //設置了窗口坐标位置，窗口大小标志位有效，但是进程

	int SleepTime = GetPrivateProfileInt(_T("t"),_T("t"),100,_T("c:\\t.ini"));

	PROCESS_INFORMATION pi = {0};
	if(CreateProcess(strExePath,NULL,NULL,NULL,\
		FALSE,CREATE_NEW_PROCESS_GROUP,NULL,NULL,&sa,&pi))
	{
		DWORD dwStartTime = GetTickCount();
		if(WaitForInputIdle(pi.hProcess,INFINITE) == 0)
		{
			DWORD waitTIme = GetTickCount()-dwStartTime;
			Sleep(SleepTime);
			CString strLog;
			strLog.Format(_T("wait---%s[%d,%d]"),strExePath,waitTIme,SleepTime);
			AddLog(strLog);
			//AfxMessageBox(strLog);
			hExeWnd = GetWndByPID(pi.dwProcessId);                //通過GetWindowThreadProcessId()对比 dwPid,能成功；但是返回的窗口句柄 （HWND)错误，用调试语句 ::SetWindowText(hWnd,_T("1111111"));無法設置窗口標題
			//CloseHandle(pi.hThread);
			//CloseHandle(pi.hProcess);
			if(sa.hStdInput)CloseHandle(sa.hStdInput);
			if(sa.hStdOutput)CloseHandle(sa.hStdOutput);
			if(sa.hStdError)CloseHandle(sa.hStdError);
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
	m_strExePath = lpExePath;
	CWnd *cWnd=CWnd::FromHandle(arg.hWnd);
	//隐藏标题栏

	cWnd->GetWindowText(strExeOrgTitle);
	CString strTitle;
	strTitle.Format(_T("[%d]%s"),arg.dwProcessId,strExeOrgTitle);
	::SetWindowText(hParentWnd,strTitle);

	CString strlog;
	strlog.Format(_T("createProcess[%s]---%x exeWnd=%x hParentWnd=%x"),lpExePath,GetDesktopWindow(),arg.hWnd,hParentWnd);
	AddLog(strlog);
	/*
	LONG lStyle = ::GetWindowLong(cWnd->m_hWnd,GWL_STYLE);
	lStyle &=~WS_POPUP;
	lStyle &=~WS_OVERLAPPED;
	lStyle |=WS_CHILD;
	::SetWindowLong(cWnd->m_hWnd,GWL_STYLE,lStyle);
/**/
	cWnd->ModifyStyle(WS_CAPTION,0);
	//隐藏边框
	cWnd->ModifyStyle(WS_THICKFRAME,1);
	//显示对话框
	::SetParent(cWnd->m_hWnd,hParentWnd);

	m_hParentWnd = hParentWnd;
	m_hExeWnd = arg.hWnd;
	m_dwProcessId = arg.dwProcessId;

	m_bIsLoad=TRUE;
	AdjustLayout(hParentWnd);
	m_bAttachWnd_created = TRUE;
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
		SetWindowPos(m_hExeWnd,HWND_BOTTOM, 0,0, m_exeRect.Width(), m_exeRect.Height(), SWP_NOACTIVATE);
		if(!m_bAttachWnd_created)
		{
			SetWindowPos(hParentWnd,HWND_BOTTOM, m_dwLeft,m_dwTop, m_exeRect.Width(), m_exeRect.Height()+10, 0);
		}

	}
 	GetWindowRect(hParentWnd,rect);
	m_dwWidth = rect.Width();
	m_dwHeight = rect.Height();
	CString ss;
	ss.Format(_T("bRectNull=%d DlgWndRect[%d,%d,%d,%d] exeRect[%d,%d,%d,%d] left=%d,top=%d"),
		bRectNull,
		rect.left,rect.top,rect.Width(),rect.Height(),
		m_exeRect.left,m_exeRect.top,m_exeRect.Width(),m_exeRect.Height(),
		m_dwLeft,m_dwTop);
	AddLog(ss);
}

CString CCreateProcessWnd::GetTitle()
{
	CString strTitle;
	strTitle.Format(_T("[%d]%s"),m_dwProcessId,strExeOrgTitle);
	return strTitle;
}
