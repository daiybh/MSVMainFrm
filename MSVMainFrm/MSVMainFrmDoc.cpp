
// MSVMainFrmDoc.cpp : CMSVMainFrmDoc ���ʵ��
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


// CMSVMainFrmDoc ����/����

CMSVMainFrmDoc::CMSVMainFrmDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMSVMainFrmDoc::~CMSVMainFrmDoc()
{
}

BOOL CMSVMainFrmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	return TRUE;
}




// CMSVMainFrmDoc ���л�

void CMSVMainFrmDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMSVMainFrmDoc ���

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


// CMSVMainFrmDoc ����

BOOL CMSVMainFrmDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO:  �ڴ������ר�õĴ�������

	return TRUE;
}
