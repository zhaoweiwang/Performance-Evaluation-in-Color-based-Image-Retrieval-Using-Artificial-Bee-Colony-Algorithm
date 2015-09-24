/******************************************************************
文件名：		Canvas.h
创建人：		王钊伟，张佳婕，钟文祺，单汇丰
加注日期：	2013-4-5
描述：		图像在基于MFC视图的OpenGL容器中绘制的实现类。其本质的绘制利用了OpenGL视图来实现。
******************************************************************/

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "Image.h"
#include "FuncsLib.h"

class Canvas
{
private:
	int mWidth;			// 窗口的宽度
	int mHeight;		// 窗口的调试
	int mBarWidth;		// 窗口右侧滚动条框的宽度

	int mTotalHeight;	// 当前绘制的图片列的总高度
	int mHeightEpsilon;	// 当前绘制的图片列的高度偏移（主要用来实现图像的滚动）

private:
	/*
	函数名：	Render
	功能：	实现将单个图像对象在指定的位置上以指定的宽高进行绘制
	输入：	参数1、2：目标图像在窗口中所在的位置；参数3、4：目标图像在窗口上所对应的宽高；参数5：目标图像的指针
	输出：	空
	*/
	void Render(int posX , long posY , int width , int height , Image* pImage);

	/*
	函数名： DrawScrooBar
	功能：	实现窗口右侧的滚动条的绘制
	输入：	空
	输出：	空
	*/
	void DrawScrollBar();

	/*
	函数名：	Render
	功能：	实现对有序的检索结果图像列表在窗口上的绘制操作
	输入：	参数1：检索结果列表的图像指针列表
	输出：	空
	*/
	void Render(List<Image*>& imagePtrList);

public:
	/*
	函数名：	SetSize
	功能：	设置窗口的大小属性
	输出：	参数1、2：窗口所对应的宽、高
	输出：	空
	*/
	void SetSize(int width , int height);

	/*
	函数名：	Draw
	功能：	外部接口，实现对检索结果列表的图像绘制
	输入：	检索结果的排序指镇针列表
	输出：	空
	*/
	void Draw(List<Image*>& imageList);

	/*
	函数名：	Scroll
	功能：	窗口上下滚动功能的实现
	输入：	滚动的幅度值
	输出：	空
	*/
	void Scroll(int delta);

	/*
	函数名：	Reset
	功能：	对绘制窗口进行重置
	输入：	空
	输出：	空
	*/
	void Reset();

public:
	Canvas();
	~Canvas();
};
#endif