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
	CRect rect;
	GetClientRect(rect);
    m_hExeWnd=CreateProcessEx(m_strExePath,rect);

	if(m_hExeWnd == NULL)
	{
		return FALSE;
	}
	CWnd *cWnd=CWnd::FromHandle(m_hExeWnd);
     //���ر�����
	cWnd->ModifyStyle(WS_CAPTION,0);
	//���ر߿�
	cWnd->ModifyStyle(WS_THICKFRAME,1);

	m_bIsLoad = TRUE;
	AdjustLayout();

	//MoveWindow(m_exeRect.left,m_exeRect.top,m_exeRect.Width(),m_exeRect.Height());
	//��ʾ�Ի���
    ::SetParent(m_hExeWnd,m_hWnd);

	return TRUE;
}
// CMSVDlg ��Ϣ�������
HWND CMSVDlg::GetWndByPID(DWORD dwProcessID)  
{  
	HWND hWnd = NULL;
	DWORD dwPID,dwThreadID;  
	HWND hParentWnd;   
	HWND hOldWnd = NULL;
	//��ȡ�����б��еĵ�һ������  
	CWnd *pWnd = FindWindow( NULL, NULL );  
	//���������б�  
	while( NULL != pWnd )  
	{  
		//ͨ�����ھ��m_hWnd��ȡ����PID  
		dwThreadID = GetWindowThreadProcessId( pWnd->GetSafeHwnd(), &dwPID );  
		if( 0 != dwThreadID && dwProcessID == dwPID )  
		{  
			hParentWnd = ::GetParent(pWnd->GetSafeHwnd());  
			TCHAR szText[MAX_PATH] = {0};  
			::GetWindowText(hParentWnd , szText ,MAX_PATH); 

			if (::IsWindowVisible(hParentWnd))  
			{  
				while (hParentWnd)  
				{  
					//ȡ����㴰��  
					hWnd = hParentWnd;  
					hParentWnd = ::GetParent(hWnd);  
					if (!(::IsWindowVisible(hParentWnd)))  
					{  
						break;  
					}  
				}  
				if (szText[0] != 0 )  
				{  
					break;  
				}  
			}  
			else if (wcscmp(szText,_T("")) == 0) //����Ѿ�SW_HIDE,�����ϲ�ľ��
			{
				hWnd = hOldWnd;
				break;
			}
			hOldWnd = hParentWnd;
		}  
		pWnd = pWnd->GetNextWindow();  
	}  
	return hWnd;
}  
HWND CMSVDlg::CreateProcessEx(CString strExePath,CRect &rect)
{
	HWND  hExeWnd = NULL;
	STARTUPINFO sa = {0};
	sa.cb = sizeof(STARTUPINFO);
	sa.dwX= rect.left;
	sa.dwY= rect.top;
	sa.dwXSize=rect.Width();
	sa.dwYSize=rect.Height();
	sa.wShowWindow=SW_HIDE;
	sa.dwFlags=STARTF_USEPOSITION | STARTF_USESIZE;            //�O���˴�������λ�ã����ڴ�С��־λ��Ч�����ǽ���
   

	PROCESS_INFORMATION pi = {0};
	if(CreateProcess(strExePath,NULL,NULL,NULL,\
		FALSE,CREATE_NEW_PROCESS_GROUP,NULL,NULL,&sa,&pi))
	{
		if(WaitForInputIdle(pi.hProcess,INFINITE) == 0)
		{
			hExeWnd = GetWndByPID(pi.dwProcessId);                //ͨ�^GetWindowThreadProcessId()�Ա� dwPid,�ܳɹ������Ƿ��صĴ��ھ�� ��HWND)�����õ������ ::SetWindowText(hWnd,_T("1111111"));�o���O�ô��ژ��}
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);                                     
		}
	}
	return hExeWnd;
}
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
	// TODO: �ڴ˴������Ϣ����������
}
