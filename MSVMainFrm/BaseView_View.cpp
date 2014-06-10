// BaseView_View.cpp : 实现文件
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


// CBaseView_View 绘图

void CBaseView_View::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CBaseView_View 诊断

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


// CBaseView_View 消息处理程序
