#include "StdAfx.h"
#include "ChildProcessMan.h"
#include "MSVDlg.h"
CChildAttachDialogMan::CChildAttachDialogMan(void)
{
	m_pParentWnd=NULL;
	m_arrAttachDlgInfoData.RemoveAll();
	{
		//testData
		for(int i=0;i<4;i++)
		{
			AttachDlgInfoData *lpData = new AttachDlgInfoData;
			lpData->strExePath =  _T("U:\\V5.5(Pro2.3)\\Middle\\binU\\MSVMainAppU.exe");
			lpData->pAttachDlg = NULL;
			AddToArr(lpData);
		}
	}
}

CChildAttachDialogMan::~CChildAttachDialogMan(void)
{
}

void CChildAttachDialogMan::StartWork( DWORD dwItmeData )
{
	
	if(dwItmeData>m_arrAttachDlgInfoData.GetSize())return;
	{
		AttachDlgInfoData*pData = m_arrAttachDlgInfoData.GetAt(dwItmeData);
		CMSVDlg*pDlg = pData->pAttachDlg;
		if(pDlg==NULL)
		{
			pDlg = new CMSVDlg();
			pDlg ->Create(IDD_MSVDLG,m_pParentWnd);
			::SetParent(pDlg->m_hWnd,m_pParentWnd->m_hWnd);
			pDlg->ShowWindow(SW_HIDE);
			pData->pAttachDlg = pDlg;
		}
		if(pDlg&&!pDlg->IsWindowVisible())
		{
			pDlg->SetExePath(pData->strExePath);
			pDlg->StartWork();
			pDlg->ShowWindow(SW_SHOW);
		}
	}
}

void CChildAttachDialogMan::CreateChildDlg()
{
	if(m_pParentWnd==NULL)return;
	for (int n=0;n<m_arrAttachDlgInfoData.GetSize();n++)
	{
		AttachDlgInfoData * pData = m_arrAttachDlgInfoData.GetAt(n);
		if(pData&&pData->pAttachDlg==NULL)		
		{
			CMSVDlg*pDlg = new CMSVDlg();
			pDlg ->Create(IDD_MSVDLG,m_pParentWnd);
			::SetParent(pDlg->m_hWnd,m_pParentWnd->m_hWnd);
			pDlg->ShowWindow(SW_HIDE);
			pData->pAttachDlg = pDlg;
		}
	}
}

void CChildAttachDialogMan::AddToArr( AttachDlgInfoData*pData )
{
	pData->nCurID = m_arrAttachDlgInfoData.GetSize();
	m_arrAttachDlgInfoData.Add(pData);
}
