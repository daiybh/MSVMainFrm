
// MSVMainFrmView.h : CMSVMainFrmView 类的接口
//


#pragma once


class CMSVMainFrmView : public CView
{
protected: // 仅从序列化创建
	CMSVMainFrmView();
	DECLARE_DYNCREATE(CMSVMainFrmView)

// 属性
public:
	CMSVMainFrmDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

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

