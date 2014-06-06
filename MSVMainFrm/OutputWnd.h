
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口

class COutputList : public CListBox
{
// 构造
public:
	COutputList();

// 实现
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
// 构造
public:
	COutputWnd();

	void AddBuildinfo(LPCTSTR lpInfo);
// 属性
protected:
	CFont m_Font;

	CMFCTabCtrl	m_wndTabs;

	COutputList m_wndOutputBuild;
protected:
	void AdjustHorzScroll(CListBox& wndListBox);
	virtual void OnPressCloseButton();	
	virtual void OnSlide(BOOL bSlideOut);
// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

