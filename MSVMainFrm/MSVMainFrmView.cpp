
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

IMPLEMENT_DYNCREATE(CMSVMainFrmView, CFormView)

BEGIN_MESSAGE_MAP(CMSVMainFrmView, CFormView)
END_MESSAGE_MAP()

// CMSVMainFrmView 构造/析构

CMSVMainFrmView::CMSVMainFrmView()
	: CFormView(CMSVMainFrmView::IDD)
{
	// TODO: 在此处添加构造代码

}

CMSVMainFrmView::~CMSVMainFrmView()
{
}

void CMSVMainFrmView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMSVMainFrmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMSVMainFrmView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//ResizeParentToFit();//自动调整框架大小
	CString xx = _T("U:\\V5.5(Pro2.3)\\Middle\\binU\\MSVMainAppU.exe");
#ifdef use_mdi_Framewnd
	AttachExeToWnd(xx,m_hWnd);
#endif
	AfxGetMainWnd()->SendMessage(WM_USER+101,0,0);

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
	CFormView::AssertValid();
}

void CMSVMainFrmView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMSVMainFrmDoc* CMSVMainFrmView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSVMainFrmDoc)));
	return (CMSVMainFrmDoc*)m_pDocument;
}
#endif //_DEBUG


// CMSVMainFrmView 消息处理程序
