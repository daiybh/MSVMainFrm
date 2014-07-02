#pragma once



// CMSVMainFrmView_Base_ScrollView ��ͼ

class CMSVMainFrmView_Base_ScrollView : public CScrollView
{
	DECLARE_DYNCREATE(CMSVMainFrmView_Base_ScrollView)

protected:
	CMSVMainFrmView_Base_ScrollView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMSVMainFrmView_Base_ScrollView();

	// ����
public:
	CMSVMainFrmDoc* GetDocument() const;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

	LRESULT onResize(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // MSVMainFrmView.cpp �еĵ��԰汾
inline CMSVMainFrmDoc* CMSVMainFrmView_Base_ScrollView::GetDocument() const
{ return reinterpret_cast<CMSVMainFrmDoc*>(m_pDocument); }
#endif

