// MSVDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "MSVDlg.h"


// CMSVDlg 对话框
extern BOOL g_bMonitorRunning;
IMPLEMENT_DYNAMIC(CMSVDlg, CDialog)

CMSVDlg::CMSVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSVDlg::IDD, pParent)
{
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
END_MESSAGE_MAP()

// CMSVDlg 消息处理程序
void CMSVDlg::OnClose()
{
	if(!g_bMonitorRunning)
	{
		CString strLog;
		strLog.Format(_T("[%s][%s] OnClose"),this->GetTitle(),this->m_strExePath);
		AddLog(strLog);
		CloseDlg();	
	}else
	this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

BOOL CMSVDlg::AttachExeToWnd( LPCTSTR lpExePath,HWND hParentWnd,BOOL bAlwaysCreateProcess )
{		
	BOOL bRet =  __super::AttachExeToWnd(lpExePath,this->m_hWnd,bAlwaysCreateProcess);
// 	CRect attachWndRect,dlgRect;
// 	::GetClientRect(this->m_hWnd,attachWndRect);
	return bRet;
}

void CMSVDlg::CloseDlg(BOOL bSilent/*=FALSE*/)
{
	if(!bSilent)
	{
		::SendMessage(m_hExeWnd,SC_CLOSE,0,0);
		::SendMessage(m_hExeWnd,WM_CLOSE,0,0);
	}
	if(bSilent)
	{
		//::SendMessage(m_hExeWnd,);
		::SendMessage(m_hExeWnd,WM_CHAR,13,0);
		::SendMessage(m_hExeWnd, WM_KEYDOWN,VK_RETURN,0);
	}
}

void CMSVDlg::ActiveWindow()
{
	if(IsWindow(this->m_hExeWnd))
	{
		int nShowCmd = SW_SHOWNA;
		if(this->IsIconic())
			nShowCmd = SW_SHOWNORMAL;
		this->ShowWindow(nShowCmd);
	}
}

