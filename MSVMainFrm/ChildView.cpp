
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  MSVINFOCOUNT  9

// CChildView

CChildView::CChildView()
{
	m_lpMsvInfo = NULL;
}

CChildView::~CChildView()
{
	if(m_lpMsvInfo != NULL)
	{
		m_lpMsvInfo->DestroyWindow();
	    delete m_lpMsvInfo;
		m_lpMsvInfo= NULL;
	}

}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{


	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	
	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}


BOOL CChildView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
     int nRet = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	 if(!m_lvMsvMgr.Create(  WS_BORDER|LVS_REPORT|LVS_ALIGNLEFT,CRect(0,0,500,2000),this,1000))
	 {
		 TRACE0("Failed to create instant bar child\n");
		 return -1;
	 }

	 DWORD dwExStyle = m_lvMsvMgr.GetExtendedStyle();
	 dwExStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	 dwExStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	 m_lvMsvMgr.SetExtendedStyle(dwExStyle); //设置扩展风格

	 TCHAR strText[MSVINFOCOUNT][40]={
         _T("Material Name"),
         _T("TaskID"),
		 _T("Capture Time"),
         _T("TotalFrames"),
         _T("Chunk Count"),
         _T("High Video Information"),
         _T("High Audio Information"),
         _T("Low  Video Information"),
		 _T("Low  Audio Information")
	 };
	
	 LV_COLUMN list;
	 list.mask =  LVCF_TEXT |LVCF_WIDTH| LVCF_FMT;// |LVCF_SUBITEM;
	 list.fmt = LVCFMT_CENTER;
	 list.cx = wcslen(strText[0])*8;

	 list.pszText   = strText[0];
	 list.iSubItem = 0;
	 list.iOrder=0;
	 m_lvMsvMgr.InsertColumn(0,&list);
  
	 for(int index = 1;index < MSVINFOCOUNT;index++)
	 {
		 list.mask =  LVCF_TEXT |LVCF_WIDTH| LVCF_FMT|LVCF_SUBITEM;// ;
		 list.fmt = LVCFMT_CENTER;
		 list.cx = wcslen(strText[index])*8;
		 list.pszText   =strText[index];
		 list.iSubItem =1;
		 list.iOrder=1;
		 m_lvMsvMgr.InsertColumn(index,&list);
	 }
	
     m_lvMsvMgr.ShowWindow(SW_SHOW);
	 if(m_lpMsvInfo == NULL)
	 {
		 m_lpMsvInfo = new CMSVInfoDlg();
		 ASSERT(m_lpMsvInfo != NULL);

		 m_lpMsvInfo->Create(IDD_DIALOG_DATAINFO,this);

		 m_lpMsvInfo ->ShowWindow(SW_HIDE);
	 }
	 return nRet;
}

void CChildView::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);

	//UpdateMSVRect(4);
 
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect);

	m_lvMsvMgr.MoveWindow(rect);
}

//-----------------------------------------------------------
// 函数名称：
//     
// 参数：
//    - 
// 返回：
//     
// 说明：
//     
//-----------------------------------------------------------
UINT CChildView::InsertMSVData(CString strTaskName,DWORD dwTaskID)
{
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT ; 
	lvi.iSubItem = 0;
	lvi.pszText = strTaskName.AllocSysString();
	lvi.iItem = m_lvMsvMgr.GetItemCount();
    
	int nRowCur = m_lvMsvMgr.InsertItem(&lvi);

	m_lvMsvMgr.SetItemData(nRowCur,dwTaskID);

	return nRowCur;
}

BOOL CChildView::SetMSVData(UINT nRowItem,STMSVMaterialInfo *lpNode)
{
	DWORD dwTaskID=m_lvMsvMgr.GetItemData(nRowItem);

	if(dwTaskID != lpNode->dwTaskId)
		return FALSE;

	CString strTemp;
	strTemp.Format(_T("%d"),lpNode->dwTaskId);
	m_lvMsvMgr.SetItemText(nRowItem,1,strTemp);
	m_lvMsvMgr.SetItemText(nRowItem,2,lpNode->timeCreateTime.Format(_T("%Y_%m_%d %H:%M:%S")));
	strTemp.Format(_T("%d"),lpNode->dwTotalFrame);
	m_lvMsvMgr.SetItemText(nRowItem,3,strTemp);

	strTemp.Format(_T("%d"),lpNode->dwChunkCount+1);
	m_lvMsvMgr.SetItemText(nRowItem,4,strTemp);

    //
	m_lvMsvMgr.SetItemText(nRowItem,5,_T("..."));
	m_lvMsvMgr.SetItemText(nRowItem,6,_T("..."));
	m_lvMsvMgr.SetItemText(nRowItem,7,_T("..."));
	m_lvMsvMgr.SetItemText(nRowItem,8,_T("..."));
  	return TRUE;
}

BOOL CChildView::ShowMsvDataInfo(UINT nRowSubItem,STMSVMaterialInfo *lpNode)
{
	int nCurIndex = nRowSubItem-5;
	if(nRowSubItem < 0)
		return FALSE;

    if(m_lpMsvInfo != NULL)
	{
		if(m_lpMsvInfo->SetDataInfo(nCurIndex,lpNode->lpDataInfo[nCurIndex]))
			
		{
			CPoint pt;
			GetCursorPos(&pt);
			m_lpMsvInfo->CenterWindow();
			m_lpMsvInfo->ShowWindow(SW_SHOW);
		}

	}
    
	return TRUE;
}