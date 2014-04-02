
#include "stdafx.h"
#include "ViewTree.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree ��Ϣ�������

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
  	CTreeCtrl* pTreeCtrl = this;

	HTREEITEM hSelect;
	CPoint pt; 
	GetCursorPos(&pt); 
	ScreenToClient(&pt); 
	hSelect = HitTest(pt); 

	if(NULL == hSelect) // ��ֹ���ֲ�����������������
	{
		hSelect = GetSelectedItem();

		if (NULL == hSelect) // ��ֹ��һ�ε�� ���ֲ����������������֣���һ�ε����GetSelectedItem��ֵ��ȥ���ڵ㣩
		{
			hSelect = GetRootItem();
		}
	}
	if( NULL != hSelect )
	{
		HTREEITEM hChildItem = GetChildItem(hSelect);
		if(hChildItem==NULL)
		{
			//CString str = pTreeCtrl->GetItemText(hSelect);

			DWORD dwData = pTreeCtrl->GetItemData(hSelect);        
			((CMainFrame*)AfxGetMainWnd())->StartWork(dwData);
		}
	}
	*pResult = 0;
}

