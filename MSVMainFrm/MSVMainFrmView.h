
// MSVMainFrmView.h : CMSVMainFrmView ��Ľӿ�
//


#pragma once


class CMSVMainFrmView : public CView
{
protected: // �������л�����
	CMSVMainFrmView();
	DECLARE_DYNCREATE(CMSVMainFrmView)

// ����
public:
	CMSVMainFrmDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

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

