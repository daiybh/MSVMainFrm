#pragma once
class CMSVDlg;
class CChildAttachDialogMan
{
public:
	~CChildAttachDialogMan(void);
	CChildAttachDialogMan(void);
	void StartWork(DWORD dwItmeData);
	void setParentWnd(CWnd *pWnd){m_pParentWnd = pWnd;};
private:
	void CreateChildDlg(int nChanCount);
private:
	CWnd *m_pParentWnd;
	CMSVDlg *m_lpAttachDlg[8];
};
