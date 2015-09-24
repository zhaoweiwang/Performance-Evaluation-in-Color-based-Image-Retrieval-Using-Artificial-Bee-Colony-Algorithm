/******************************************************************
文件名：		CBIR.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		MFC工程的框架主类， 由VS自动生成。主要负责整个程序框架生命周期的维护与管理。
******************************************************************/
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"

class CCBIRApp : public CWinApp
{
public:
	CCBIRApp();

public:
	/*
	函数名： InitInstance
	功能：	初始化应用程序
	输入：	空
	输出：	空
	*/
	virtual BOOL InitInstance();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCBIRApp theApp;