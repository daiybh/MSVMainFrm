
// ChildView.h : CChildView 类的接口
//

#pragma once
#include "MSVListCtrl.h"
 #include "MSVInfoDlg.h"
// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 属性
public:
// 操作
	CMSVListCtrl m_lvMsvMgr;
	CMSVInfoDlg  *m_lpMsvInfo;
	

	UINT  InsertMSVData(CString strTaskName,DWORD dwTaskID);
	BOOL  SetMSVData(UINT nRowItem,STMSVMaterialInfo *lpNode);
	BOOL  ShowMsvDataInfo(UINT nRowSubItem,STMSVMaterialInfo *lpNode);
public:
  
// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
 
// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

