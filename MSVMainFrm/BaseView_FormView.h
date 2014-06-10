
// MSVMainFrmView.h : CMSVMainFrmView ��Ľӿ�
//


#pragma once

#include "MSVMainFrmDoc.h"
#include "Resource.h"
class CBaseView_FormView : public CFormView
{
protected: // �������л�����
	CBaseView_FormView();
	DECLARE_DYNCREATE(CBaseView_FormView)

public:
	enum{ IDD = IDD_MSVMAINFRM_FORM };

// ����
public:
	CMSVMainFrmDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CBaseView_FormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	DECLARE_MESSAGE_MAP()
	LRESULT onResize(WPARAM wParam,LPARAM lParam);
};

#ifndef _DEBUG  // MSVMainFrmView.cpp �еĵ��԰汾
inline CMSVMainFrmDoc* CBaseView_FormView::GetDocument() const
   { return reinterpret_cast<CMSVMainFrmDoc*>(m_pDocument); }
#endif

