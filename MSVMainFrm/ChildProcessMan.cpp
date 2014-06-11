#include "StdAfx.h"
#include "ChildProcessMan.h"
void doCopy(TCHAR *pSrcPath,TCHAR *pDestPath,int nSize){
	_tcsncpy(pDestPath,pSrcPath,nSize);
}
void getRealPath(TCHAR * pSrcPath)
{
	TCHAR *pSrcCurPos = pSrcPath;	
	TCHAR * cp = pSrcPath;

	BOOL bFind=FALSE;
	TCHAR *pFindPos=NULL;
	while( *cp++ = *pSrcCurPos++ )
	{
		if(*pSrcCurPos=='\\')
		{
			if(pFindPos==pSrcCurPos-1)
				pSrcCurPos++;
			else
			{
				pFindPos=pSrcCurPos;
			}
		}
	}	              

}
CChildAttachDialogMan::CChildAttachDialogMan(void)
{
	m_arrAttachDlgInfoData.RemoveAll();
	CString strIni;
	TCHAR strModuleFileName[MAX_PATH];
	TCHAR strDriver[MAX_PATH];
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strModuleFileName,MAX_PATH);
	_tsplitpath_s(strModuleFileName, strDriver,_countof(strDriver), strPath,_countof(strPath),NULL,0,NULL,0);
	_tcscat_s(strDriver,_countof(strDriver),strPath);
	_tcscat_s(strDriver,_countof(strDriver),_T("process.ini"));  
	strIni=strDriver;
	int groupCount = GetPrivateProfileInt(_T("group"),_T("count"),0,strIni);
	int nMaxColumns = GetPrivateProfileInt(_T("group"),_T("maxColumn"),0,strIni);
	if(nMaxColumns<1)nMaxColumns = 3;
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
		pInfo->n_MaxColumns = nMaxColumns;
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
		TCHAR strTemp[255];
		CString strAppName;
		strAppName.Format(_T("process_%d"),i);
		GetPrivateProfileString(strAppName,_T("path"),_T(""),strTemp,255,strIni);
		//这里需要去掉路径中的多余斜杠
		getRealPath(strTemp);
		CString strExePath(strTemp);
		if(strExePath.IsEmpty() || strExePath.GetLength()<3)//c:\1.exe
		{		
			continue;
		}

		GetPrivateProfileString(strAppName,_T("displayname"),_T(""),strTemp,255,strIni);
		int nGroupID = GetPrivateProfileInt(strAppName,_T("groupID"),pUnKnownGroupInfo->nGroupID,strIni);

		AttachDlgInfoData *lpData = new AttachDlgInfoData;

		lpData->strExePath =  strExePath;

		std::map<int ,stGroupInfo*>::iterator it ;
		it = m_mapGroupInfo.find(nGroupID);
		if(it !=m_mapGroupInfo.end())
			lpData->pstGroupInfo =it->second;
		else{
			lpData->pstGroupInfo = pUnKnownGroupInfo;
			bHadUnKnownGroupInfo = TRUE;
		}
		lpData->nInGroupPos = lpData->pstGroupInfo->AddRef();
		
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
void CChildAttachDialogMan::StopAllWork()
{
	for(int i=0;i<m_arrAttachDlgInfoData.GetSize();i++)
	{
		AttachDlgInfoData*pData = m_arrAttachDlgInfoData.GetAt(i);
		pData->pAttachDlg->CloseDlg(TRUE);
	}
}
HTREEITEM CChildAttachDialogMan::CreateChildProcess( DWORD dwID,CWnd*pParentWnd,CString &strTitle,BOOL bAlwaysCreateProcess/*=FALSE*/ )
{	
	if(dwID>=m_arrAttachDlgInfoData.GetSize())
	{
		return NULL;
	}
	AttachDlgInfoData*pData = m_arrAttachDlgInfoData.GetAt(dwID);
	if(pData==NULL)return NULL;
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
		BOOL bShowWindow=FALSE;
		if(!pDlg->IsWindowVisible()||bAlwaysCreateProcess)
		{			
			//获取组的下一个 left top位置

// 			pDlg->m_dwLeft = pData->pstGroupInfo->nNextLeft;
// 			pDlg->m_dwTop = pData->pstGroupInfo->nNextTop;
			//pData->pstGroupInfo->GetNextPos(pDlg->m_dwLeft,pDlg->m_dwTop);
			pData->pstGroupInfo->GetPos(pData->nInGroupPos,pDlg->m_dwLeft,pDlg->m_dwTop);
			BOOL bRet = pDlg->AttachExeToWnd(pData->strExePath,pDlg->m_hWnd,bAlwaysCreateProcess);
			if(bRet)
			{
				strTitle= pDlg->GetTitle();
				bShowWindow = TRUE;
				//AddLog
				CString strLog;
				strLog.Format(_T("StartWork ret=%d id=%d--title[%s] path[%s] exeWnd=%x"),bRet,dwID,strTitle,pData->strExePath,pDlg->m_hExeWnd);
				AddLog(strLog);
				{
					//获取PDG的width height
					;;
					//更新group的next top left
					//pData->pstGroupInfo->AddRectInfo(pDlg->m_dwWidth,pDlg->m_dwHeight);		
					pData->pstGroupInfo->SetRectInfo(pData->nInGroupPos,pDlg->m_dwWidth,pDlg->m_dwHeight);
				}
			}
		}
		else if(pDlg->IsWindowVisible())
		{
			bShowWindow = TRUE;
		}
		if(bShowWindow)
		{
			pDlg->ShowWindow(SW_SHOW);
			pPp->ShowWindow(SW_SHOW);
			pPp->ActivateTopParent();

			return pData->pTreePosItem;
		}

	}
	return NULL;
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
	pData->ActiveWindow();
	return TRUE;
}

void CChildAttachDialogMan::UpdateGroupFramewnd( int nGroupID,CFrameWnd*pFrameWnd )
{
	for (int i=0;i<m_arrAttachDlgInfoData.GetCount();i++)
	{
		AttachDlgInfoData *pData = m_arrAttachDlgInfoData.GetAt(i);
		if(nGroupID==0x8888)
		{
			//收到view窗口还原，最大化消息，此时通知view更新他的scroll
			if(pData->hFrameWnd == pFrameWnd){
				pData->ActiveWindow();
			}
		}
		else
		{
			if(pData->pstGroupInfo)				
			{
				if(pData->pstGroupInfo->nGroupID == nGroupID){
					pData->hParentWnd = pFrameWnd->GetActiveView();
					pData->hFrameWnd = pFrameWnd;
				}
			}else{//unknown docView
				pData->hParentWnd =AfxGetMainWnd();
			}
		}
	}
}

void tag_RectInfos::getTotalInfo( int nID,DWORD &nLeft,DWORD &nTop )
{
	nLeft = nTop = 0;
	if(nID>=n_MaxColumns){
		for (int i=nID;i>=0;i-=n_MaxColumns)
		{
			tag_RectInfo *ri = &(rectInfo[i]);
			nTop += (ri->nHeight);
			nLeft = ri->nLeft;
		}
	}
	else{
		//在第一行内
		tag_RectInfo *ri = &(rectInfo[0]);
		nTop = ri->nTop;
		nLeft = (ri->nWidth);
		for(int i=1;i<nID;i++)
		{
			ri = &(rectInfo[i]);
			nLeft+= (ri->nWidth);
		}
	}
}

void tag_RectInfos::SetRectInfo( int nID,DWORD nWidth,DWORD nHeight )
{
	//需要计算
	tag_RectInfo *ri =&(rectInfo[nID]);
	DWORD nLeft,nTop;
	getTotalInfo(nID,nLeft,nTop);
	ri->SetRectInfo(nLeft,nTop,nWidth,nHeight);
	dwTotalWidth = nWidth+nLeft;
	dwTotalHeight =nHeight+nTop;
	dwTotalHeight *=2;
	dwTotalWidth *=2;

	ri =&(rectInfo[nID+1]);
	getTotalInfo(nID+1,nLeft,nTop);
	ri->SetRectInfo(nLeft,nTop,nWidth,nHeight);	
}

tag_RectInfos::tag_RectInfos()
{
	n_MaxColumns = 3;
	dwTotalWidth = dwTotalHeight = 0;
}
