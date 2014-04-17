#include "StdAfx.h"
#include "ChildProcessMan.h"
#include "MSVDlg.h"
void doCopy(TCHAR *pSrcPath,TCHAR *pDestPath,int nSize){
	_tcsncpy(pDestPath,pSrcPath,nSize);
}
void getRealPath(TCHAR * pSrcPath)
{
	TCHAR *pSrcCurPos = pSrcPath;	
	TCHAR * cp = pSrcPath;

	while( *cp++ = *pSrcCurPos++ )
	{
		if(*pSrcCurPos=='\\')pSrcCurPos++;
	}	              

}
CChildAttachDialogMan::CChildAttachDialogMan(void)
{
	CString strExeArr[]={_T("U:\\V5.5(Pro2.3)\\Middle\\binU\\MSVMainAppU.exe"),
		_T("U:\\V5.5(Pro2.3)\\Middle\\binU\\MgAvWriterU.exe")};
	m_arrAttachDlgInfoData.RemoveAll();
	if(0){
		//testData
		for(int i=0;i<2;i++)
		{
			AttachDlgInfoData *lpData = new AttachDlgInfoData;
			lpData->strExePath =  strExeArr[i];
			lpData->pAttachDlg = NULL;

			CMSVDlg*pDlg = new CMSVDlg();
			//CWnd*pPp = (pParentWnd==NULL)?m_pParentWnd:pParentWnd;
			pDlg ->Create(IDD_MSVDLG);
			lpData->pAttachDlg = pDlg;

			AddToArr(lpData);
		}		
	}
	CString strIni;
	strIni=_T("c:\\process.ini");
	int groupCount = GetPrivateProfileInt(_T("group"),_T("count"),0,strIni);
	for (int i=0;i<groupCount;i++)
	{
		//read group INFO
		stGroupInfo *pInfo = new stGroupInfo;
		TCHAR strTemp[255];
		CString strkeyName;
		strkeyName.Format(_T("groupname_%d"),i);
		GetPrivateProfileString(_T("group"),strkeyName,_T(""),strTemp,255,strIni);
		pInfo->nGroupID = i;
		pInfo->strGroupName = strTemp;
		m_mapGroupInfo[i] = pInfo;
	}
	stGroupInfo *pUnKnownGroupInfo = new stGroupInfo;
	pUnKnownGroupInfo->nGroupID = 20140409;//magicNum 组id 不会到这个数吧。
	pUnKnownGroupInfo->strGroupName=_T("UnKnownGroup");
	std::pair<std::map<int,stGroupInfo*>::iterator,bool> retInsertMap
		= m_mapGroupInfo.insert(std::pair<int,stGroupInfo*>(pUnKnownGroupInfo->nGroupID,pUnKnownGroupInfo));

	int processCount = GetPrivateProfileInt(_T("process"),_T("count"),0,strIni);
	BOOL bHadUnKnownGroupInfo=FALSE;
	for (int i=0;i<processCount;i++)
	{
		AttachDlgInfoData *lpData = new AttachDlgInfoData;
		TCHAR strTemp[255];
		CString strAppName;
		strAppName.Format(_T("process_%d"),i);
		GetPrivateProfileString(strAppName,_T("path"),_T(""),strTemp,255,strIni);
		getRealPath(strTemp);
		lpData->strExePath =  strTemp;
		GetPrivateProfileString(strAppName,_T("displayname"),_T(""),strTemp,255,strIni);
		int nGroupID = GetPrivateProfileInt(strAppName,_T("groupID"),pUnKnownGroupInfo->nGroupID,strIni);

		std::map<int ,stGroupInfo*>::iterator it ;
		it = m_mapGroupInfo.find(nGroupID);
		if(it !=m_mapGroupInfo.end())
			lpData->pstGroupInfo =it->second;
		else{
			lpData->pstGroupInfo = pUnKnownGroupInfo;
			bHadUnKnownGroupInfo = TRUE;
		}
		
		lpData->pAttachDlg = NULL;
		CMSVDlg*pDlg = new CMSVDlg();
		pDlg ->Create(IDD_MSVDLG);
		lpData->pAttachDlg = pDlg;
		AddToArr(lpData);
	}
	if(!bHadUnKnownGroupInfo && retInsertMap.second){
		m_mapGroupInfo.erase(retInsertMap.first);
	}

/*
 normal
 [group]
 count=
 groupname_0=
 groupname_1=

 [process]
 count=1

 [process_0]
 path=
 displayname=
 groupname=
 groupID=

 */

}

CChildAttachDialogMan::~CChildAttachDialogMan(void)
{
}


BOOL CChildAttachDialogMan::StartWork( DWORD dwID,CWnd*pParentWnd,CString &strTitle,BOOL bAlwaysCreateProcess/*=FALSE*/ )
{	
	if(dwID>=m_arrAttachDlgInfoData.GetSize())
	{
		return FALSE;
	}

	{
		AttachDlgInfoData*pData = m_arrAttachDlgInfoData.GetAt(dwID);
		if(pData==NULL)return FALSE;
		CMSVDlg*pDlg = pData->pAttachDlg;
		if(pDlg==NULL)
		{
			pDlg = new CMSVDlg();
			CWnd*pPp = (pParentWnd==NULL)?pData->hParentWnd:pParentWnd;
			pDlg ->Create(IDD_MSVDLG,pPp);
			::SetParent(pDlg->m_hWnd,pPp->m_hWnd);
			pDlg->ShowWindow(SW_HIDE);
			pData->pAttachDlg = pDlg;
		}
		if(pDlg)
		{
			CWnd*pPp = (pParentWnd==NULL)?pData->hParentWnd:pParentWnd;

			::SetParent(pDlg->m_hWnd,pPp->m_hWnd);		

			if(!pDlg->IsWindowVisible()||bAlwaysCreateProcess)
			{				
				BOOL bRet = pDlg->AttachExeToWnd(pData->strExePath,pDlg->m_hWnd,bAlwaysCreateProcess);
			//	bRet = pDlg->StartWork(pData->strExePath,bAlwaysCreateProcess);
				if(bRet)
				{
					strTitle= pData->strTitle = pDlg->strTitle;
					pDlg->ShowWindow(SW_SHOW);
					pPp->ShowWindow(SW_SHOW);
					pPp->ActivateTopParent();

					return TRUE;
				}
			}else if(pDlg->IsWindowVisible())
			{
				strTitle= pData->strTitle;
				pPp->ShowWindow(SW_SHOW);
				pPp->ActivateTopParent();
				return TRUE;
			}
		}
	}
	return FALSE;
}


void CChildAttachDialogMan::AddToArr( AttachDlgInfoData*pData )
{
	pData->nCurID = m_arrAttachDlgInfoData.GetSize();
	m_arrAttachDlgInfoData.Add(pData);
}

BOOL CChildAttachDialogMan::ActiveWindow( DWORD dwID )
{
	AttachDlgInfoData*pData = m_arrAttachDlgInfoData.GetAt(dwID);
	if(!pData)return FALSE;
	pData->hFrameWnd->ActivateFrame(SW_SHOWNORMAL);
	pData->pAttachDlg->ShowWindow(SW_SHOWMINIMIZED);
	pData->pAttachDlg->ShowWindow(SW_SHOWNORMAL);
	return TRUE;
}
