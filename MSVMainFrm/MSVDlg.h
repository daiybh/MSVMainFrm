#pragma once
#include "resource.h"

// CMSVDlg 对话框
#include "CreateProcessWnd.h"
class CMSVDlg : public CDialog,public CCreateProcessWnd
{
	DECLARE_DYNAMIC(CMSVDlg)
public:
protected:
public:
	CMSVDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMSVDlg();

	virtual BOOL AttachExeToWnd(LPCTSTR lpExePath,HWND hAttachWnd,BOOL bAlwaysCreateProcess);
	void CloseDlg(BOOL bSilent=FALSE);
	void ActiveWindow();
// 对话框数据
	enum { IDD = IDD_MSVDLG };
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CRect   m_exeRect;
public:
	afx_msg void OnClose();
};
