#pragma once
class CCreateProcessWnd
{
public:
	CCreateProcessWnd(void);
	~CCreateProcessWnd(void);
	virtual BOOL AttachExeToWnd(LPCTSTR lpExePath,HWND hParentWnd,BOOL bAlwaysCreateProcess);
	void AdjustLayout()
	{
		AdjustLayout(m_hParentWnd);
	}
	//////////////////////////////////////////////////////////////////////////
	class CCreateProcess{
	public:
		typedef struct EnumFunArg{
			HWND hWnd;
			DWORD dwProcessId;
		};
		EnumFunArg CreateProcessEx(CString strExePath,CRect &rect);

		static BOOL CALLBACK lpEnumFunc(HWND hwnd,LPARAM lParam);
		HWND GetWndByPID(DWORD dwProcessID);  
	};
private:
	void AdjustLayout(HWND hParentWnd);
public:
	HWND    m_hExeWnd;
	DWORD m_dwProcessId;
	HWND	m_hParentWnd;
	HWND    m_hMaskWnd;
	BOOL    m_bIsLoad;
public:
	CString strTitle;
private:
	CCreateProcess m_CreateProcess;
};

