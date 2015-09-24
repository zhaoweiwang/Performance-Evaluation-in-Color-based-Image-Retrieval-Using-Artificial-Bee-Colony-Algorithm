/******************************************************************
文件名：		CBIRFormView.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		多窗口视图下左侧控制栏的Form面板视图的实现类。对分割窗口中左侧的Form窗口进行控制与管理，这其中包括相应的
UI控件，及相应的操作响应（其中涉及到与数据库以及View类的交互等）
******************************************************************/

#include "stdafx.h"
#include "CBIR.h"
#include "CBIRFormView.h"
#include "MainFrm.h"
#include "FuncsLib.h"
#include "RPResultDlg.h"
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

IMPLEMENT_DYNCREATE(CCBIRFormView, CFormView)

CCBIRFormView::CCBIRFormView() : CFormView(CCBIRFormView::IDD)
{
	mpImagePPI = NULL;
	mSelectedIndex = 0;
}

CCBIRFormView::~CCBIRFormView()
{
	if(mpImagePPI)
	{
		mpImagePPI->Release();
	}
}

/************************************************************************************
MFC控件对象的成员方法，主要实现控件数据的更新
************************************************************************************/
void CCBIRFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODELDBTREE, mImageDBTree);
}

BEGIN_MESSAGE_MAP(CCBIRFormView, CFormView)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MODELDBTREE, &CCBIRFormView::OnTvnSelchangedModeldbtree)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RETRIVEIMAGE, &CCBIRFormView::OnBnClickedRetriveimage)
	ON_BN_CLICKED(IDC_PRRESULT, &CCBIRFormView::OnBnClickedPrresult)
	ON_UPDATE_COMMAND_UI(ID_SHOWNORMAL, &CCBIRFormView::OnUpdateShownormal)
	ON_COMMAND(ID_SHOWNORMAL, &CCBIRFormView::OnShownormal)
	ON_UPDATE_COMMAND_UI(ID_SHOWBEECOLONY, &CCBIRFormView::OnUpdateShowbeecolony)
	ON_COMMAND(ID_SHOWBEECOLONY, &CCBIRFormView::OnShowbeecolony)
	ON_COMMAND(ID_SHOWDSR, &CCBIRFormView::OnShowdsr)
	ON_COMMAND(ID_RETRIEVAL, &CCBIRFormView::OnRetrieval)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_OUTPUTRESULT, &CCBIRFormView::OnBnClickedOutputresult)
	ON_COMMAND(ID_OUTPUTRESULT, &CCBIRFormView::OnOutputresult)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CCBIRFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCBIRFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

/************************************************************************************
使用GDI绘图的方法来加载外部的JPG对象，并用来实现图像预览显示的实现。
************************************************************************************/
bool LoadMyJpegFile(CString fname , LPPICTURE *lppi)
{
	HANDLE hFile=CreateFile(fname,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);

	if(hFile==INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL , "无法打开文件!" , "Error" , MB_OK);
		return FALSE;
	}
	//取得文件大小
	DWORD dwFileSize=GetFileSize(hFile,NULL);

	if((DWORD)-1==dwFileSize)
	{
		CloseHandle(hFile);

		MessageBoxA(NULL , "图像文件是空的!" , "Error" , MB_OK);
		return FALSE;
	}
	//读取图像文件
	LPVOID pvData;

	//按文件大小分配内存
	HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,dwFileSize);

	if(NULL==hGlobal)
	{
		CloseHandle(hFile);

		MessageBoxA(NULL , "内存不足，无法分配足够内存!" , "Error" , MB_OK);
		return FALSE;
	}

	pvData=GlobalLock(hGlobal);
	if(NULL==pvData)
	{
		GlobalUnlock(hGlobal);
		CloseHandle(hFile);

		MessageBoxA(NULL , "无法锁定内存!" , "Error" , MB_OK);
		return FALSE;
	}

	DWORD dwFileRead=0;
	BOOL bRead=ReadFile(hFile,pvData,dwFileSize,&dwFileRead,NULL);
	GlobalUnlock(hGlobal);
	CloseHandle(hFile);
	if(FALSE==bRead)
	{
		MessageBoxA(NULL , "读文件出错!" , "Error" , MB_OK);
		return FALSE;
	}

	LPSTREAM pstm=NULL;
	//从已分配内存生成IStream流
	HRESULT hr=CreateStreamOnHGlobal(hGlobal,TRUE,&pstm);

	if(!SUCCEEDED(hr))
	{
		MessageBoxA(NULL , "生成流操作失败!" , "Error" , MB_OK);
		if(pstm!=NULL)
			pstm->Release();
		return FALSE;
	}
	else if(pstm==NULL)
	{
		MessageBoxA(NULL , "生成流操作失败!" , "Error" , MB_OK);
		return FALSE;
	}

	if(lppi != NULL && *lppi != NULL)
	{
		(*lppi)->Release();
	}
	hr=OleLoadPicture(pstm,dwFileSize,FALSE,IID_IPicture,(LPVOID*)&(*lppi));
	pstm->Release();
	if(!SUCCEEDED(hr))
	{
		MessageBoxA(NULL , "加载操作失败!" , "Error" , MB_OK);
		return FALSE;
	}
	else if(*lppi==NULL)
	{
		MessageBoxA(NULL , "加载操作失败!" , "Error" , MB_OK);
		return FALSE;
	}
	return TRUE;
}

/************************************************************************************
Form视图创建完成后的更新操作
主要包括以下内容：
1. Form视图上控件的创建与初始化；
2. 各个控件大小与分辨率无关化操作；
3. 图像库的扫描与加载（ScanDatabase）
************************************************************************************/
void CCBIRFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 设置当前视图的大小
	SetScrollSizes(MM_TEXT , CSize(10 , 10));

	// 设置当前视图的MFC风格
	DWORD dwStyle = GetWindowLong(mImageDBTree.m_hWnd , GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;

	SetWindowLong(mImageDBTree.m_hWnd , GWL_STYLE , dwStyle);
	m_allRoot = mImageDBTree.InsertItem("database");
	m_curRoot = m_allRoot;

	// 扫描与应用程序相关的图像库，并加载其中的内容
	ScanDatabase();

	// 预览相关的其它初始化操作：树状控制的初始化、预览图像的初始化与加载等
	mImageDBTree.Expand(m_allRoot , TVE_TOGGLE);

	LoadMyJpegFile("data/image.orig/0.jpg" , &mpImagePPI);

	RECT treeRect;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_MODELDBTREE);
	pWnd->GetWindowRect(&treeRect);
	pWnd->SetWindowPos(NULL , treeRect.left , treeRect.top , 
		(int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f)) , 
		(int)((float)(treeRect.bottom - treeRect.top) * ((float)mHeight / 738.0f)) , SWP_NOMOVE);

	pWnd = GetDlgItem(IDC_RETRIVEIMAGE);
	pWnd->GetWindowRect(&treeRect);
	pWnd->SetWindowPos(NULL , 5 , 700.0f / 738.0f * (float)mHeight , 
		(int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f)) , 
		(int)((float)(treeRect.bottom - treeRect.top) * ((float)mHeight / 738.0f)) , SWP_NOZORDER);
	int lastWidth = (int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f));

	pWnd = GetDlgItem(IDC_PRRESULT);
	pWnd->GetWindowRect(&treeRect);
	pWnd->SetWindowPos(NULL , 10 + lastWidth , 700.0f / 738.0f * (float)mHeight , 
		(int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f)) , 
		(int)((float)(treeRect.bottom - treeRect.top) * ((float)mHeight / 738.0f)) , SWP_NOZORDER);
}

/************************************************************************************
C++ Std格式的比较函数，用来实现两个带有干扰字符的字符串的大小比较。
实现上采用在字符串中剔除对应的后缀干扰字符，只对关注部分进行比较
比如10.jpg , 111.jpg，该函数返回10.jpg < 111.jpg
************************************************************************************/
bool StringCompareFunc(string a , string b)
{
	char ca[32] , cb[32];
	ZeroMemory(ca , sizeof(char) * 32);
	ZeroMemory(cb , sizeof(char) * 32);
	a._Copy_s(ca , 32 , a.length() - 4);
	b._Copy_s(cb , 32 , b.length() - 4);

	return atoi(ca) < atoi(cb);
}

/************************************************************************************
扫描并加载图像库。
1. 调用函数库中的方法ListDstFilesInFloder，其会返回在目标文件夹中的所有文件
2. 目标库中的所有文件以vector的形式存储
3. 根据图像文件的名字对vector对象进行排序
4. 组织得到当前应用程序的图像库
************************************************************************************/
void CCBIRFormView::ScanDatabase()
{
	List<string>* pDatabase = new List<string>();
	FuncsLib::ListDstFilesInFolder("data/image.orig" , ".jpg" , pDatabase);

	vector<string> databaseVector;

	for(unsigned int i = 0 ; i < pDatabase->GetListSize() ; ++i)
	{
		databaseVector.push_back(*pDatabase->GetItemPtr(i));
	}

	// Sort the items in the database
	sort(databaseVector.begin() , databaseVector.end() , StringCompareFunc);

	int itemIndex = 0;
	for(vector<string>::iterator ite = databaseVector.begin() ; ite != databaseVector.end() ; ite++)
	{
		CString imageName;
		imageName.Format("%s" , ite->c_str());
		AddFile(itemIndex++ , imageName);
	}

	if (mpCBIRView)
	{
		mpCBIRView->InitDatabase(databaseVector);
	}
	delete pDatabase;
}

/************************************************************************************
得到与当前的Form视图关联的右侧渲染窗口指针。
该指针会在创建两个子窗口时由MainFrame对象进行初始化。
在使用时应做安全检查，以判断得到的窗口指针是否合法。
************************************************************************************/
CCBIRView* CCBIRFormView::GetViewPointer()
{
	CMainFrame* parent = ((CMainFrame*)GetParent());
	return (CCBIRView*)parent->m_wndSplitterFrame.GetPane(0 , 1);
}

/************************************************************************************
添加新文件到树状控件中（主要是数据库中的图像文件）
************************************************************************************/
void CCBIRFormView::AddFile(int index , CString& fileName)
{
	HTREEITEM lastRoot;
	lastRoot = m_curRoot;

	mImageDBTree.InsertItem(fileName , m_curRoot);
	mImageDBTree.SetItemData(m_curRoot , index);

	m_curRoot = lastRoot;
}

/************************************************************************************
MFC中的UI操作响应函数。
主要是用户在操作左侧树状控件时得到相应的更新变化，以便及时修改预览信息、变化目标图像的特征值等。
************************************************************************************/
void CCBIRFormView::OnTvnSelchangedModeldbtree(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	TVITEM item = pNMTreeView->itemNew;
	HTREEITEM hChild = mImageDBTree.GetChildItem(item.hItem);

	if(!hChild)
	{
		CString imagePath;
		imagePath.Format("data/image.orig/%s" , mImageDBTree.GetItemText(item.hItem));
		LoadMyJpegFile(imagePath , &mpImagePPI);

		InvalidateRect(NULL , true);

		CString imageName = mImageDBTree.GetItemText(item.hItem);

		char imageNameIndex[32];
		sprintf_s(imageNameIndex , sizeof(char) * 32 , "%s" , imageName.GetBuffer());
		imageNameIndex[strlen(imageNameIndex) - 4] = '\0';

		mSelectedIndex = atoi(imageNameIndex);

		char dstImageName[MAX_PATH];
		sprintf_s(dstImageName , sizeof(char) * MAX_PATH , "%d.jpg" , mSelectedIndex);
		mpCBIRView->LoadDstImage(dstImageName , mSelectedIndex , false);
	}

	InvalidateRect(NULL , false);
}

void CCBIRFormView::OnDestroy()
{
	CFormView::OnDestroy();
}

/************************************************************************************
Form视图的绘制函数
************************************************************************************/
void CCBIRFormView::OnPaint()
{
	CPaintDC dc(this);

	int xPos = 13 * ((float)mWidth / 250.0f);
	int yPos = 465 * ((float)mHeight / 738.0f);
	float maxWith = 230.0f * ((float)mWidth / 250.0f);
	float maxHeight = 220.0f * ((float)mHeight / 738.0f);

	int halfWidth = (int)(maxWith * 0.5f);
	int haftHeight = (int)(maxHeight * 0.5f);

	if(mpImagePPI)
	{
		CDC *pDC = GetDC();

		long hmWidth = 0;
		long hmHeight = 0;
		mpImagePPI->get_Height(&hmHeight);
		mpImagePPI->get_Width(&hmWidth);
		float ahmWidth = (float)hmWidth / 26.45f;
		float ahmHeight = (float)hmHeight /26.45f;

		float xScale = maxWith / (float)ahmWidth;
		float yScale = maxHeight / (float)ahmHeight;
		float scale = min(xScale , yScale);

		float aWidth = (float)ahmWidth * scale;
		float aHeight = (float)ahmHeight * scale; 

		CRect rc;
		GetClientRect(&rc);
		HRESULT hr = mpImagePPI->Render(pDC->m_hDC , xPos + halfWidth - aWidth * 0.5f , yPos + haftHeight - aHeight * 0.5f , aWidth , aHeight , 0 , hmHeight , hmWidth , -hmHeight , &rc);

		ReleaseDC(pDC);
	}
}

/************************************************************************************
以下均为相应的UI响应操作函数
************************************************************************************/
void CCBIRFormView::OnBnClickedRetriveimage()
{
	mpCBIRView->PerformRetrieval();
}

void CCBIRFormView::OnBnClickedPrresult()
{
	// TODO: Add your control notification handler code here
	mpCBIRView->mpRPResultDlg->ShowWindow(SW_SHOW);
}

void CCBIRFormView::OnUpdateShownormal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!mpCBIRView->mShowBeeResult);
}

void CCBIRFormView::OnShownormal()
{
	// TODO: Add your command handler code here
	mpCBIRView->mShowBeeResult = false;
	mpCBIRView->InvalidateRect(NULL , false);
}

void CCBIRFormView::OnUpdateShowbeecolony(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(mpCBIRView->mShowBeeResult);
}

void CCBIRFormView::OnShowbeecolony()
{
	// TODO: Add your command handler code here
	mpCBIRView->mShowBeeResult = true;
	mpCBIRView->InvalidateRect(NULL , false);
}

void CCBIRFormView::OnShowdsr()
{
	// TODO: Add your command handler code here
	mpCBIRView->mpImageDsrDlg->ShowWindow(SW_SHOW);
}

void CCBIRFormView::OnRetrieval()
{
	// TODO: Add your command handler code here
	mpCBIRView->PerformRetrieval();
}

void CCBIRFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	mWidth = cx;
	mHeight = cy;

	TRACE("Size: %d , %d\n" , mWidth , mHeight);
}


void CCBIRFormView::OnBnClickedOutputresult()
{
	mpCBIRView->OutputResult();
}


void CCBIRFormView::OnOutputresult()
{
	// TODO: Add your command handler code here
	mpCBIRView->OutputResult();
}
