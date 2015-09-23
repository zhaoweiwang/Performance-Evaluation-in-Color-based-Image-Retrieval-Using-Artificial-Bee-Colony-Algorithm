/******************************************************************
文件名：		MainFrm.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		程序的MFC框架类，由VS自动生成。
******************************************************************/

#include "stdafx.h"
#include "CBIR.h"

#include "CBIRView.h"
#include "CBIRFormView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX;
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(rect);
	int width, height;
	m_formWidth = 250;
	width = rect.right - rect.left - m_formWidth;
	height = rect.bottom - rect.top;

	if (!m_wndSplitterFrame.CreateStatic(this, 1, 2))
	{
		return false;
	}

	if (!m_wndSplitterFrame.CreateView(0 , 0 , RUNTIME_CLASS(CCBIRFormView) ,  CSize(m_formWidth , 0), pContext))
	{
		return false;
	}

	if (!m_wndSplitterFrame.CreateView(0, 1, RUNTIME_CLASS(CCBIRView),CSize((int)(width * 0.5) , (int)(height * 0.5)), pContext))
	{
		return false;
	}

	CCBIRView* showView;
	CCBIRFormView* formView;
	showView = (CCBIRView*)m_wndSplitterFrame.GetPane(0 , 1);
	formView = (CCBIRFormView*)m_wndSplitterFrame.GetPane(0 , 0);

	showView->mpCBIRFormView = formView;
	formView->mpCBIRView = showView;

	return true;
}
