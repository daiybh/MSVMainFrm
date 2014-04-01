#include "StdAfx.h"
#include "ChildProcessMan.h"
#include "MSVDlg.h"
CChildAttachDialogMan::CChildAttachDialogMan(void)
{
	m_pParentWnd=NULL;
	for (int n=0;n<8;n++)
	{
		m_lpAttachDlg[n] = NULL;
	}
}

CChildAttachDialogMan::~CChildAttachDialogMan(void)
{
}

void CChildAttachDialogMan::StartWork( DWORD dwItmeData )
{
	if(dwItmeData<1)return;
	MSVInfoData *lpMSVInfo =NULL;
	if(dwItmeData >0)
	{
		lpMSVInfo = (MSVInfoData*)dwItmeData;
	}
	int n=0;
	if(m_lpAttachDlg[0]==NULL)
		CreateChildDlg(4);
	for (;n<4;n++)
	{
		if(!m_lpAttachDlg[n]->IsWindowVisible())
		{
			m_lpAttachDlg[n]->SetExePath(lpMSVInfo->strExePath);
			m_lpAttachDlg[n]->StartWork();
			m_lpAttachDlg[n]->ShowWindow(SW_SHOW);
			break;
		}
	}
}

void CChildAttachDialogMan::CreateChildDlg( int nChanCount )
{
	if(m_pParentWnd==NULL)return;
	for (int n=0;n<nChanCount;n++)
	{
		if(m_lpAttachDlg[n] == NULL)
		{
			m_lpAttachDlg[n] = new CMSVDlg();

			//	pDlg->Create(IDD_MSVDLG,);
			m_lpAttachDlg[n] ->Create(IDD_MSVDLG,m_pParentWnd);

			::SetParent(m_lpAttachDlg[n]->m_hWnd,m_pParentWnd->m_hWnd);
			m_lpAttachDlg[n]->ShowWindow(SW_HIDE);
		}
	}
	//AdjustLayout(nChanCount);
}
