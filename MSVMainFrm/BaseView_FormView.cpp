
// MSVMainFrmView.cpp : CMSVMainFrmView 类的实现
//

#include "stdafx.h"
#include "MSVMainFrm.h"

#include "MSVMainFrmDoc.h"
#include "BaseView_FormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMSVMainFrmView

IMPLEMENT_DYNCREATE(CBaseView_FormView, CFormView)

BEGIN_MESSAGE_MAP(CBaseView_FormView, CFormView)
	ON_MESSAGE(WM_USER+120,onResize)
END_MESSAGE_MAP()

// CMSVMainFrmView 构造/析构

CBaseView_FormView::CBaseView_FormView()
	: CFormView(CBaseView_FormView::IDD)
{
	// TODO: 在此处添加构造代码

}

CBaseView_FormView::~CBaseView_FormView()
{
}

void CBaseView_FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CBaseView_FormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style &= WS_VSCROLL |~WS_THICKFRAME;
	return CFormView::PreCreateWindow(cs);
}

void CBaseView_FormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}

void CBaseView_FormView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBaseView_FormView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMSVMainFrmView 诊断

#ifdef _DEBUG
void CBaseView_FormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBaseView_FormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMSVMainFrmDoc* CBaseView_FormView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSVMainFrmDoc)));
	return (CMSVMainFrmDoc*)m_pDocument;
}
#endif //_DEBUG


// CMSVMainFrmView 消息处理程序

void CBaseView_FormView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: 在此添加专用代码和/或调用基类

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if(bActivate)
	{
		
	}
}

LRESULT CBaseView_FormView::onResize( WPARAM wParam,LPARAM lParam )
{
	DWORD dWidth = (DWORD)wParam;
	DWORD dHeight = (DWORD)lParam;

	CSize sizeTotal(dWidth,dHeight);
	SetScrollSizes(MM_LOENGLISH,sizeTotal);
	SetScrollPos(SB_VERT,100);
	//invalidaterect();
	Invalidate();
	//UpdateWindow();
	return 1;
}
