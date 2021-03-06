
// MSVMainFrmDoc.h : CMSVMainFrmDoc 类的接口
//


#pragma once


class CMSVMainFrmDoc : public CDocument
{
protected: // 仅从序列化创建
	CMSVMainFrmDoc();
	DECLARE_DYNCREATE(CMSVMainFrmDoc)

// 属性
public:
	CString m_strGroupName;
	int		m_nFilePos;
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CMSVMainFrmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};


