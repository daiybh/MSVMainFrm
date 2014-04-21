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
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CMSVDlg 消息处理程序
void CMSVDlg::OnClose()
{
	this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CMSVDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//	AdjustLayout();
	// TODO: 在此处添加消息处理程序代码
}




void CMSVDlg::OnMove(int x, int y)
{
	__super::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
//	SendMessage(WM_ERASEBKGND,0,0);
//	SendMessage(WM_PAINT,0,0);
//	Invalidate(TRUE);

//	::SendMessage(m_hExeWnd,WM_ERASEBKGND,0,0);
//	::SendMessage(m_hExeWnd,WM_PAINT,0,0);
//	::RedrawWindow(m_hExeWnd);
//	::InvalidateRect();
//	UpdateWindow();
}


void CMSVDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
}


void CMSVDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	AfxGetMainWnd()->SendMessage(WM_USER+102,0x9898,(LPARAM)(LPCTSTR)_T("CMSVDlg::OnLButtonDblClk"));
	AdjustLayout();
	CRect attachWndRect,dlgRect;
	GetDlgItem(IDC_STATIC_ATTACHWND)->GetClientRect(attachWndRect);
	SetWindowPos(NULL, 0,15, attachWndRect.Width()+10, attachWndRect.Height()+15, 0);
	//::SetWindowPos(GetDlgItem(IDC_STATIC_ATTACHWND2)->m_hWnd,HWND_TOPMOST, 0,15, attachWndRect.Width()+10, attachWndRect.Height()+15, 0);
	__super::OnLButtonDblClk(nFlags, point);
}

BOOL CMSVDlg::AttachExeToWnd( LPCTSTR lpExePath,HWND hParentWnd,BOOL bAlwaysCreateProcess )
{
	HWND hAttachWnd = GetDlgItem(IDC_STATIC_ATTACHWND)->m_hWnd;
	BOOL bRet =  __super::AttachExeToWnd(lpExePath,hAttachWnd,bAlwaysCreateProcess);
	CRect attachWndRect,dlgRect;
	::GetClientRect(hAttachWnd,attachWndRect);
	SetWindowPos(NULL, 0,15, attachWndRect.Width()+10, attachWndRect.Height()+15, 0);
	//::SetWindowPos(GetDlgItem(IDC_STATIC_ATTACHWND2)->m_hWnd,HWND_TOP, 0,15, attachWndRect.Width()+10, attachWndRect.Height()+15, 0);
	return bRet;
}

