
// stdafx.cpp : 只包括标准包含文件的源文件
// MSVMainFrm.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


//#include "MainFrm.h"
void AddLog(LPCTSTR lpStrLog)
{
	//((CMainFrame*)AfxGetMainWnd())->AddBuildinfo(lpStrLog);
	AfxGetMainWnd()->SendMessage(WM_USER+102,0x9898,(LPARAM)lpStrLog);
}