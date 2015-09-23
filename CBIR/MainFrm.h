/******************************************************************
文件名：		MainFrm.h
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		程序的MFC框架类，由VS自动生成。
******************************************************************/

#include "FixedSplitterWnd.h"

#include "CBIRFormView.h"
#include "CBIRView.h"

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:
	CFixedSplitter m_wndSplitterFrame;	// 子窗口分割栏对象
	int m_formWidth;					// 左侧Form视图的宽度

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


