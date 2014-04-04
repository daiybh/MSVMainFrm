#pragma once

#include "ChildProcessMan.h"
class CProcessMonitor
{
public:
	CProcessMonitor(void);
	~CProcessMonitor(void);
	static void _MonitorThread_CB(LPVOID para);
	void _MonitorThread();
	void PauseMonitor();
	void ResumeMonitor();
	void StartWork(HWND hMsgWnd,const CArray<AttachDlgInfoData*,AttachDlgInfoData*> *pArr);	
private:
	BOOL _IsProcessExist(CString strProPath,DWORD dwProcessID);
	const CArray<AttachDlgInfoData*,AttachDlgInfoData*> *m_pArrAttachData;
	HANDLE m_hMonitorThread;
	HWND	m_hMsgWnd;
	BOOL  m_bPauseMonitor;
};
