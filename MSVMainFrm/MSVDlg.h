#pragma once
#include "resource.h"

// CMSVDlg �Ի���

class CMSVDlg : public CDialog
{
	DECLARE_DYNAMIC(CMSVDlg)
public:
	void SetExePath(CString strExePath);
	BOOL StartWork();
	void AdjustLayout();
protected:
	HWND GetWndByPID(DWORD dwProcessID);
    HWND CreateProcessEx(CString strExePath,CRect &rect);
public:
	CMSVDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMSVDlg();

// �Ի�������
	enum { IDD = IDD_MSVDLG };
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
