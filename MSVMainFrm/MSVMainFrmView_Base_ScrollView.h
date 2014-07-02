#pragma once



// CMSVMainFrmView_Base_ScrollView 视图

class CMSVMainFrmView_Base_ScrollView : public CScrollView
{
	DECLARE_DYNCREATE(CMSVMainFrmView_Base_ScrollView)

protected:
	CMSVMainFrmView_Base_ScrollView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMSVMainFrmView_Base_ScrollView();

	// 属性
public:
	CMSVMainFrmDoc* GetDocument() const;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次

	LRESULT onResize(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // MSVMainFrmView.cpp 中的调试版本
inline CMSVMainFrmDoc* CMSVMainFrmView_Base_ScrollView::GetDocument() const
{ return reinterpret_cast<CMSVMainFrmDoc*>(m_pDocument); }
#endif

