
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include <afxcview.h>

#define  EN_CAPFINISH  0x01
#define  EN_TRANSFER   0x02
#define  EN_UPDATEINFO 0x04

typedef struct tag_MSVInfo{
	int     nCardID;
	int     nCtrlPort;
	int     nCardType;
	CString strExePath;
}MSVInfoData;

typedef struct tag_MSVMaterialInfo{
    int     nCureState;
	DWORD   dwTaskId;
	CTime   timeCreateTime;
	DWORD   dwTotalFrame;
	DWORD   dwChunkCount;
	int     nRowCtrlList;    
	TCHAR   szIdxPath[MAX_PATH];
	TCHAR   szTaskName[MAX_PATH];
	TCHAR   szIDXSelfPath[MAX_PATH]; //半路径
	BYTE    *lpDataInfo[4];
	tag_MSVMaterialInfo()
	{
		nCureState  = EN_CAPFINISH;
        dwTaskId     = 0;
		dwTotalFrame = 0;
        dwChunkCount  = 0;
        nRowCtrlList  = -1;
		szIdxPath[0]  = _T('\0');
        szTaskName[0] = _T('\0');
        szIDXSelfPath[0] =_T('\0');
		
		for (int n=0;n<4;n++)
		{
			lpDataInfo[n] = NULL;
		}
	}
}STMSVMaterialInfo,*LPMSVMaterialInfo;

#define MSVINFO_DBCLICK  WM_USER+100

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


