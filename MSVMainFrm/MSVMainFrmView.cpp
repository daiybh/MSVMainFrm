
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

IMPLEMENT_DYNCREATE(CMSVMainFrmView, CFormView)

BEGIN_MESSAGE_MAP(CMSVMainFrmView, CFormView)
END_MESSAGE_MAP()

// CMSVMainFrmView ����/����

CMSVMainFrmView::CMSVMainFrmView()
	: CFormView(CMSVMainFrmView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CMSVMainFrmView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//ResizeParentToFit();//�Զ�������ܴ�С
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


// CMSVMainFrmView ���

#ifdef _DEBUG
void CMSVMainFrmView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMSVMainFrmView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMSVMainFrmDoc* CMSVMainFrmView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSVMainFrmDoc)));
	return (CMSVMainFrmDoc*)m_pDocument;
}
#endif //_DEBUG


// CMSVMainFrmView ��Ϣ�������
