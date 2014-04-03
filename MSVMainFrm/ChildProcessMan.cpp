#include "StdAfx.h"
#include "ChildProcessMan.h"
#include "MSVDlg.h"
CChildAttachDialogMan::CChildAttachDialogMan(void)
{
	m_pParentWnd=NULL;
	CString strExeArr[]={_T("U:\\V5.5(Pro2.3)\\Middle\\binU\\MSVMainAppU.exe"),
		_T("U:\\V5.5(Pro2.3)\\Middle\\binU\\MgAvWriterU.exe")};
	m_arrAttachDlgInfoData.RemoveAll();
	{
		//testData
		for(int i=0;i<2;i++)
		{
			AttachDlgInfoData *lpData = new AttachDlgInfoData;
			lpData->strExePath =  strExeArr[i];
			lpData->pAttachDlg = NULL;

			CMSVDlg*pDlg = new CMSVDlg();
			//CWnd*pPp = (pParentWnd==NULL)?m_pParentWnd:pParentWnd;
			pDlg ->Create(IDD_MSVDLG);
			lpData->pAttachDlg = pDlg;

			AddToArr(lpData);
		}

		
	}
}

CChildAttachDialogMan::~CChildAttachDialogMan(void)
{
}

void CChildAttachDialogMan::StartWork( DWORD dwID,CWnd*pParentWnd,BOOL bAlwaysCreateProcess/*=FALSE*/ )
{	
	if(dwID>m_arrAttachDlgInfoData.GetSize())return;
	{
		AttachDlgInfoData*pData = m_arrAttachDlgInfoData.GetAt(dwID);
		CMSVDlg*pDlg = pData->pAttachDlg;
		if(pDlg==NULL)
		{
			pDlg = new CMSVDlg();
			CWnd*pPp = (pParentWnd==NULL)?m_pParentWnd:pParentWnd;
			pDlg ->Create(IDD_MSVDLG,pPp);
			::SetParent(pDlg->m_hWnd,pPp->m_hWnd);
			pDlg->ShowWindow(SW_HIDE);
			pData->pAttachDlg = pDlg;
		}
		if(pDlg)
		{

			CWnd*pPp = (pParentWnd==NULL)?m_pParentWnd:pParentWnd;
			::SetParent(pDlg->m_hWnd,pPp->m_hWnd);		

			if(!pDlg->IsWindowVisible()||bAlwaysCreateProcess)
			{				
				pDlg->StartWork(pData->strExePath,bAlwaysCreateProcess);
				pDlg->ShowWindow(SW_SHOW);
			}
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
