
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "ChildProcessMan.h"
#include "ProcessMonitor.h"
#ifndef use_mdi_Framewnd
#define CMDIFrameWndEx CFrameWndEx
#endif

class CMainFrame : public CMDIFrameWndEx
{
#ifdef use_mdi_Framewnd
	DECLARE_DYNAMIC(CMainFrame)
#else
	DECLARE_DYNCREATE(CMainFrame)
#endif
public:
	CMainFrame();

// 属性
public:

// 操作
public:
	void StartWork(DWORD dwItmeData,BOOL bAlwaysCreateProcess=FALSE);	



// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CChildAttachDialogMan	  m_ChildProcessMan;

	CProcessMonitor m_ProcessMonitor;
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	LRESULT onViewComplete(WPARAM wParam,LPARAM lParam);
	LRESULT onMsgAttachWnd(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnButtonStop();
	afx_msg void OnUpdateButtonStop(CCmdUI *pCmdUI);
	afx_msg void OnButtonMonitor();
	afx_msg void OnUpdateButtonMonitor(CCmdUI *pCmdUI);
};


