#pragma once
#include "stdafx.h"
#include "MsvClipDef.h"
#include "resource.h"
#include "MsvClipDef.h"
#include "afxcmn.h"
// CMSVInfoDlg �Ի���

class CMSVInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMSVInfoDlg)

public:
	CMSVInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMSVInfoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATAINFO };
public:
	BOOL SetDataInfo(int nCureSel,BYTE *lpData);

private:
	CString GetstrFileType(DWORD nID);
	CString GetstrCodeType(DWORD nID);
	CString GetstrSubCodeType(DWORD EncID,DWORD SubnID);
	CString GetstrChromaFmt(DWORD nID);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeDataInfo;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
private:
	BOOL  m_bIsShow;
};
