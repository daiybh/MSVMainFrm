// MSVListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "MSVListCtrl.h"


// CMSVListCtrl

IMPLEMENT_DYNAMIC(CMSVListCtrl, CListCtrl)

CMSVListCtrl::CMSVListCtrl()
{

}

CMSVListCtrl::~CMSVListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMSVListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CMSVListCtrl::OnNMDblclk)
END_MESSAGE_MAP()



// CMSVListCtrl 消息处理程序



void CMSVListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
	LVHITTESTINFO lvhti;

	// Clear the subitem text the user clicked on.
	lvhti.pt = pia->ptAction;
	SubItemHitTest(&lvhti);
   
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
	    AfxGetMainWnd()->SendMessage(MSVINFO_DBCLICK,lvhti.iItem,lvhti.iSubItem);
	}
	*pResult = 0;
}
