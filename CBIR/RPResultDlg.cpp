/******************************************************************
文件名：		RPResultDlg.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		检索结果的绘制实现类。其中含在RPResult类的成员对象，并使用其中的值
将每次检索的结果以二维曲线的形式进行绘制并向用户反馈。
******************************************************************/

#include "stdafx.h"
#include "RPResultDlg.h"


// CRPResultDlg 对话框

IMPLEMENT_DYNAMIC(CRPResultDlg, CDialog)

	CRPResultDlg::CRPResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRPResultDlg::IDD, pParent)
{

}

CRPResultDlg::~CRPResultDlg()
{
}

void CRPResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRPResultDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRPResultDlg 消息处理程序

BOOL CRPResultDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

/************************************************************************************
在X轴上绘制给定位置的坐标
************************************************************************************/
inline void drawX(int posX , int posY , CPaintDC* pDC , float value)
{
	char valueStr[12];
	char text[4];
	text[3] = 0;
	sprintf(valueStr , "%1.1f" , value);
	text[0] = valueStr[0];
	text[1] = valueStr[1];
	text[2] = valueStr[2];

	pDC->MoveTo(posX , posY);
	pDC->LineTo(posX , posY - 5);

	pDC->TextOut(posX - 10 , posY , text);
}

/************************************************************************************
在Y轴上绘制给定位置的坐标
************************************************************************************/
inline void drawY(int posX , int posY , CPaintDC* pDC , float value)
{
	char valueStr[12];
	char text[4];
	text[3] = 0;
	sprintf(valueStr , "%1.1f" , value);
	text[0] = valueStr[0];
	text[1] = valueStr[1];
	text[2] = valueStr[2];

	pDC->MoveTo(posX , posY);
	pDC->LineTo(posX + 5 , posY);

	pDC->TextOut(posX - 25 , posY - 5 , text);
}

/************************************************************************************
绘制函数
该函数主要完成对绘制更新操作，主要过程如下：
1. 绘制相应的X轴信息
2. 绘制相应的Y轴信息
3. 绘制常规检索下的RP曲线
4. 绘制蜂群检索下的RP曲线
5. 绘制其它一些辅助信息（如检索用时等）
************************************************************************************/
void CRPResultDlg::OnPaint()
{
	CPaintDC dc(this);

	CFont font;
	font.CreatePointFont(100, "微软雅黑");
	CFont *pOldFont = (CFont *)dc.SelectObject(&font);

	//设置背景为透明
	dc.SetBkMode(0);

	RECT clientRect;
	GetClientRect(&clientRect);

	POINT originPos;
	originPos.x = clientRect.left + 30;
	originPos.y = clientRect.bottom - 70;

	POINT size;
	size.x = (clientRect.right - clientRect.left) - 50;
	size.y = (clientRect.bottom - clientRect.top) - 80;

	dc.MoveTo(originPos.x , originPos.y);
	dc.LineTo(originPos.x + size.x , originPos.y);

	dc.MoveTo(originPos.x , originPos.y);
	dc.LineTo(originPos.x , originPos.y - size.y);

	drawX(originPos.x , originPos.y , &dc , 0.0f);
	drawX(originPos.x + size.x * 0.5 , originPos.y , &dc , 0.5f);
	drawX(originPos.x + size.x , originPos.y , &dc , 1.0f);
	drawY(originPos.x , originPos.y - size.y * 0.5f , &dc , 0.5f);
	drawY(originPos.x , originPos.y - size.y , &dc , 1.0f);

	dc.TextOut(clientRect.right - 100 , clientRect.bottom - 45 , "横向-Recall");
	dc.TextOut(clientRect.right - 100 , clientRect.bottom - 25 , "纵向-Precision");

	// 绘制常规搜索下的结果
	{
		CPen pen(PS_SOLID , 1 , RGB(255, 0, 0));
		CPen *pOldPen = dc.SelectObject(&pen);

		POINT curPos;
		float lastX , lastY;

		int valueX , valueY;
		// 绘制在X轴上 50维度的曲线
		if(mRPResult.mRPDataList.GetListSize() > 0)
		{
			RPData* pRTData = mRPResult.mRPDataList.GetItemPtr(0);
			curPos.x = (LONG)(pRTData->recall * size.x + originPos.x);
			curPos.y = (LONG)(-pRTData->precision * size.y + originPos.y);
			dc.MoveTo(curPos.x , curPos.y);
			lastX = pRTData->recall;
			lastY = pRTData->precision;

			for(int i = 1 ; i < mRPResult.mRPDataList.GetListSize() ; i++)
			{
				if ((i % 20 == 0))
				{
					pRTData = mRPResult.mRPDataList.GetItemPtr(i);
					curPos.x = (int)(pRTData->recall * (float)size.x) + originPos.x;
					curPos.y = -(int)(pRTData->precision * (float)size.y) + originPos.y;
					dc.LineTo(curPos.x , curPos.y);

					valueX = (int)(pRTData->recall * 100.0f);
					valueY = (int)(pRTData->precision * 100.0f);

					dc.MoveTo(curPos.x , curPos.y);

					lastX = pRTData->recall;
					lastY = pRTData->precision;
				}
			}
		}

		dc.MoveTo(75 , clientRect.bottom - 15);
		dc.LineTo(120 , clientRect.bottom - 15);
		
		CString timeText;
		timeText.Format("时间：%3.6f 秒" , mRPResult.mUsedTime);
		dc.TextOut(160 , clientRect.bottom - 25 , timeText);
		dc.TextOut(15 , clientRect.bottom - 25 , "常规搜索");

		dc.SelectObject(pOldPen);
	}

	// 绘制蜂群搜索下的结果
	{
		CPen pen(PS_SOLID , 1 , RGB(0, 0, 255));
		CPen *pOldPen = dc.SelectObject(&pen);

		POINT curPos;
		float lastX , lastY;

		int valueX , valueY;

		int xStep = mRPResultBee.mRPDataList.GetListSize() / 50;
		if(mRPResultBee.mRPDataList.GetListSize() > 0)
		{
			RPData* pRTData = mRPResultBee.mRPDataList.GetItemPtr(0);
			curPos.x = (LONG)(pRTData->recall * size.x + originPos.x);
			curPos.y = (LONG)(-pRTData->precision * size.y + originPos.y);
			dc.MoveTo(curPos.x , curPos.y);
			lastX = pRTData->recall;
			lastY = pRTData->precision;

			for(int i = 1 ; i < mRPResultBee.mRPDataList.GetListSize() ; i++)
			{
				if ((i % xStep == 0))
				{
					pRTData = mRPResultBee.mRPDataList.GetItemPtr(i);
					curPos.x = (int)(pRTData->recall * (float)size.x) + originPos.x;
					curPos.y = -(int)(pRTData->precision * (float)size.y) + originPos.y;
					dc.LineTo(curPos.x , curPos.y);

					valueX = (int)(pRTData->recall * 100.0f);
					valueY = (int)(pRTData->precision * 100.0f);

					dc.MoveTo(curPos.x , curPos.y);

					lastX = pRTData->recall;
					lastY = pRTData->precision;
				}
			}
		}

		dc.MoveTo(75 , clientRect.bottom - 35);
		dc.LineTo(120 , clientRect.bottom - 35);

		CString timeText;
		timeText.Format("时间：%3.6f 秒" , mRPResultBee.mUsedTime);
		dc.TextOut(160 , clientRect.bottom - 45 , timeText);
		dc.TextOut(15 , clientRect.bottom - 45 , "蜂群搜索");

		dc.SelectObject(pOldPen);
	}
	dc.SelectObject(pOldFont);
}