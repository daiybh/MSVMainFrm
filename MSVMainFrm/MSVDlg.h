#pragma once
#include "resource.h"

// CMSVDlg 对话框

class CCreateProcessWnd{
public:
	CCreateProcessWnd(){
		m_bIsLoad= FALSE;
	}
	HWND CreateProcessEx(CString strExePath,CRect &rect)
	{
		HWND  hExeWnd = NULL;
		STARTUPINFO sa = {0};
		sa.cb = sizeof(STARTUPINFO);
		sa.dwX= rect.left;
		sa.dwY= rect.top;
		sa.dwXSize=rect.Width();
		sa.dwYSize=rect.Height();
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
		return hExeWnd;
	}

	typedef struct EnumFunArg{
		HWND hWnd;
		DWORD dwProcessId;
	};
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

	BOOL AttachExeToWnd(LPCTSTR lpExePath,HWND hParentWnd)
	{
		if(m_bIsLoad)
		{
			ShowWindow(m_hParentWnd,SW_SHOW);
			return TRUE;
		}
		CRect rect;
		GetClientRect(hParentWnd,rect);
		m_hExeWnd=CreateProcessEx(lpExePath,rect);

		if(m_hExeWnd == NULL)
		{
			return FALSE;
		}
		CWnd *cWnd=CWnd::FromHandle(m_hExeWnd);
		//隐藏标题栏
		cWnd->ModifyStyle(WS_CAPTION,0);
		//隐藏边框
		cWnd->ModifyStyle(WS_THICKFRAME,1);
		//MoveWindow(m_exeRect.left,m_exeRect.top,m_exeRect.Width(),m_exeRect.Height());
		//显示对话框
		::SetParent(m_hExeWnd,hParentWnd);
		m_bIsLoad=TRUE;
		m_hParentWnd = hParentWnd;
		AdjustLayout();
		return TRUE;
	}
	void AdjustLayout()
	{
		if(!m_bIsLoad)
			return;
		CRect rect;
		GetClientRect(m_hParentWnd,rect);
		CWnd *cWnd=CWnd::FromHandle(m_hExeWnd);
		CRect m_exeRect;
		cWnd->GetClientRect(m_exeRect);
		if(m_exeRect.IsRectNull())
			cWnd->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), 0);
		else
		{
			SetWindowPos(m_hParentWnd,NULL, m_exeRect.left, m_exeRect.top, m_exeRect.Width()+1, m_exeRect.Height()+10, 0);
		}
	}
	HWND    m_hExeWnd;
	HWND	m_hParentWnd;
	BOOL    m_bIsLoad;
};
class CMSVDlg : public CDialog,CCreateProcessWnd
{
	DECLARE_DYNAMIC(CMSVDlg)
public:
	void SetExePath(CString strExePath);
	BOOL StartWork();
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
