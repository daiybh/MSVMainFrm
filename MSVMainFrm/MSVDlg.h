#pragma once
#include "resource.h"

// CMSVDlg �Ի���
#include "CreateProcessWnd.h"
class CMSVDlg : public CDialog,public CCreateProcessWnd
{
	DECLARE_DYNAMIC(CMSVDlg)
public:
protected:
public:
	CMSVDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMSVDlg();

	virtual BOOL AttachExeToWnd(LPCTSTR lpExePath,HWND hAttachWnd,BOOL bAlwaysCreateProcess);
// �Ի�������
	enum { IDD = IDD_MSVDLG };
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_strExePath;
	CRect   m_exeRect;
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
