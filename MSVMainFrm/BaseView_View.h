#pragma once


// CBaseView_View ��ͼ

class CBaseView_View : public CView
{
	DECLARE_DYNCREATE(CBaseView_View)

protected:
	CBaseView_View();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBaseView_View();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};

