
// MSVMainFrmView.cpp : CMSVMainFrmView ���ʵ��
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

// CMSVMainFrmView ����/����

CMSVMainFrmView::CMSVMainFrmView()
{
	// TODO: �ڴ˴���ӹ������

}

CMSVMainFrmView::~CMSVMainFrmView()
{
}

BOOL CMSVMainFrmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMSVMainFrmView ����

void CMSVMainFrmView::OnDraw(CDC* /*pDC*/)
{
	CMSVMainFrmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CMSVMainFrmView ���

#ifdef _DEBUG
void CMSVMainFrmView::AssertValid() const
{
	CView::AssertValid();
}

void CMSVMainFrmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMSVMainFrmDoc* CMSVMainFrmView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSVMainFrmDoc)));
	return (CMSVMainFrmDoc*)m_pDocument;
}
#endif //_DEBUG


// CMSVMainFrmView ��Ϣ�������
