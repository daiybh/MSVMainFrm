
// MSVMainFrmView.h : CMSVMainFrmView 类的接口
//


#pragma once

#include "MSVDlg.h"
class CMSVMainFrmView : public CFormView,CCreateProcessWnd
{
protected: // 仅从序列化创建
	CMSVMainFrmView();
	DECLARE_DYNCREATE(CMSVMainFrmView)

public:
	enum{ IDD = IDD_MSVMAINFRM_FORM };

// 属性
public:
	CMSVMainFrmDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMSVMainFrmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MSVMainFrmView.cpp 中的调试版本
inline CMSVMainFrmDoc* CMSVMainFrmView::GetDocument() const
   { return reinterpret_cast<CMSVMainFrmDoc*>(m_pDocument); }
#endif

