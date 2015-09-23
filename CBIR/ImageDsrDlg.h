/******************************************************************
文件名：		ImageDsrDlg.h
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		主要用来实现图像特征值在MFC的Dialog控件中的绘制并更新
******************************************************************/
#pragma once

#include "resource.h"
#include "RPResult.h"
#include "Image.h"

class ImageDsrDlg : public CDialog
{
	DECLARE_DYNAMIC(ImageDsrDlg)

public:
	ImageDsrDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ImageDsrDlg();

	// 对话框数据
	enum { IDD = IDD_DSRDLG };

	Image* mpSrcImage;	// 目标图像的指针

public:
	/*
	函数名：	SetSrcImage
	功能：	设置当前特征值绘制的目标图像
	输入：	参数1：目标图像的对象指针
	输出：	空
	*/
	void SetSrcImage(Image* pSrcImage);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();
};
