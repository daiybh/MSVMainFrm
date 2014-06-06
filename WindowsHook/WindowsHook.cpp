// WindowsHook.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "WindowsHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_MYMSG WM_USER + 305 //�Զ�����Ϣ�����ں�������ͨ��

typedef BOOL (CALLBACK *ENCODEDATA_CALLBACKFUNC)(WPARAM wparam,LPARAM lParam, LPVOID pUserData);

//���������ڹ����,�������̹߳������±���;
#pragma data_seg(".SHARED")
static HHOOK  hhkMouse=NULL; //��깳�Ӿ��;
static HINSTANCE g_hInstDll=NULL; //��dll��ʵ�����;
static ENCODEDATA_CALLBACKFUNC g_EncCallBack=NULL;
static LPVOID	g_lpUserData=NULL;
#pragma data_seg()
#pragma comment(linker, "/section:.SHARED,rws")
//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CWindowsHookApp

BEGIN_MESSAGE_MAP(CWindowsHookApp, CWinApp)
END_MESSAGE_MAP()


// CWindowsHookApp ����

CWindowsHookApp::CWindowsHookApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CWindowsHookApp ����

CWindowsHookApp theApp;


// CWindowsHookApp ��ʼ��

BOOL CWindowsHookApp::InitInstance()
{
	CWinApp::InitInstance();

	g_hInstDll=::AfxGetInstanceHandle();
	return TRUE;
}
//�ͼ���깳�ӹ���
LRESULT CALLBACK LowLevelMouseProc(
								   int nCode,      // hook code
								   WPARAM wParam,  // message identifier
								   LPARAM lParam   // mouse coordinates
								   )
{


	//�������Ϣʱ�����䷢��������
	if (g_EncCallBack!=NULL && nCode==HC_ACTION)
	{
		if(g_EncCallBack(wParam,lParam,g_lpUserData))
		{
			return 1;
		}
	}
	return CallNextHookEx(hhkMouse,nCode,wParam,lParam);
}
LRESULT CALLBACK MouseProc(
						   _In_  int nCode,
						   _In_  WPARAM wParam,
						   _In_  LPARAM lParam
						   )
{
	if (g_EncCallBack!=NULL && nCode==HC_ACTION)
	{
		if(g_EncCallBack(wParam,lParam,g_lpUserData))
		{
			return 1;
		}
	}
	return CallNextHookEx(hhkMouse,nCode,wParam,lParam);
}
//��װ�ͼ���깳�ӣ��Ӷ��ػ�ϵͳ���е������Ϣ
BOOL WINAPI StartHookMouse(ENCODEDATA_CALLBACKFUNC pFunc,LPVOID lpUserData)
{
	hhkMouse=::SetWindowsHookEx(WH_MOUSE_LL,LowLevelMouseProc,g_hInstDll,0);
	//hhkMouse=::SetWindowsHookEx(WH_MOUSE,MouseProc,g_hInstDll,0);
	g_EncCallBack = pFunc;
	g_lpUserData = lpUserData;
	if (hhkMouse==NULL)
	{
		return FALSE;
	} 
	else
	{
		return TRUE;
	}
}

//ж�صͼ���깳��
VOID WINAPI StopHookMouse()
{
	if (hhkMouse!=NULL)
	{
		::UnhookWindowsHookEx(hhkMouse);
	}
}