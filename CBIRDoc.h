/******************************************************************
文件名：		CBIRDoc.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		MFC工程的文档主类， 由VS自动生成。主要负责应用程序中相关文档的序列化等操作。
******************************************************************/

#pragma once

class CCBIRDoc : public CDocument
{
protected: 
	CCBIRDoc();
	DECLARE_DYNCREATE(CCBIRDoc)

public:

public:

public:
	/*
	函数名：		OnNewDocument
	功能：		打开新的外部文件
	输入：		空
	输出：		BOOL类型，初始化的结果是否成功
	*/
	virtual BOOL OnNewDocument();

	/*
	函数名：		Serialize
	功能：		以序列化的形式保存当前的文档
	输入：		空
	输出：		空
	*/
	virtual void Serialize(CArchive& ar);

public:
	virtual ~CCBIRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


