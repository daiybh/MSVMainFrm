
// MSVMainFrmDoc.h : CMSVMainFrmDoc ��Ľӿ�
//


#pragma once


class CMSVMainFrmDoc : public CDocument
{
protected: // �������л�����
	CMSVMainFrmDoc();
	DECLARE_DYNCREATE(CMSVMainFrmDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMSVMainFrmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


