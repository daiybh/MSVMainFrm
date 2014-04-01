
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
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
	TCHAR   szIDXSelfPath[MAX_PATH]; //��·��
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


