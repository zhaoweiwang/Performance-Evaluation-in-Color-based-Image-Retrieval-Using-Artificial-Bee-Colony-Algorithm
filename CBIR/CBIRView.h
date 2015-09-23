/******************************************************************
文件名：		CBIRView.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		多窗口视图下右侧绘制窗口的实现类。对分割窗口中右侧的视图窗口进行控制与管理，这其中包括相应的
窗口的初始化、基于窗口的OpenGL设备的创建与维护，基于视图上的一些UI操作以及相应的操作响应（其中涉及到与数据
库以及View类的交互等）等
******************************************************************/

#pragma once

#include "CBIRDoc.h"
#include <GL/glew.h>
#include "Image.h"
#include "FuncsLib.h"
#include "Canvas.h"
#include "RPResult.h"
#include "BeeColonyAlgo.h"
#include "ImageDsrDlg.h"
#include "RPResultDlg.h"

#include <vector>
using namespace std;

class CCBIRFormView;

class CCBIRView : public CView
{
protected:
	CCBIRView();
	DECLARE_DYNCREATE(CCBIRView)

public:
	CCBIRDoc* GetDocument() const;

public:
	HGLRC m_hRC;						// OpenGL设备上下文对象			
	int m_nGLPixelIndex;				// OpenGL像素模式对象
	CRect m_oldRect;					// 渲染区域标记对象

	CCBIRFormView* mpCBIRFormView;		// 当前视图关联的Form视图对象

	int m_screenWidth , m_screenHeight;	// 窗口的宽、高

	List<Image> mImageList;				// 图像库对应的图片列表

	bool mShowBeeResult;				// 显示结果标记
	List<Image*> mSortedListNormal;		// 常规检索结果列表
	List<Image*> mSortedListBeeColony;	// 蜂群算法检索结果列表

	Image* mpDstImage;					// 目标图像指针

	Canvas mCanvas;						// 绘制图片墙画布对象

	BeeColonyAlgo mBeeColony;			// 蜂群算法对象

	ImageDsrDlg* mpImageDsrDlg;			// 图像特征值绘制对话框对象

	CRPResultDlg* mpRPResultDlg;		// 检索结果RP曲线绘制对象

	bool mIsRetrived;					// 标记当前是否进行了检索操作

public:
	/*
	函数名：	SetWindowPixelFormat
	功能：	设置OpenGL渲染上下文的像素模式
	输入：	参数1：当前窗口的设备DC句柄
	输出：	bool，设置结果成功与否
	*/
	bool SetWindowPixelFormat(HDC hDC);

	/*
	函数名：	CreateRenderContext
	功能：	创建OpenGL渲染设备
	输入：	参数1：当前窗口的设备DC句柄
	输出：	bool，创建结果成功与否
	*/
	bool CreateRenderContext(HDC hDC);

	/*
	函数名：	GetFormViewPointer
	功能：	得到与当前窗口关联的Form窗口的指针
	输入：	空
	输出：	CCBIRFormView*，关联的Form视图对象的指针
	*/
	CCBIRFormView* GetFormViewPointer();

	/*
	函数名：	SetViewOrtho
	功能：	设置当前OpenGL窗口的投影模式
	输入：	参数1、2：当前窗口的宽高
	输出：	空
	*/
	void SetViewOrtho(int width , int height);

	/*
	函数名：	PerformNormRetrieval
	功能：	对当前的图像数据库执行常规的检索操作
	输入：	空
	输出：	double，执行检索操作的耗时
	*/
	double PerformNormRetrieval();

	/*
	函数名：	PerformBeeRetrieval
	功能：	对当前的图像数据库执行蜂群算法的检索操作
	输入：	空
	输出：	double，执行检索操作的耗时
	*/
	double PerformBeeRetrieval();

public:
	/*
	函数名：	InitDatabase
	功能：	初始对图像数据库
	输入：	参数1：图像名称列表
	输出：	空
	*/
	void InitDatabase(vector<string>& imageList);

	/*
	函数名：	LoadDstImage
	功能：	加载指定的图像作为当前检索的目标图像
	输入：	参数1：目标图像的地址；参数2：目标图像的索引；参数3：标记全局或局部路径
	输出：	空
	*/
	void LoadDstImage(char* fileAddress , int index = 0 , bool globalPath = false);

	/*
	函数名：	PerformRetrieval
	功能：	对当前的目标图像在数据库中执行检索操作（包括常规检索和蜂群检索）
	输入：	空
	输出：	空
	*/
	void PerformRetrieval();

	/*
	函数名：	ComputeRPResult
	功能：	计算当前检索后的RP曲线，并将检索结果返回
	输入：	参数1：要返回的检索结果的对象指针；参数2：统计蜂群算法或常规算法
	输出：	空
	*/
	void ComputeRPResult(RPResult* pRPResult , bool beeColony);

	/*
	*/
	void OutputResult();

	/*
	以下为相应的MFC事件处理函数
	*/
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~CCBIRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnPaint();
protected:
	virtual void OnDraw(CDC* /*pDC*/);
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnUpdateShownormal(CCmdUI *pCmdUI);
	afx_msg void OnShownormal();
	afx_msg void OnUpdateShowbeecolony(CCmdUI *pCmdUI);
	afx_msg void OnShowbeecolony();
	afx_msg void OnShowdsr();
	afx_msg void OnRetrieval();
	afx_msg void OnOutputresult();
};

struct threadInfo
{
	bool completed;
	CCBIRView* wndPraent;
};

#ifndef _DEBUG
inline CCBIRDoc* CCBIRView::GetDocument() const
   { return reinterpret_cast<CCBIRDoc*>(m_pDocument); }
#endif

