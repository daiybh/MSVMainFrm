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
	CString GetTitle();
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
	CString m_strExePath;
	DWORD m_dwProcessId;
	HWND	m_hParentWnd;
	HWND    m_hMaskWnd;
	BOOL    m_bIsLoad;
	BOOL	m_bAttachWnd_created;
	DWORD	m_dwTop;
	DWORD	m_dwLeft;
	DWORD	m_dwWidth;
	DWORD	m_dwHeight;
private:
	CString strExeOrgTitle;
private:
	CCreateProcess m_CreateProcess;

};

