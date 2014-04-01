
// MSVMainFrmView.h : CMSVMainFrmView ��Ľӿ�
//


#pragma once

#include "MSVDlg.h"
class CMSVMainFrmView : public CFormView,CCreateProcessWnd
{
protected: // �������л�����
	CMSVMainFrmView();
	DECLARE_DYNCREATE(CMSVMainFrmView)

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
	virtual ~CMSVMainFrmView();
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
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MSVMainFrmView.cpp �еĵ��԰汾
inline CMSVMainFrmDoc* CMSVMainFrmView::GetDocument() const
   { return reinterpret_cast<CMSVMainFrmDoc*>(m_pDocument); }
#endif

