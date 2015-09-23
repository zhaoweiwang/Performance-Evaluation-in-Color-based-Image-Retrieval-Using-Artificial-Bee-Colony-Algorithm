/******************************************************************
文件名：		CBIRView.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		多窗口视图下右侧绘制窗口的实现类。对分割窗口中右侧的视图窗口进行控制与管理，这其中包括相应的
窗口的初始化、基于窗口的OpenGL设备的创建与维护，基于视图上的一些UI操作以及相应的操作响应（其中涉及到与数据
库以及View类的交互等）等
******************************************************************/

#include "stdafx.h"
#include "CBIR.h"
#include "CBIRDoc.h"
#include "CBIRView.h"
#include "MainFrm.h"
#include "Image.h"
#include "Canvas.h"
#include <GL/glew.h>
#include "RPResult.h"
#include "Timer.h"

#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCBIRView, CView)

BEGIN_MESSAGE_MAP(CCBIRView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_SHOWNORMAL, &CCBIRView::OnUpdateShownormal)
	ON_COMMAND(ID_SHOWNORMAL, &CCBIRView::OnShownormal)
	ON_UPDATE_COMMAND_UI(ID_SHOWBEECOLONY, &CCBIRView::OnUpdateShowbeecolony)
	ON_COMMAND(ID_SHOWBEECOLONY, &CCBIRView::OnShowbeecolony)
	ON_COMMAND(ID_SHOWDSR, &CCBIRView::OnShowdsr)
	ON_COMMAND(ID_RETRIEVAL, &CCBIRView::OnRetrieval)
	ON_COMMAND(ID_OUTPUTRESULT, &CCBIRView::OnOutputresult)
END_MESSAGE_MAP()

CCBIRView::CCBIRView()
{
	mpCBIRFormView = NULL;

	mpDstImage = NULL;

	mShowBeeResult = false;

	mpImageDsrDlg = new ImageDsrDlg;
	mpImageDsrDlg->Create(IDD_DSRDLG);

	mpRPResultDlg = new CRPResultDlg;
	mpRPResultDlg->Create(IDD_RPRESULT);

	mIsRetrived = false;
}

CCBIRView::~CCBIRView()
{
	if (mpDstImage)
	{
		delete mpDstImage;
	}

	if (mpImageDsrDlg)
	{
		delete mpImageDsrDlg;
	}

	if (mpRPResultDlg)
	{
		delete mpRPResultDlg;
	}
}

/************************************************************************************
设置OpenGL渲染设备的像素格式。
与OpenGL相关的操作
************************************************************************************/
bool CCBIRView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | 
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER |
		PFD_STEREO_DONTCARE;

	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	m_nGLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if(m_nGLPixelIndex==0)
	{
		m_nGLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_nGLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return FALSE;
		}
	}

	if(SetPixelFormat(hDC,m_nGLPixelIndex,&pixelDesc)==FALSE)
	{
		return FALSE;
	}

	return TRUE;	
}

/************************************************************************************
创建OpenGL渲染设备
与OpenGL相关的操作
************************************************************************************/
bool CCBIRView::CreateRenderContext(HDC hDC)
{
	m_hRC = wglCreateContext(hDC);

	if(m_hRC == NULL)
	{
		return FALSE;
	}

	if(wglMakeCurrent(hDC,m_hRC)==FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCBIRView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CCBIRView::AssertValid() const
{
	CView::AssertValid();
}

void CCBIRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/************************************************************************************
设置当前OpenGL渲染窗口的投影模式
与OpenGL相关的操作
************************************************************************************/
void CCBIRView::SetViewOrtho(int width , int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0 , width , 0 , height , -10.0f , 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0 , 0.0f , 100.0f , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0);
	glShadeModel(GL_SMOOTH);

	mCanvas.SetSize(width , height);
}

void CCBIRView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	//store the size of the screen
	m_screenWidth = cx;
	m_screenHeight = cy;

	if(cy > 0)
	{
		if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
		{
			RedrawWindow();
		}

		m_oldRect.right = cx;
		m_oldRect.bottom = cy;

		SetViewOrtho(cx , cy);

		glDrawBuffer(GL_BACK);
		glEnable(GL_DEPTH_TEST);
	}

	if(mpCBIRFormView)
	{
		mpCBIRFormView->InvalidateRect(NULL , false);
	}

	InvalidateRect(NULL , false);
}

int CCBIRView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();

	if(SetWindowPixelFormat(pDC->m_hDC) == FALSE)
	{
		return 0;
	}

	if(CreateRenderContext(pDC->m_hDC) == FALSE)
	{
		return 0;
	}

	CRect rect;
	GetClientRect(rect);

	SetViewOrtho(rect.Width() , rect.Height());

	glewInit();

	return 0;
}

void CCBIRView::OnDraw(CDC* /*pDC*/)
{

}

BOOL CCBIRView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	TRACE("CCBIRView::OnMouseWheel\n");
	mCanvas.Scroll(zDelta);

	InvalidateRect(NULL , false);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

/************************************************************************************
返回与当前窗口关联Form窗口的指针
************************************************************************************/
CCBIRFormView* CCBIRView::GetFormViewPointer()
{
	return NULL;
}

/************************************************************************************
绘制操作
主要包含一个操作：图片墙画布的绘制
************************************************************************************/
void CCBIRView::OnPaint()
{
	CPaintDC dc(this);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8f , 0.8f , 0.8f , 1.0f);

	glPushMatrix();

	if (mShowBeeResult)
	{
		mCanvas.Draw(mSortedListBeeColony);
	}
	else
	{
		mCanvas.Draw(mSortedListNormal);
	}

	glPopMatrix();

	glFlush();

	SwapBuffers(dc.m_ps.hdc);
}

/************************************************************************************
初始化数据库
应用程序开始执行后首先需要加载所需要的图像库，主要有以下几个操作：
1. 扫描当前应用程序下的图像库目录，并将其中的图像全部添加到图像列表；
2. 将初始化后的图像列表进行加载（包括内存和显存）；
3. 提取图像列表中的所有图像的特征值；
4. 将初始化的图像库加到初始的排序列表中（因未执行检索，因而顺序与原始库中的顺序一致）
************************************************************************************/
void CCBIRView::InitDatabase(vector<string>& imageList)
{
	int testImageNums = imageList.size();
	int i = 0;
	for (vector<string>::iterator ite = imageList.begin() ; ite != imageList.end() ; ite++)
	{
		Image imageItem;
		imageItem.InitImage(ite->c_str() , i);

		if (i < testImageNums)
		mImageList.AddItem(imageItem);

		i++;
	}
	
	// 加载图片库到内存中
	//for(int i = 0 ; i < mImageList.GetListSize() ; ++i)
	for(int i = 0 ; i < testImageNums ; ++i)
	{
		mImageList.GetItemPtr(i)->LoadImage();
	}

	// 提取图片所对应的特征值
	for(int i = 0 ; i < testImageNums ; ++i)
	{
		mImageList.GetItemPtr(i)->ExtractDescriptor();
	}

	// 将图片加入到Sorted List中
	for(int i = 0 ; i < testImageNums ; ++i)
	{
		Image* pImage = mImageList.GetItemPtr(i);
		mSortedListNormal.AddItem(pImage);
		mSortedListBeeColony.AddItem(pImage);
	}
}

/************************************************************************************
加载目标图像
1. 利用参数设置目标图像的属性
2. 加载图像的具体数据（包括OpenGL对象的创建、特征值的提取等）
************************************************************************************/
void CCBIRView::LoadDstImage(char* fileAddress , int index , bool globalPath)
{
	if(fileAddress)
	{
		if (mpDstImage)
		{
			delete mpDstImage;
		}
		mpDstImage = new Image;

		mpDstImage->InitImage(fileAddress , index);

		if (globalPath)
		{
			mpDstImage->LoadOutImage();
		}
		else
		{
			mpDstImage->LoadImage();
		}
		
		mpDstImage->ExtractDescriptor();

		mpImageDsrDlg->SetSrcImage(mpDstImage);
	}
}

/************************************************************************************
执行常规的检索
1. 首先重置渲染画布；
2. 遍历图像库中的每个图像，并将其与目标图像进行特征向量的匹配；
3. 在检索结果列表中，根据相似程序进行排序
这其中为了统计效率，在检索开始前放置计时器，并开始计时；当检索完成之后停止计时器，得到相应的耗时
************************************************************************************/
double CCBIRView::PerformNormRetrieval()
{
	if (mpDstImage)
	{
		CPerfCounter timeCounter;
		timeCounter.Start();

		// 将绘制面板重置
		mCanvas.Reset();

		// 将目标图片与数据库列表中的图片进行一一匹配
		for (unsigned int i = 0 ; i < mImageList.GetListSize() ; ++i)
		{
			mImageList.GetItemPtr(i)->Match(mpDstImage);
		}

		// 清空排序列表
		mSortedListNormal.EmptyList();

		// 对匹配结果按Distance由小到大进行排序（这里使用比较暴力的N*N方法，可以凸显蜂群算法的速度提升^-^）
		double minDistance;
		int minImageIndex;
		for (unsigned int i = 0 ; i < mImageList.GetListSize() ; ++i)
		{
			minDistance = 999999.0f;
			minImageIndex = 0;

			// 遍历以搜索当前最匹配度最高（距离最小）的图片，并对其进行标记以避免重复搜索
			for (unsigned int j = 0 ; j < mImageList.GetListSize() ; ++j)
			{
				if(mImageList.GetItemPtr(j)->IsFlagged() == false)
				{
					if (mImageList.GetItemPtr(j)->GetDistance() < minDistance)
					{
						minImageIndex = j;
						minDistance = mImageList.GetItemPtr(j)->GetDistance();
					}
				}
			}

			// 将当前最相近的图片加入到列表中，并修改其标记值（该值会有每次Match操作时重置）
			Image* pImage = mImageList.GetItemPtr(minImageIndex);
			mSortedListNormal.AddItem(pImage);
			mImageList.GetItemPtr(minImageIndex)->SetFlagged();

			TRACE("Distance: %f\n" , minDistance);
		}

		InvalidateRect(NULL , FALSE);

		timeCounter.Stop();

		return timeCounter.GetElapsedTime();
	}

	return 0.0;
}

/************************************************************************************
执行常规的检索
1. 首先重置渲染画布；
2. 使用蜂群检索算法对象（BeeColonyAlgo）来执行检索操作
其中的检索结果排序等相关的操作均由蜂群算法对象来维护。这其中为了统计效率，在检索开始前放置计时器，
并开始计时；当检索完成之后停止计时器，得到相应的耗时
************************************************************************************/
double CCBIRView::PerformBeeRetrieval()
{
	if (mpDstImage)
	{
		CPerfCounter timeCounter;
		timeCounter.Start();

		// 将绘制面板重置
		mCanvas.Reset();

		mBeeColony.PerformRetrieval(mpDstImage , mImageList , mSortedListBeeColony);

		InvalidateRect(NULL , FALSE);

		timeCounter.Stop();
		return timeCounter.GetElapsedTime();
	}

	return 0.0;
}

/************************************************************************************
计算检索结果的RP曲线
************************************************************************************/
void CCBIRView::ComputeRPResult(RPResult* pRPResult , bool beeColony)
{
	if (pRPResult)
	{
		if (beeColony)
		{
			pRPResult->ComputeRP(mpDstImage->GetImageIndex() , mSortedListBeeColony);
		}
		else
		{
			pRPResult->ComputeRP(mpDstImage->GetImageIndex() , mSortedListNormal);
		}
	}
}

/************************************************************************************
消息响应函数，更新程序菜单
************************************************************************************/
void CCBIRView::OnUpdateShownormal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!mShowBeeResult);
}

/************************************************************************************
消息响应函数，更新程序菜单
************************************************************************************/
void CCBIRView::OnShownormal()
{
	// TODO: Add your command handler code here
	mShowBeeResult = false;

	InvalidateRect(NULL , false);
}

/************************************************************************************
消息响应函数，更新程序菜单
************************************************************************************/
void CCBIRView::OnUpdateShowbeecolony(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(mShowBeeResult);
}

/************************************************************************************
消息响应函数，更新程序菜单
************************************************************************************/
void CCBIRView::OnShowbeecolony()
{
	// TODO: Add your command handler code here
	mShowBeeResult = true;

	InvalidateRect(NULL , false);
}

/************************************************************************************
消息响应函数，更新程序菜单
************************************************************************************/
void CCBIRView::OnShowdsr()
{
	// TODO: Add your command handler code here
	mpImageDsrDlg->ShowWindow(SW_SHOW);
}

/************************************************************************************
按键响应函数
执行检索按钮所触发的检索操作，其内部会同时执行两个检索操作：
1. 常规检索
2. 蜂群检索
************************************************************************************/
void CCBIRView::PerformRetrieval()
{
	if(mpDstImage == NULL)
	{
		MessageBoxA("请先选中目标图片！" , "提示" , MB_OK);
		return;
	}

	// 加上变量判断，防止智能优化算法丢失解的情况出现
	bool isValidResult;

	// 执行常规的遍历搜索
	isValidResult = false;
	while(isValidResult == false)
	{
		mpRPResultDlg->mRPResult.mUsedTime = (float)PerformNormRetrieval();
		ComputeRPResult(&(mpRPResultDlg->mRPResult) , false);
		isValidResult = mpRPResultDlg->mRPResult.mbIsValid;
	}

	// 执行蜂群搜索
	isValidResult = false;
	while(isValidResult == false)
	{
		mpRPResultDlg->mRPResultBee.mUsedTime = (float)PerformBeeRetrieval();
		ComputeRPResult(&(mpRPResultDlg->mRPResultBee) , true);
		isValidResult = mpRPResultDlg->mRPResultBee.mbIsValid;
	}

	mpRPResultDlg->InvalidateRect(NULL , true);

	mIsRetrived = true;
}

/************************************************************************************
消息响应函数
************************************************************************************/
void CCBIRView::OnRetrieval()
{
	// TODO: Add your command handler code here
	PerformRetrieval();
}

void CCBIRView::OutputResult()
{
	if (mpDstImage == NULL || 
		mIsRetrived == false)
	{
		return;
	}

	ofstream outFile;

	char fileName[32];
	sprintf_s(fileName , sizeof(char) * 32 , "检索结果_%d.txt" , mpDstImage->GetImageIndex());
	outFile.open(fileName);

	/** 输出常规检索的结果 **/
	outFile<<"常规检索"<<endl;
	{
		// 输出检索结果中的模型顺序，输出前100个图像即可
		outFile<<"Index: ";
		for(int i = 0 ; i < 100 ; ++i)
		{
			outFile<<(*mSortedListNormal.GetItemPtr(i))->GetImageIndex()<<" ";
		}
		outFile<<endl;

		// 输出检索结果中的PR结果
		mpRPResultDlg->mRPResult.OutputResult(outFile);
	}
	
	/** 输出蜂群检索的结果 **/
	outFile<<"蜂群检索"<<endl;
	{
		// 输出检索结果中的模型顺序，输出前100个图像即可
		outFile<<"图像列表：";
		for(int i = 0 ; i < 100 ; ++i)
		{
			outFile<<(*mSortedListBeeColony.GetItemPtr(i))->GetImageIndex()<<" ";
		}
		outFile<<endl;

		// 输出检索结果中的PR结果
		mpRPResultDlg->mRPResultBee.OutputResult(outFile);
	}

	outFile.close();
}


void CCBIRView::OnOutputresult()
{
	// TODO: Add your command handler code here
	OutputResult();
}
