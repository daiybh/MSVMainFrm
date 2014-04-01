// MSVDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "MSVDlg.h"


// CMSVDlg 对话框

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


void CMSVDlg::SetExePath(CString strExePath)
{
	m_strExePath = strExePath;
}

BOOL CMSVDlg::StartWork()
{

	if(m_bIsLoad)
	{
		ShowWindow(SW_SHOW);
		return TRUE;
	}
	AttachExeToWnd(m_strExePath,m_hWnd);
	m_bIsLoad = TRUE;
	AdjustLayout();
}
// CMSVDlg 消息处理程序
void CMSVDlg::OnClose()
{
	 this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}
void CMSVDlg::AdjustLayout()
{
	if(!m_bIsLoad || GetSafeHwnd() == NULL)
		return;
	CRect rect;
	GetClientRect(rect);
   	CWnd *cWnd=CWnd::FromHandle(m_hExeWnd);

	cWnd->GetClientRect(m_exeRect);
	if(m_exeRect.IsRectNull())
		cWnd->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), 0);
	else
	{
		SetWindowPos(NULL, m_exeRect.left, m_exeRect.top, m_exeRect.Width()+1, m_exeRect.Height()+10, 0);
	}
}
void CMSVDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
    
	AdjustLayout();
	// TODO: 在此处添加消息处理程序代码
}
