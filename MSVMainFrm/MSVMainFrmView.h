#pragma once
#include "BaseView_FormView.h"
#include "BaseView_ScrollView.h"
#include "BaseView_View.h"
class CMSVMainFrmView:public CBaseView_View
{
public:
	CMSVMainFrmView(void);
	~CMSVMainFrmView(void);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
};
