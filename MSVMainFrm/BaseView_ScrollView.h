#pragma once



// CMainFrm_ScrollView 视图

class CBaseView_ScrollView : public CScrollView
{
	DECLARE_DYNCREATE(CBaseView_ScrollView)

protected:
	CBaseView_ScrollView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBaseView_ScrollView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次

	DECLARE_MESSAGE_MAP()
};


