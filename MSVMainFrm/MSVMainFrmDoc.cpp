
// MSVMainFrmDoc.cpp : CMSVMainFrmDoc 类的实现
//

#include "stdafx.h"
#include "MSVMainFrm.h"

#include "MSVMainFrmDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMSVMainFrmDoc

IMPLEMENT_DYNCREATE(CMSVMainFrmDoc, CDocument)

BEGIN_MESSAGE_MAP(CMSVMainFrmDoc, CDocument)
END_MESSAGE_MAP()


// CMSVMainFrmDoc 构造/析构

CMSVMainFrmDoc::CMSVMainFrmDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMSVMainFrmDoc::~CMSVMainFrmDoc()
{
}

BOOL CMSVMainFrmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	return TRUE;
}




// CMSVMainFrmDoc 序列化

void CMSVMainFrmDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMSVMainFrmDoc 诊断

#ifdef _DEBUG
void CMSVMainFrmDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMSVMainFrmDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMSVMainFrmDoc 命令

BOOL CMSVMainFrmDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO:  在此添加您专用的创建代码

	return TRUE;
}
