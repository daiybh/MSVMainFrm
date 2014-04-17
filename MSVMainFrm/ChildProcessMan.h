#pragma once
class CMSVDlg;
typedef struct tag_GroupInfo{
	CString strGroupName;
	int		nGroupID;
}stGroupInfo;
typedef struct tag_AttachDlgInfo{
	int		nCurID;
	int     nProcessID;
	CString strExePath;
	CString strTitle;//displayName
	CMSVDlg	*pAttachDlg;
	CWnd	*hParentWnd;
	CFrameWnd * hFrameWnd;
	stGroupInfo *pstGroupInfo;
	HTREEITEM  pTreePosItem;//对应树的节点指针
	
	tag_AttachDlgInfo(){
		 pAttachDlg =NULL;
		 hParentWnd = NULL;
		nProcessID = 0;
		nCurID=0;
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
	BOOL StartWork(DWORD dwID,CWnd*pParentWnd,CString &strTitle,BOOL bAlwaysCreateProcess=FALSE);
	BOOL ActiveWindow(DWORD dwID);
private:
private:
	//CArray<CMSVDlg*,CMSVDlg*> m_arrAttachDlg;
public:
	void AddToArr(AttachDlgInfoData*pData);
	CArray<AttachDlgInfoData*,AttachDlgInfoData*> m_arrAttachDlgInfoData;
	//CArray<stGroupInfo*,stGroupInfo*>	m_arrGroupInfos;
	std::map<int,stGroupInfo*>				m_mapGroupInfo;
	//CMSVDlg *m_lpAttachDlg[8];
};
