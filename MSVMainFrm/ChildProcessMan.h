#pragma once
class CMSVDlg;

typedef struct tag_AttachDlgInfo{
	int		nCurID;
	int     nProcessID;
	CString strExePath;
	CMSVDlg	*pAttachDlg;
	tag_AttachDlgInfo(){
		pAttachDlg =NULL;
		nProcessID = 0;
		nCurID=0;
	}
}AttachDlgInfoData;

class CChildAttachDialogMan
{
public:
	~CChildAttachDialogMan(void);
	CChildAttachDialogMan(void);
	void StartWork(DWORD dwID,CWnd*pParentWnd,BOOL bAlwaysCreateProcess=FALSE);
	void setParentWnd(CWnd *pWnd){m_pParentWnd = pWnd;};
private:
	void CreateChildDlg();
private:
	CWnd *m_pParentWnd;
	//CArray<CMSVDlg*,CMSVDlg*> m_arrAttachDlg;
public:
	void AddToArr(AttachDlgInfoData*pData);
	CArray<AttachDlgInfoData*,AttachDlgInfoData*> m_arrAttachDlgInfoData;
	//CMSVDlg *m_lpAttachDlg[8];
};
