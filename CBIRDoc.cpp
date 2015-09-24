/******************************************************************
文件名：		CBIRDoc.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		MFC工程的文档主类， 由VS自动生成。主要负责应用程序中相关文档的序列化等操作
******************************************************************/

#include "stdafx.h"
#include "CBIR.h"

#include "CBIRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCBIRDoc, CDocument)

BEGIN_MESSAGE_MAP(CCBIRDoc, CDocument)
END_MESSAGE_MAP()

CCBIRDoc::CCBIRDoc()
{

}

CCBIRDoc::~CCBIRDoc()
{
}

/************************************************************************************
调用MFC的库函数来打开新的文档。
************************************************************************************/
BOOL CCBIRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}
/************************************************************************************
调用MFC的库函数来序列化当前活动的文档。
************************************************************************************/
void CCBIRDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{

	}
}

#ifdef _DEBUG
void CCBIRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCBIRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif