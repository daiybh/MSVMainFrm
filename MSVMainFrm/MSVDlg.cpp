// MSVDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "MSVDlg.h"


// CMSVDlg �Ի���

IMPLEMENT_DYNAMIC(CMSVDlg, CDialog)

CMSVDlg::CMSVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSVDlg::IDD, pParent)
{
    m_strExePath = _T("");
	m_bIsLoad    = FALSE;
}

CMSVDlg::~CMSVDlg()
{
}

void CMSVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMSVDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



BOOL CMSVDlg::StartWork( LPCTSTR lpStrExePath,BOOL bAlwaysCreateProcess/*=FALSE*/ )
{
	m_strExePath = lpStrExePath;
	return AttachExeToWnd(m_strExePath,m_hWnd,bAlwaysCreateProcess);	
}
// CMSVDlg ��Ϣ�������
void CMSVDlg::OnClose()
{
	 this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CMSVDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
    
	AdjustLayout();
	// TODO: �ڴ˴������Ϣ����������
}
