/******************************************************************
文件名：		ImageDsrDlg.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		主要用来实现图像特征值在MFC的Dialog控件中的绘制并更新
******************************************************************/

#include "stdafx.h"
#include "ImageDsrDlg.h"


// CRPResultDlg 对话框

IMPLEMENT_DYNAMIC(ImageDsrDlg, CDialog)

	ImageDsrDlg::ImageDsrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ImageDsrDlg::IDD, pParent)
{
	mpSrcImage = NULL;
}

ImageDsrDlg::~ImageDsrDlg()
{
}

void ImageDsrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImageDsrDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRPResultDlg 消息处理程序

BOOL ImageDsrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

/************************************************************************************
在X轴上绘制给定位置的坐标
************************************************************************************/
inline void drawX(int posX , int posY , CPaintDC* pDC , int value)
{
	char text[32];
	sprintf_s(text , sizeof(char) * 32 , "%d" , value);

	pDC->MoveTo(posX , posY);
	pDC->LineTo(posX , posY - 5);

	if (value == 256)
	{
		pDC->TextOut(posX - 25 , posY , text);
	}
	else
	{
		pDC->TextOut(posX - 10 , posY , text);
	}
}

/************************************************************************************
在Y轴上绘制给定位置的坐标
************************************************************************************/
inline void drawY(int posX , int posY , CPaintDC* pDC , float value)
{
	char text[32];
	sprintf_s(text , sizeof(char) * 32 , "%1.1f" , value);

	pDC->MoveTo(posX , posY);
	pDC->LineTo(posX + 5 , posY);

	pDC->TextOut(posX - 20 , posY , text);
}

/************************************************************************************
绘制函数
该函数主要完成对绘制更新操作，主要过程如下：
1. 绘制相应的X轴信息
2. 绘制相应的Y轴信息
3. 对图像的原始特征值进行插值细化
4. 绘制插值后每个维度处一特征值
************************************************************************************/
void ImageDsrDlg::OnPaint()
{
	if (mpSrcImage == NULL)
	{
		return;
	}

	CPaintDC dc(this);

	CFont font;
	font.CreatePointFont(100, "微软雅黑");
	CFont *pOldFont = (CFont *)dc.SelectObject(&font);

	//设置背景为透明
	dc.SetBkMode(0);

	RECT clientRect;
	GetClientRect(&clientRect);

	POINT originPos;
	originPos.x = clientRect.left + 25;
	originPos.y = clientRect.bottom - 30;

	POINT size;
	size.x = (clientRect.right - clientRect.left) - 25;
	size.y = (clientRect.bottom - clientRect.top) - 80;

	dc.MoveTo(originPos.x , originPos.y);
	dc.LineTo(originPos.x + size.x , originPos.y);
	dc.MoveTo(originPos.x , originPos.y);
	dc.LineTo(originPos.x , clientRect.top);

	drawX(originPos.x , originPos.y , &dc , 0);
	drawX(originPos.x + size.x * 0.5 , originPos.y , &dc , 128);
	drawX(originPos.x + size.x , originPos.y , &dc , 256);
	drawY(originPos.x , clientRect.top + (clientRect.bottom - clientRect.top - 30) * 0.5 , &dc , 0.5);
	drawY(originPos.x , clientRect.top , &dc , 1.0);

	dc.TextOut(clientRect.right - 80 , clientRect.top , "横向-维度");
	dc.TextOut(clientRect.right - 80 , clientRect.top + 20 , "纵向-向量值");

	{
		CPen pen(PS_SOLID , 1 , RGB(0, 0, 255));
		CPen *pOldPen = dc.SelectObject(&pen);

		float dsrValue[256 + 3 + 9];
		int dsrIndex = 0;
		for (int i = 0 ; i < 256 ; ++i)
		{
			dsrValue[dsrIndex++] = mpSrcImage->GetHistogramValue(i);
		}
		for (int i = 0 ; i < 3 ; ++i)
		{
			dsrValue[dsrIndex++] = mpSrcImage->GetHistogramValue(i);
		}
		for (int i = 0 ; i < 9 ; ++i)
		{
			dsrValue[dsrIndex++] = mpSrcImage->GetHistogramValue(i);
		}

		//int intDimSize = 76 * 5 - 4;
		//float intDsrValue[1024];
		//InterpolateDsrValue(dsrValue , intDsrValue , 76);

		int intDimSize = 256 + 3 + 9;
		int step = 1;//size.x / 220;

		int xPos = 2;
		for (int i = 0 ; i < intDimSize ; ++i)
		{
			dc.MoveTo(originPos.x + xPos , originPos.y);
			dc.LineTo(originPos.x + xPos , originPos.y - dsrValue[i] * size.y * 30);
			xPos += step + 1;
		}

		dc.SelectObject(pOldPen);
	}
	dc.SelectObject(pOldFont);
}

/************************************************************************************
设置目标图像的指针
************************************************************************************/
void ImageDsrDlg::SetSrcImage(Image* pSrcImage)
{
	mpSrcImage = pSrcImage;

	InvalidateRect(NULL , TRUE);
}