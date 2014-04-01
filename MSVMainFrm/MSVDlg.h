#pragma once
#include "resource.h"

// CMSVDlg 对话框

class CCreateProcessWnd{
public:
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
};
class CMSVDlg : public CDialog,CCreateProcessWnd
{
	DECLARE_DYNAMIC(CMSVDlg)
public:
	void SetExePath(CString strExePath);
	BOOL StartWork();
	void AdjustLayout();
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
	HWND    m_hExeWnd;
	CRect   m_exeRect;
	BOOL    m_bIsLoad;
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
