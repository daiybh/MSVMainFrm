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
	ON_WM_MOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMSVDlg ��Ϣ�������
void CMSVDlg::OnClose()
{
	this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CMSVDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//	AdjustLayout();
	// TODO: �ڴ˴������Ϣ����������
}




void CMSVDlg::OnMove(int x, int y)
{
	__super::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
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
		// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� __super::OnPaint()
}
