#pragma once


// CMSVListCtrl

class CMSVListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMSVListCtrl)

public:
	CMSVListCtrl();
	virtual ~CMSVListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


