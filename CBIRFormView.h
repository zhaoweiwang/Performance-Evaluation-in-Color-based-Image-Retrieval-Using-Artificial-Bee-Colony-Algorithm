/******************************************************************
文件名：		CBIRFormView.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		多窗口视图下左侧控制栏的Form面板视图的实现类。对分割窗口中左侧的Form窗口进行控制与管理，这其中包括相应的
UI控件，及相应的操作响应（其中涉及到与数据库以及View类的交互等）
******************************************************************/

#pragma once
#include "afxcmn.h"

#include "RPResultDlg.h"

class CCBIRView;
class COperationDlg;

class CCBIRFormView : public CFormView
{
	DECLARE_DYNCREATE(CCBIRFormView)

private:
	int mWidth , mHeight;	// Form视图的宽和高

public:	
	HTREEITEM m_allRoot;	// 树状控件相对应的对象
	HTREEITEM m_curRoot;

	CCBIRView* mpCBIRView;	// 关联的右侧绘制视图的指针

	CTreeCtrl mImageDBTree;	// 树状MFC控件对象

	LPPICTURE mpImagePPI;	// GDI绘图对象，用来绘制左侧视图中的预览图像框

	int mSelectedIndex;		// 当前选中的图像对象的索引，在进行检索时用来攻取对应的目标图像

public:
	/*
	函数名：	GetViewPointer
	功能：	获取与当前Form视图相关联的右侧绘制视图的对象指针
	输入：	空
	输出：	绘制视图的指针
	*/
	CCBIRView* GetViewPointer();

	/*
	函数名：	AddFile
	功能：	添加新的图像对象到当前的数据库列表中
	输入：	参数1：新对象对应的ID（由外部自增变量控制）；参数2：新对象的名字
	输出：	空
	*/
	void AddFile(int index , CString& fileName);

private:
	/*
	函数名： ScanDatabase
	功能：	在初始化时调用，用来扫描当前应用程序目录下的图像库文件夹，并将其中的图像全部添加到程序图像库内存中
	输入：	空
	输出：	空
	*/
	void ScanDatabase();

	/*
	函数名：	GetSelectedItemIndex
	功能：	得到当前左侧树状浏览控件中选中的图像对像的索引值，该索引值用来加载对应的图像以及进行图像分类等
	输入：	树状控件中被选中的子项
	输出：	选中的图像对象的索引
	*/
	int GetSelectedItemIndex(TVITEM& selectedItem);

protected:
	CCBIRFormView();
	virtual ~CCBIRFormView();

public:
	enum { IDD = IDD_CBIRFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	/*
	函数名：	OnInitalUpdate
	功能：	在初次创建FormView之后调用该函数以完成面板上相应控件的更新，来自于重载的基类
	输入：	空
	输出：	空
	*/
	virtual void OnInitialUpdate();

	/*
	以下函数均为MFC中的消息响应函数，相应的功能与实现可以从名字中读出
	*/
public:
	afx_msg void OnTcnSelchangeOperationtab(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedOpenmodeldb();
public:
	afx_msg void OnTvnSelchangedModeldbtree(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRetriveimage();
	afx_msg void OnBnClickedPrresult();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnUpdateShownormal(CCmdUI *pCmdUI);
	afx_msg void OnShownormal();
	afx_msg void OnUpdateShowbeecolony(CCmdUI *pCmdUI);
	afx_msg void OnShowbeecolony();
	afx_msg void OnShowdsr();
	afx_msg void OnRetrieval();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOutputresult();
	afx_msg void OnOutputresult();
};


