#pragma once
#include "resource.h"

// CMSVDlg 对话框

class CCreateProcessWnd{
public:
	CCreateProcessWnd(){
		m_bIsLoad= FALSE;
	}
	typedef struct EnumFunArg{
		HWND hWnd;
		DWORD dwProcessId;
	};
	EnumFunArg CreateProcessEx(CString strExePath,CRect &rect)
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

	static BOOL CALLBACK lpEnumFunc(HWND hwnd,LPARAM lParam)
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
	HWND GetWndByPID(DWORD dwProcessID)  
	{  
		EnumFunArg arg;
		arg.dwProcessId = dwProcessID;
		arg.hWnd =0;
		EnumWindows(&CCreateProcessWnd::lpEnumFunc,reinterpret_cast<LPARAM>(&arg));
		return arg.hWnd;		
	}  
	BOOL AttachExeToWnd(LPCTSTR lpExePath,HWND hParentWnd,BOOL bAlwaysCreateProcess)
	{
	return 	AttachExeToWnd(lpExePath,hParentWnd,NULL,bAlwaysCreateProcess);
	}
	BOOL AttachExeToWnd(LPCTSTR lpExePath,HWND hParentWnd,HWND hDlgWnd,BOOL bAlwaysCreateProcess)
	{
		if(m_bIsLoad && !bAlwaysCreateProcess)
		{
			ShowWindow(m_hParentWnd,SW_SHOW);
			return TRUE;
		}
		m_hExeWnd =NULL;
		CRect rect;
		GetClientRect(hParentWnd,rect);
		EnumFunArg arg=CreateProcessEx(lpExePath,rect);

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
		
		::SetWindowText((hDlgWnd==NULL)?hParentWnd:hDlgWnd,strTitle);
		cWnd->ModifyStyle(WS_CAPTION,0);
		//隐藏边框
		cWnd->ModifyStyle(WS_THICKFRAME,1);
		//MoveWindow(m_exeRect.left,m_exeRect.top,m_exeRect.Width(),m_exeRect.Height());
		//显示对话框
		::SetParent(arg.hWnd,hParentWnd);
		
		m_hParentWnd = hParentWnd;
		m_hExeWnd = arg.hWnd;
		m_dwProcessId = arg.dwProcessId;
		if(!m_bIsLoad)
		{
			m_bIsLoad=TRUE;
			AdjustLayout(hParentWnd,hDlgWnd);
		}
		
		return TRUE;
	}
	void AdjustLayout()
	{
		AdjustLayout(m_hParentWnd,NULL);
	}
	void AdjustLayout(HWND hParentWnd,HWND hDlgWnd)
	{
		if(!m_bIsLoad)
			return;
		CRect rect;
		GetClientRect(hDlgWnd?hDlgWnd:hParentWnd,rect);

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
			SetWindowPos(hParentWnd,NULL, m_exeRect.left, m_exeRect.top, m_exeRect.Width()+10, m_exeRect.Height()+15, 0);
		}
		if(hDlgWnd&& hDlgWnd!=hParentWnd){
			SetWindowPos(hDlgWnd,NULL, m_exeRect.left, m_exeRect.top, m_exeRect.Width()+10, m_exeRect.Height()+10, 0);
		}
// 		CRect rect2;
// 		GetClientRect(hParentWnd,rect2);

// 		CString ss;
// 		ss.Format(_T("bRectNull=%d DlgWndRect[%d,%d,%d,%d][%d,%d,%d,%d] exeRect[%d,%d,%d,%d]"),
// 			bRectNull,
// 			rect.left,rect.top,rect.Width(),rect.Height(),
// 			rect2.left,rect2.top,rect2.Width(),rect2.Height(),
// 			m_exeRect.left,m_exeRect.top,m_exeRect.Width(),m_exeRect.Height());
// 		AfxGetMainWnd()->SendMessage( WM_USER+102,0x9898,(LPARAM)(LPCTSTR)ss);


	}
	HWND    m_hExeWnd;
	DWORD m_dwProcessId;
	HWND	m_hParentWnd;
	BOOL    m_bIsLoad;
	public:
	CString strTitle;
};
class CMSVDlg : public CDialog,public CCreateProcessWnd
{
	DECLARE_DYNAMIC(CMSVDlg)
public:
	BOOL StartWork(LPCTSTR lpStrExePath,BOOL bAlwaysCreateProcess=FALSE);
protected:
public:
	CMSVDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMSVDlg();

// 对话框数据
	enum { IDD = IDD_MSVDLG };
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_strExePath;
	CRect   m_exeRect;
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
