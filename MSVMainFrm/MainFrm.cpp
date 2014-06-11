
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MSVMainFrm.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
#ifdef use_mdi_Framewnd
IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)
#else
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)
#define CMDIFrameWndEx CFrameWndEx
#endif

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;
#define ID_MSG_VIEW_COMPLETE WM_USER+101
#define ID_MSG_ATTACH_WND	 WM_USER+102
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_MESSAGE(ID_MSG_VIEW_COMPLETE,&CMainFrame::onViewComplete)
	ON_MESSAGE(ID_MSG_ATTACH_WND,&CMainFrame::onMsgAttachWnd)
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_BUTTON_STOP, &CMainFrame::OnButtonStop)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_STOP, &CMainFrame::OnUpdateButtonStop)
	ON_COMMAND(ID_BUTTON_MONITOR, &CMainFrame::OnButtonMonitor)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MONITOR, &CMainFrame::OnUpdateButtonMonitor)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构
BOOL g_bMonitorRunning=FALSE;
CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
/*
	if(m_wndMDIClient.Attach(m_hWndMDIClient)==0){
		return -1;
	}
	/**/
	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 加载菜单项图像(不在任何标准工具栏上):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	//CDockablePane* pTabbedBar = NULL;
	//m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, FALSE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

#ifdef use_mdi_Framewnd
	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);
#endif
	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

// 	if (CMFCToolBar::GetUserImages() == NULL)
// 	{
// 		// 加载用户定义的工具栏图像
// 		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
// 		{
// 			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
// 			CMFCToolBar::SetUserImages(&m_UserImages);
// 		}
// 	}

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);
	
	lstBasicCommands.AddTail(ID_BUTTON_STOP);
	lstBasicCommands.AddTail(ID_BUTTON_MONITOR);
	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	CMDIFrameWndEx::EnableLoadDockState(TRUE) ;

	m_wndFileView.FillView(&m_ChildProcessMan);
	SetTimer(1,1000,NULL);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建类视图
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_MSV_IP);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 400), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“类视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建文件视图
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_MSV_SDI);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 400), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
#ifdef use_mdi_Framewnd
	ShowWindowsDialog();
#endif
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	CWinApp* pApp = AfxGetApp();
	if (pApp->m_pMainWnd == NULL)
		pApp->m_pMainWnd = this;

	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

void CMainFrame::ActiveWindow(DWORD dwID)
{
	m_ChildProcessMan.ActiveWindow(dwID);
}


#define  MODULE_LEN		(64)

// 定义函数入口全局变量
static VOID (*g_pfn)(WCHAR* szModuleName,LONG  lLogLevel, const WCHAR *fmt);
static BOOL (*g_pfnNMInit)();
HINSTANCE g_hinstPlugLib = NULL;
void LoadNmLoger()
{
	//初始化代码, 
	g_hinstPlugLib = LoadLibrary(_T("sonaps.logger.client.dll"));
	if (g_hinstPlugLib == NULL)
	{
	//	AfxMessageBox(_T("LoadLibrary(sonaps.logger.client.dll) Failed!"));
		return;
	}
	
	const char szFn[] = "NMTrace0";
	const char szNMInit[] = "NMInit";
	*(FARPROC*)&g_pfn = GetProcAddress(g_hinstPlugLib, szFn);
	*(FARPROC*)&g_pfnNMInit = GetProcAddress(g_hinstPlugLib, szNMInit);

	if (g_pfnNMInit != NULL)
	{
		g_pfnNMInit();
	}
}

void WriteLog(WCHAR* szModuleName,LONG  lLogLevel, LPCTSTR strLog)
//void WriteLog(WCHAR* szModuleName,LONG  lLogLevel,const WCHAR *fmt, ...)
{
	if(g_pfn==NULL)
	{
		LoadNmLoger();
	}
	if (g_pfn != NULL)
	{	
		try
		{
			g_pfn(szModuleName, lLogLevel, strLog);
			//strLog.ReleaseBuffer();
		}
		catch(...)		//当字符串里包含“%S”这样的转义字符时有可能会异常
		{

		}
	}
}
void WriteLog(LPCTSTR strLog)
{
	WriteLog(_T("ProcessManager"),2,strLog);
//	g_pfn(_T("ProcessManager"), 2, strLog);
}
void CMainFrame::AddBuildinfo(LPCTSTR lpStrInfo)
{
	m_wndOutput.AddBuildinfo(lpStrInfo);
	WriteLog(lpStrInfo);


}
BOOL  CMainFrame::CreateChildProcess( DWORD dwItmeData,CString &strTitle,BOOL bAlwaysCreateProcess/*=FALSE*/ )
{
	HTREEITEM pTreePosItem =  m_ChildProcessMan.CreateChildProcess(dwItmeData,NULL,strTitle,bAlwaysCreateProcess);
	if(pTreePosItem)
	{
		m_wndFileView.SetItemTitle(pTreePosItem,strTitle);
	}
	return (pTreePosItem!=NULL);
}
LRESULT CMainFrame::onViewComplete( WPARAM wParam,LPARAM lParam )
{
	CWnd *pWnd = (CWnd*)wParam;
	CFrameWnd *pFrameWnd =(CFrameWnd*)wParam;
	
	int nGroupID = (int )lParam;
	m_ChildProcessMan.UpdateGroupFramewnd(nGroupID,pFrameWnd);
	
	return 1;
}

LRESULT CMainFrame::onMsgAttachWnd( WPARAM wParam,LPARAM lParam )
{
	DWORD dId = (DWORD)wParam;
	if(dId==0x9898){

		AddBuildinfo((LPCTSTR)lParam);
		return 1;
	}else if(dId==0x9999){
		AddBuildinfo(_T("onMsgAttachWnd 0x9999"));
		{
			//调整为组模式
		}
		return 1;
	}
	CString strTitle;
	CreateChildProcess(dId,strTitle,TRUE);
	return 1;
}
CString strStatusInfo[]={_T("Stop Monitor"),_T("Resume Monitor")};
void CMainFrame::OnButtonStop()
{
	// TODO: 在此添加命令处理程序代码
	m_ProcessMonitor.PauseMonitor();
	SetTimer(2,1000,NULL);
	g_bMonitorRunning =FALSE ;
	CString strLog;
	strLog.Format(_T("%s-%d"),strStatusInfo[0],m_ProcessMonitor.GetMonitorStatus());
	AddBuildinfo(strLog);
}
void CMainFrame::OnUpdateButtonStop(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(!g_bMonitorRunning);
}

void CMainFrame::OnButtonMonitor()
{
	// TODO: 在此添加命令处理程序代码	
	g_bMonitorRunning =TRUE ;
	m_ProcessMonitor.ResumeMonitor();
	KillTimer(2);
	CString strLog;
	strLog.Format(_T("%s-%d"),strStatusInfo[1],m_ProcessMonitor.GetMonitorStatus());
	AddBuildinfo(strLog);
}

void CMainFrame::OnUpdateButtonMonitor(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(g_bMonitorRunning);
}
DWORD getProcessID(POINT pt)
{
	HWND hW = WindowFromPoint(pt);
	DWORD processID,threadID;
	threadID = GetWindowThreadProcessId(hW,&processID);
	return processID;
}
BOOL IsSameWindow(DWORD dProcessID,POINT pt)
{
	return (dProcessID== getProcessID(pt));
}
BOOL CMainFrame::MouseEvent_CallBack(WPARAM wParam,LPARAM lParam, LPVOID pUserData)
{
	CMainFrame*pThis = (CMainFrame*)pUserData;
	return pThis->MouseEventCB(wParam,lParam);
}

BOOL CMainFrame::MouseEventCB( WPARAM wParam,LPARAM lParam )
{
	//if(m_ProcessMonitor.GetMonitorStatus())return FALSE;
	if(WM_LBUTTONDOWN==wParam || WM_RBUTTONDOWN==wParam)
	{
		//PMSLLHOOKSTRUCT pMouseSt =(PMSLLHOOKSTRUCT)lParam;
		PMOUSEHOOKSTRUCT pMouseSt =(PMOUSEHOOKSTRUCT)lParam;
		//检查鼠标是否落在自己的子进程
		//TODO: 这里的遍历效率是个问题。
		DWORD dwProcessID = getProcessID(pMouseSt->pt);
		BOOL bRet=FALSE;
		for(int i=0;i<m_ChildProcessMan.m_arrAttachDlgInfoData.GetCount();i++)
		{
			AttachDlgInfoData*pdata = m_ChildProcessMan.m_arrAttachDlgInfoData.GetAt(i);
			if(pdata->GetProcessID()==dwProcessID)
			{
				pdata->ActiveWindow();
				return 1;
			}
		}
	}
	return FALSE;
}

typedef BOOL (CALLBACK *ENCODEDATA_CALLBACKFUNC)(WPARAM wparam,LPARAM lParam, LPVOID pUserData);
typedef BOOL (CALLBACK *LPFUNC_STARTHOOKMOUSE)(ENCODEDATA_CALLBACKFUNC pFunc,LPVOID lpUserData);
typedef void (CALLBACK *LPFUNC_STOPHOOKMOUSE)();
LPFUNC_STARTHOOKMOUSE g_HookFunc_StartHook=NULL;
LPFUNC_STOPHOOKMOUSE  g_HookFunc_StopHook=NULL;
HHOOK hhkMouse = NULL;
HINSTANCE g_hInstDll = NULL;

BOOL CMainFrame::StartHookMouse()
{
	g_hInstDll=LoadLibrary(_T("WindowsHook.dll"));
	if(g_hInstDll==NULL)
	{
	//	AfxMessageBox(_T("no MouseHook.dll"));
		return FALSE;
	}

	g_HookFunc_StartHook=(LPFUNC_STARTHOOKMOUSE)::GetProcAddress(g_hInstDll,"StartHookMouse");
	if(g_HookFunc_StartHook==NULL)
	{
	//	AfxMessageBox(_T("func StartHookMouse not found!"));
		return FALSE;
	}
	//if (StartHook(hWnd,GetCurrentProcessId()))
	if(!g_HookFunc_StartHook(MouseEvent_CallBack,this))
	{
	//	AfxMessageBox(_T("Hook Mouse faild"));
	}
	g_HookFunc_StopHook = (LPFUNC_STOPHOOKMOUSE)::GetProcAddress(g_hInstDll,"StopHookMouse");
	return FALSE;
}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==1)
	{
		KillTimer(1);
		//鼠标钩子
		StartHookMouse();
		//创建一堆 doc view
		//由于如果文件不存在 那么OpenDocumentFile 会奔溃
		//所以打开temp中的一个文件
		TCHAR tempPath[MAX_PATH];
		GetTempPath(MAX_PATH,tempPath);
		std::map<int,stGroupInfo*>::iterator it = m_ChildProcessMan.m_mapGroupInfo.begin();
		CString strLastName;
		for(;it!=m_ChildProcessMan.m_mapGroupInfo.end();++it)
		{
			CString xx;
			stGroupInfo *pInfo = it->second;
			xx.Format(_T("%s\\%s@%d"),tempPath,pInfo->strGroupName,pInfo->nGroupID);
			if(strLastName.IsEmpty())
			{
				FILE *pFile = _tfopen(xx,_T("w"));
				if(pFile)
				{
					fclose(pFile);
				}
			}else{
				_trename(strLastName,xx);
			}
			strLastName = xx;
			AfxGetApp()->OpenDocumentFile(xx);
		}
		if(!strLastName.IsEmpty())
			_tremove(strLastName);
		m_ProcessMonitor.StartWork(this->m_hWnd,&m_ChildProcessMan.m_arrAttachDlgInfoData);
		g_bMonitorRunning=TRUE;
//		m_ProcessMonitor.StartWork(this,&m_ChildProcessMan.m_arrAttachDlgInfoData);
	}
	else if(nIDEvent==2)
	{
		//AddBuildinfo(m_ChildProcessMan.CheckWindow());
		for(int i=0;i<m_ChildProcessMan.m_arrAttachDlgInfoData.GetSize();i++)
		{
			AttachDlgInfoData*pData = m_ChildProcessMan.m_arrAttachDlgInfoData.GetAt(i);
			if(pData==NULL)continue;
			bool bRet =pData->IsChildWindowLive();
			if(!bRet)
			{
				m_wndFileView.SetItemTitle(pData->pTreePosItem,pData->GetTitle());
			}
		}
	}
	CMDIFrameWndEx::OnTimer(nIDEvent);
}

CMDIChildWnd * CMainFrame::GetNextMDIChildWnd()
{
	if(!m_pWndCurrentChild){
		m_pWndCurrentChild = m_wndMDIClient.GetWindow(GW_CHILD);
	}else{
		m_pWndCurrentChild = (CMDIChildWnd*)m_pWndCurrentChild->GetWindow(GW_HWNDNEXT);

	}

	if(!m_pWndCurrentChild)return NULL;
	if(!m_pWndCurrentChild->GetWindow(GW_OWNER)){
		if   (m_pWndCurrentChild->   
			IsKindOf(RUNTIME_CLASS(CMDIChildWnd)))   
		{   
			//   CMDIChildWnd   or   a   derived   class.   
			return   (CMDIChildWnd*)m_pWndCurrentChild;   
		}   
		else   
		{   
			//   Window   is   foreign   to   the   MFC   framework.   
			//   Check   the   next   window   in   the   list   recursively.   
			return   GetNextMDIChildWnd();   
		}   
	}else{
		  return   GetNextMDIChildWnd();   
	}
}

int CMainFrame::GetCountCMDIChildWnds()
{
	return 0;
	int   count   =   0;   

	CMDIChildWnd*   pChild   =   GetNextMDIChildWnd();   
	while   (pChild)   
	{   
		count++;   
		pChild   =   GetNextMDIChildWnd();   
	}   
	return   count;  
}

void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//退出时通知程序正常退出。
	if(IDNO ==AfxMessageBox(_T("Exit ProcessManager?"),MB_YESNO))
		return;
	AddBuildinfo(_T("User Exit ProcessManager."));
	if(g_HookFunc_StopHook!=NULL)
	{
		g_HookFunc_StopHook();
	}
	m_ProcessMonitor.StopWork();
	m_ChildProcessMan.StopAllWork();
	CMDIFrameWndEx::OnClose();
}

