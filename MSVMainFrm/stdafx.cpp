
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// MSVMainFrm.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


//#include "MainFrm.h"
void AddLog(LPCTSTR lpStrLog)
{
	//((CMainFrame*)AfxGetMainWnd())->AddBuildinfo(lpStrLog);
	AfxGetMainWnd()->SendMessage(WM_USER+102,0x9898,(LPARAM)lpStrLog);
}