
// MSVMainFrmView.cpp : CMSVMainFrmView 类的实现
//

#include "stdafx.h"
#include "MSVMainFrm.h"

#include "MSVMainFrmDoc.h"
#include "MSVMainFrmView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMSVMainFrmView

IMPLEMENT_DYNCREATE(CMSVMainFrmView, CView)

BEGIN_MESSAGE_MAP(CMSVMainFrmView, CView)
END_MESSAGE_MAP()

// CMSVMainFrmView 构造/析构

CMSVMainFrmView::CMSVMainFrmView()
{
	// TODO: 在此处添加构造代码

}

CMSVMainFrmView::~CMSVMainFrmView()
{
}

BOOL CMSVMainFrmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMSVMainFrmView 绘制

void CMSVMainFrmView::OnDraw(CDC* /*pDC*/)
{
	CMSVMainFrmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CMSVMainFrmView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMSVMainFrmView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMSVMainFrmView 诊断

#ifdef _DEBUG
void CMSVMainFrmView::AssertValid() const
{
	CView::AssertValid();
}

void CMSVMainFrmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMSVMainFrmDoc* CMSVMainFrmView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSVMainFrmDoc)));
	return (CMSVMainFrmDoc*)m_pDocument;
}
#endif //_DEBUG


// CMSVMainFrmView 消息处理程序
