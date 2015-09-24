/******************************************************************
文件名：		FixedSplitterWnd.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		MFC中对于窗口分割类的实现。其主要功能即是对于MFC结构中的View视图进行分割，
以便得到左侧的控制栏（FormView）、右侧的绘制栏（View）。这样可以在左侧添加相应的UI控件，
而在右侧进行相应的图片绘制等实现。
******************************************************************/

#include "stdafx.h"
#include "FixedSplitterWnd.h"
    
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFixedSplitter::CFixedSplitter()   
{
	m_cxSplitter = 3;
	m_cySplitter = 3;
	m_cxSplitterGap = 3;
	m_cySplitterGap = 3;
}

CFixedSplitter::~CFixedSplitter()   
{

}

BEGIN_MESSAGE_MAP(CFixedSplitter, CSplitterWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_SIZE() 
END_MESSAGE_MAP()

void CFixedSplitter::OnMouseMove(UINT nFlags, CPoint point)     
{
	CWnd::OnMouseMove(nFlags, point);   
}

void CFixedSplitter::OnLButtonDown(UINT nFlags, CPoint point)     
{
	CWnd::OnLButtonDown(nFlags, point);   
}

BOOL CFixedSplitter::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnSetCursor(pWnd, nHitTest, message);   
}

void CFixedSplitter::OnSize(UINT nType, int cx, int cy)
{
	CSplitterWnd::OnSize(nType, cx, cy);
}