// MSVMainFrmView_Base_ScrollView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "MSVMainFrmDoc.h"
#include "MSVMainFrmView_Base_ScrollView.h"


// CMSVMainFrmView_Base_ScrollView

IMPLEMENT_DYNCREATE(CMSVMainFrmView_Base_ScrollView, CScrollView)

CMSVMainFrmView_Base_ScrollView::CMSVMainFrmView_Base_ScrollView()
{

}

CMSVMainFrmView_Base_ScrollView::~CMSVMainFrmView_Base_ScrollView()
{
}


BEGIN_MESSAGE_MAP(CMSVMainFrmView_Base_ScrollView, CScrollView)
	ON_MESSAGE(WM_USER+120,onResize)
END_MESSAGE_MAP()


// CMSVMainFrmView_Base_ScrollView ��ͼ

void CMSVMainFrmView_Base_ScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);


	int iPos = GetDocument()->m_nFilePos;
	this->GetParentFrame()->ShowWindow(SW_MINIMIZE);
	AfxGetMainWnd()->SendMessage(WM_USER+101,WPARAM(this->GetParentFrame()),iPos);
}

void CMSVMainFrmView_Base_ScrollView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CMSVMainFrmView_Base_ScrollView ���

#ifdef _DEBUG
void CMSVMainFrmView_Base_ScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CMSVMainFrmView_Base_ScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}


#endif
#endif //_DEBUG


// CMSVMainFrmView_Base_ScrollView ��Ϣ�������

LRESULT CMSVMainFrmView_Base_ScrollView::onResize( WPARAM wParam,LPARAM lParam )
{
	DWORD dWidth = (DWORD)wParam;
	DWORD dHeight = (DWORD)lParam;
	if(dWidth ==99999)
	{
		POINT pt;
		pt.x = GetScrollPos(SB_HORZ);
		pt.y = GetScrollPos(SB_VERT);
		pt.y = dHeight;
		ScrollToPosition(pt);
	}
	else
	{
		CSize sizeTotal(dWidth,dHeight);
		SetScrollSizes(MM_TEXT,sizeTotal);
	}
	return 1;
}