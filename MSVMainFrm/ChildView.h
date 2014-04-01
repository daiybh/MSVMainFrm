
// ChildView.h : CChildView ��Ľӿ�
//

#pragma once
#include "MSVListCtrl.h"
 #include "MSVInfoDlg.h"
// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
// ����
	CMSVListCtrl m_lvMsvMgr;
	CMSVInfoDlg  *m_lpMsvInfo;
	

	UINT  InsertMSVData(CString strTaskName,DWORD dwTaskID);
	BOOL  SetMSVData(UINT nRowItem,STMSVMaterialInfo *lpNode);
	BOOL  ShowMsvDataInfo(UINT nRowSubItem,STMSVMaterialInfo *lpNode);
public:
  
// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
 
// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

