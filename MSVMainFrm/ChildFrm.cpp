
// ChildFrm.cpp : CChildFrame 类的实现
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

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	//cs.style &= ~(WS_THICKFRAME);
	//cs.style &= ~(WS_MAXIMIZEBOX);

//	cs.style |= WS_BORDER;
	return TRUE;
}

// CChildFrame 诊断

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

// CChildFrame 消息处理程序

void CChildFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_MINIMIZE);
	//CMDIChildWndEx::OnClose();
}

void CChildFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
