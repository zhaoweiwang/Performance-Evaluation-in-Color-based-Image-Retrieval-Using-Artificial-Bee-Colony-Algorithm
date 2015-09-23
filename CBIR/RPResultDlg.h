/******************************************************************
文件名：		RPResultDlg.h
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		检索结果的绘制实现类。其中含在RPResult类的成员对象，并使用其中的值
将每次检索的结果以二维曲线的形式进行绘制并反馈。
******************************************************************/
#pragma once

#include "resource.h"
#include "RPResult.h"

class CRPResultDlg : public CDialog
{
	DECLARE_DYNAMIC(CRPResultDlg)

public:
	CRPResultDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRPResultDlg();

	// 对话框数据
	enum { IDD = IDD_RPRESULT };

	RPResult mRPResult;		// 常规检索下的RP结果对象
	RPResult mRPResultBee;	// 蜂群算法检索下的RP结果对象

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();
};
