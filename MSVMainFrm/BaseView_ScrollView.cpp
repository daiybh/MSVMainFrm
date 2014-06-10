// MainFrm_ScrollView.cpp : 实现文件
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "MSVMainFrmDoc.h"
#include "BaseView_ScrollView.h"


// CMainFrm_ScrollView

IMPLEMENT_DYNCREATE(CBaseView_ScrollView, CScrollView)

CBaseView_ScrollView::CBaseView_ScrollView()
{

}

CBaseView_ScrollView::~CBaseView_ScrollView()
{
}


BEGIN_MESSAGE_MAP(CBaseView_ScrollView, CScrollView)
END_MESSAGE_MAP()


// CMainFrm_ScrollView 绘图
//*
void CBaseView_ScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	//SetScrollSizes(MM_TEXT, sizeTotal);
#ifdef use_mdi_Framewnd
	ResizeParentToFit();//自动调整框架大小
#endif	

	CMSVMainFrmDoc *pDoc = (CMSVMainFrmDoc*)GetDocument();
	int iPos =pDoc->m_nFilePos;
	this->GetParentFrame()->ShowWindow(SW_MINIMIZE);
	AfxGetMainWnd()->SendMessage(WM_USER+101,WPARAM(this->GetParentFrame()),iPos);
}
/**/
void CBaseView_ScrollView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CMainFrm_ScrollView 诊断

#ifdef _DEBUG
void CBaseView_ScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseView_ScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainFrm_ScrollView 消息处理程序
