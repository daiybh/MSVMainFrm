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
	void CloseDlg(BOOL bSilent=FALSE);
	void ActiveWindow();
// �Ի�������
	enum { IDD = IDD_MSVDLG };
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CRect   m_exeRect;
public:
	afx_msg void OnClose();
};
