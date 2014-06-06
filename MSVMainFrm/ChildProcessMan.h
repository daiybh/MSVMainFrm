#pragma once
#include "MSVDlg.h"
typedef struct tag_RectInfo{
	DWORD		nLeft;
	DWORD		nTop;
	DWORD		nWidth;
	DWORD		nHeight;
	int		nCurChildID;
	tag_RectInfo(){
		nTop = nLeft=0;
		nWidth = nHeight =0;
		nCurChildID = 0;
	}
	void GetPos(DWORD &nLeft,DWORD &nTop){
		nLeft = this->nLeft;
		nTop = this->nTop;
	}
	void SetRectInfo(DWORD nLeft,DWORD nTop,DWORD nWidth,DWORD nHeight){
		this->nTop = nTop;
		this->nLeft = nLeft;
		this->nWidth = nWidth;
		this->nHeight = nHeight;
	}
};
#define max_Group_ITems 100
typedef struct tag_RectInfos{
	int n_MaxColumns;//此值可以在加载完配置后读取屏幕宽度，在SetRectInfo的时候自动修正
	DWORD dwTotalWidth;
	DWORD dwTotalHeight;
	tag_RectInfos();
	tag_RectInfo rectInfo[max_Group_ITems];
	void GetPos(int nID,DWORD &nLeft,DWORD &nTop){
		tag_RectInfo *ri =&(rectInfo[nID]);
		ri->GetPos(nLeft,nTop);
	}
	void SetRectInfo(int nID,DWORD nWidth,DWORD nHeight);
private:
	void getTotalInfo(int nID,DWORD &nLeft,DWORD &nTop);
};
typedef struct tag_GroupInfo:public tag_RectInfos{
	CString strGroupName;
	int		nGroupID;
	int		nChildCount;
	int AddRef(){return nChildCount++;}
	tag_GroupInfo(){
		nChildCount =0;
	}

}stGroupInfo;
typedef struct tag_AttachDlgInfo{
	int		nCurID;
	CString strExePath;
	//CString strTitle;//displayName
	CMSVDlg	*pAttachDlg;
	CWnd	*hParentWnd;
	CFrameWnd * hFrameWnd;
	stGroupInfo *pstGroupInfo;
	int			nInGroupPos;
	HTREEITEM  pTreePosItem;//对应树的节点指针
	BOOL IsChildWindowLive(){
		if(this->pAttachDlg->m_hExeWnd==0)return FALSE;
		BOOL bWindow = IsWindow(this->pAttachDlg->m_hExeWnd);
		if(!bWindow)
		{
			this->pAttachDlg->ShowWindow(SW_HIDE);
			//this->strTitle=_T("Null");
			this->pAttachDlg->m_hExeWnd = 0;
			this->pAttachDlg->m_dwProcessId = 0;
		}
		return bWindow;
	}
	CString GetTitle(){return this->pAttachDlg->GetTitle();}
	void UpdateGroupViewScroll()
	{
		SendMessage(this->hFrameWnd->GetActiveView()->m_hWnd,WM_USER+120,pstGroupInfo->dwTotalWidth,pstGroupInfo->dwTotalHeight);
	}
	void ActiveWindow(){
		int nCmdShow = SW_SHOW;
		if (this->hFrameWnd->IsIconic())
		{
			nCmdShow = (SW_SHOWMAXIMIZED);
		}
		this->hFrameWnd->ActivateFrame(nCmdShow);
		UpdateGroupViewScroll();
		this->pAttachDlg->ActiveWindow();
	}
	DWORD GetProcessID(){return pAttachDlg?pAttachDlg->m_dwProcessId:0;}
	
	tag_AttachDlgInfo(){
		 pAttachDlg =NULL;
		 hParentWnd = NULL;
		nCurID=0;
		nInGroupPos =0;
		pstGroupInfo =NULL;
		pTreePosItem = NULL;
		hFrameWnd = NULL;
	}
}AttachDlgInfoData;

#include <map>
class CChildAttachDialogMan
{
public:
	~CChildAttachDialogMan(void);
	CChildAttachDialogMan(void);
	HTREEITEM CreateChildProcess(DWORD dwID,CWnd*pParentWnd,CString &strTitle,BOOL bAlwaysCreateProcess=FALSE);
	BOOL ActiveWindow(DWORD dwID);
	void UpdateGroupFramewnd(int nGroupID,CFrameWnd*pFrameWnd);
private:
private:
	//CArray<CMSVDlg*,CMSVDlg*> m_arrAttachDlg;
public:
	void AddToArr(AttachDlgInfoData*pData);
	void StopAllWork();
	CArray<AttachDlgInfoData*,AttachDlgInfoData*> m_arrAttachDlgInfoData;
	//CArray<stGroupInfo*,stGroupInfo*>	m_arrGroupInfos;
	std::map<int,stGroupInfo*>				m_mapGroupInfo;
	
};
