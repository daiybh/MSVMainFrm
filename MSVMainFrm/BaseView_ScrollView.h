#pragma once



// CMainFrm_ScrollView ��ͼ

class CBaseView_ScrollView : public CScrollView
{
	DECLARE_DYNCREATE(CBaseView_ScrollView)

protected:
	CBaseView_ScrollView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBaseView_ScrollView();

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

	DECLARE_MESSAGE_MAP()
};


