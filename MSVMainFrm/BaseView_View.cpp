// BaseView_View.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "BaseView_View.h"


// CBaseView_View

IMPLEMENT_DYNCREATE(CBaseView_View, CView)

CBaseView_View::CBaseView_View()
{

}

CBaseView_View::~CBaseView_View()
{
}

BEGIN_MESSAGE_MAP(CBaseView_View, CView)
END_MESSAGE_MAP()


// CBaseView_View ��ͼ

void CBaseView_View::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CBaseView_View ���

#ifdef _DEBUG
void CBaseView_View::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseView_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseView_View ��Ϣ�������
