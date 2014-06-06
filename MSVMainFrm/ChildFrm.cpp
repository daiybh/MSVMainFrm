
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "MSVMainFrm.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	//cs.style &= ~(WS_THICKFRAME);
	//cs.style &= ~(WS_MAXIMIZEBOX);

//	cs.style |= WS_BORDER;
	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������

void CChildFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->ShowWindow(SW_MINIMIZE);
	//CMDIChildWndEx::OnClose();
}

void CChildFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMDIChildWndEx::OnSysCommand(nID, lParam);
	switch(nID)
	{
	case SC_MAXIMIZE:
		//case SC_ZOOM:
		{
			//	break;
		}
	case SC_RESTORE:
		{
			AfxGetMainWnd()->SendMessage(WM_USER+101,WPARAM(this),0x8888);
			//::SendMessage(GetActiveView()->m_hWnd,WM_SYSCOMMAND,nID,lParam);
			break;
		}
	case SC_MINIMIZE:
		//case SC_ICON:
		{
			break;
		}
	}
}
