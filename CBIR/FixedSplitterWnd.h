/******************************************************************
文件名：		FixedSplitterWnd.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		MFC中对于窗口分割类的实现。其主要功能是对于MFC结构中的View视图进行分割，
以便得到左侧的控制栏（FormView）、右侧的绘制栏（View）。这样可以在左侧添加相应的UI控件，
而在右侧进行相应的图片绘制等实现。
******************************************************************/

#if !defined(AFX_FIXEDSPLITTER_H__9DB2BF9B_1C2E_483F_985E_FC38AB087B05__INCLUDED_)   
#define AFX_FIXEDSPLITTER_H__9DB2BF9B_1C2E_483F_985E_FC38AB087B05__INCLUDED_   
    
#if _MSC_VER > 1000   
#pragma once   
#endif
    
class CFixedSplitter : public CSplitterWnd   
{
public:   
	CFixedSplitter();
    
public:   
	virtual ~CFixedSplitter();
protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);   
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);   
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()   
};   

#endif