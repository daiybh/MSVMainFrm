#include "StdAfx.h"
#include "ProcessMonitor.h"

#include "Psapi.h"
#include <tlhelp32.h>
#pragma comment(lib,"Psapi.Lib")
CProcessMonitor::CProcessMonitor(void)
{
	m_bPauseMonitor=FALSE;
}

CProcessMonitor::~CProcessMonitor(void)
{
}
void CProcessMonitor::StartWork(HWND hMsgWnd,const CArray<AttachDlgInfoData*,AttachDlgInfoData*> *pArr)
{
	m_pArrAttachData = pArr;
	m_hMsgWnd = hMsgWnd;
	m_hExitEvent=CreateEvent(NULL,NULL,FALSE,NULL);
	m_hMonitorThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)_MonitorThread_CB, this,NULL,0);	
	m_bPauseMonitor=FALSE;
}
void CProcessMonitor::_MonitorThread_CB( LPVOID para )
{
	CProcessMonitor * pThis = (CProcessMonitor *)para;
	pThis->_MonitorThread();
}

BOOL CProcessMonitor::_IsProcessExist(CString strProPath,DWORD dwProcessID)
{
	TCHAR buff[MAX_PATH];
	CString strTempPath;
	HANDLE hProcess = NULL;
	HANDLE hfindhandle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32* info=new PROCESSENTRY32;
	memset(buff,0,MAX_PATH);
	info->dwSize=sizeof(PROCESSENTRY32);
	strProPath.MakeLower();
	if(Process32First(hfindhandle,info))        
	{
		hProcess=OpenProcess(PROCESS_QUERY_INFORMATION   |   PROCESS_VM_READ,FALSE,info->th32ProcessID);   
		if(hProcess != NULL)  
		{
			GetModuleFileNameEx(hProcess,(HMODULE)info->th32ModuleID,buff,MAX_PATH);
			strTempPath.Format(_T("%s"),buff);
			strTempPath.MakeLower();
			CloseHandle(hProcess);
			hProcess = NULL;
		}
		if((strProPath == strTempPath) )//&& (dwProcessID == info->th32ProcessID))	// && (dwProcessID == info->th32ProcessID)
		{			
			CloseHandle(hfindhandle);
			delete info;
			return TRUE;
		}		
		while(Process32Next(hfindhandle,info)!=FALSE)
		{
			hProcess=OpenProcess(PROCESS_QUERY_INFORMATION   |   PROCESS_VM_READ,FALSE,info->th32ProcessID);   
			if(hProcess != NULL)  
			{
				GetModuleFileNameEx(hProcess,(HMODULE)info->th32ModuleID,buff,MAX_PATH);
				strTempPath.Format(_T("%s"),buff);
				strTempPath.MakeLower();
				CloseHandle(hProcess);
				hProcess = NULL;
			}			
			if((strProPath == strTempPath))// && (dwProcessID == info->th32ProcessID))	// 
			{	
				CloseHandle(hfindhandle);
				delete info;
				return TRUE;
			}
		}			
	}
	CloseHandle(hfindhandle);
	delete info;
	return FALSE;
}
/*
1 检查CChildAttachDialogMan.m_arrAttachDlgInfoData nProcessID strExePath 是否存在。
2  or3 不存在通知出去该节点需要创建
3 not2 不存在 就把该进程创建起来，然后通知出去 attachwnd，这样中间有间断会有程序闪的效果。
*/
#include "ChildProcessMan.h"
void CProcessMonitor::_MonitorThread()
{
	int nPocessNum = m_pArrAttachData->GetSize();
	DWORD m_iMonitorInterval=1000;
	CString strInfo;
	while (1)
	{		
		for (int i=0;i<nPocessNum;i++)
		{
			AttachDlgInfoData *pData = m_pArrAttachData->GetAt(i);
			if (!_IsProcessExist(pData->strExePath,pData->GetProcessID()))
			{	
				//通知出去该节点需要创建进程
				CString notifyStr;
				notifyStr.Format(_T("Process:%s--"),pData->strExePath);
				OutputDebugString(notifyStr);
				//TODO: z这里应该直接调用外部接口，不应该通过消息
				::SendMessage(m_hMsgWnd,WM_USER+102,i,pData->nCurID);
			}
		}
		if (WaitForSingleObject(m_hExitEvent,m_iMonitorInterval) == WAIT_OBJECT_0)
		{
			break;
		}
		nPocessNum = m_pArrAttachData->GetSize();
	}
}

void CProcessMonitor::PauseMonitor()
{
	if(!m_bPauseMonitor)
		SuspendThread(m_hMonitorThread);
	m_bPauseMonitor=true;
}

void CProcessMonitor::ResumeMonitor()
{
	if(m_bPauseMonitor)
		ResumeThread(m_hMonitorThread);

	m_bPauseMonitor=FALSE;
}

void CProcessMonitor::StopWork()
{
	SetEvent(m_hExitEvent);
	DWORD dwRet =WaitForSingleObject(m_hMonitorThread,3000);
	if(dwRet==WAIT_TIMEOUT)
	{
		TerminateThread(m_hMonitorThread,0);
	}
	CloseHandle( m_hMonitorThread);
	m_hMonitorThread = NULL; 
	CloseHandle(m_hExitEvent);
}

