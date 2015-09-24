/******************************************************************
文件名：		Canvas.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		图像在基于MFC视图的OpenGL容器中绘制的实现类。其本质的绘制利用了正交投影下的OpenGL视图来实现。
******************************************************************/
#include "stdafx.h"
#include "Canvas.h"

/************************************************************************************
使用OpenGL中的贴图模式来绘制右侧的滚动条
************************************************************************************/
void Canvas::DrawScrollBar()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();

	// Base bar
	//*
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.8f , 0.0f , 0.0f);
	glTexCoord2f(0.0 , 1.0);
	glVertex3f((GLfloat)mWidth - mBarWidth , (float)mHeight , 0.0f);
	glTexCoord2f(1.0 , 1.0);
	glVertex3f((GLfloat)mWidth, (float)mHeight , 0.0f);
	glTexCoord2f(1.0 , 0.0);
	glVertex3f((GLfloat)mWidth , 0 , 0.0f);
	glTexCoord2f(0.0 , 0.0);
	glVertex3f((GLfloat)mWidth - mBarWidth , 0 , 0.0f);
	glEnd();
	//*/

	// Slider bar
	int barWidthEpsilon = 1;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f , 0.5f , 1.0f);
	glTexCoord2f(0.0 , 1.0);
	glVertex3f((GLfloat)mWidth - mBarWidth + barWidthEpsilon , (float)mHeight , 1.0f);
	glTexCoord2f(1.0 , 1.0);
	glVertex3f((GLfloat)mWidth - barWidthEpsilon , (float)mHeight , 1.0f);
	glTexCoord2f(1.0 , 0.0);
	glVertex3f((GLfloat)mWidth - barWidthEpsilon , (float)mHeight - 50 , 1.0f);
	glTexCoord2f(0.0 , 0.0);
	glVertex3f((GLfloat)mWidth - mBarWidth + barWidthEpsilon , (float)mHeight - 50 , 1.0f);
	glEnd();

	glPopMatrix();

	glPopAttrib();
}

/************************************************************************************
使用OpenGL中的贴图模式来绘制指定位置上的图像。根据传入的位置以及宽高信息构造相应的目标矩形，
之后从给定的图像中获取相应的贴图信息，并将其施加到当前的目标矩形中并进行绘制。
************************************************************************************/
void Canvas::Render(int posX , long posY , int width , int height , Image* pImage)
{
	if(pImage)
	{
		int xEpsilon = 2;
		int yEpsilon = 2;

		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glEnable(GL_TEXTURE_2D);
		//glEnable(GL_BLEND);

		glBindTexture(GL_TEXTURE_2D , pImage->GetGLIndex());

		glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST);  
		glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST); 

		glPushMatrix();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f , 1.0f , 1.0f);

		glTexCoord2f(0.0 , 1.0);
		glVertex3f((float)(posX + xEpsilon) , (float)mHeight - posY - yEpsilon , 0.0f);

		glTexCoord2f(1.0 , 1.0);
		glVertex3f((GLfloat)width + posX - xEpsilon, (float)mHeight - posY - yEpsilon , 0.0f);

		glTexCoord2f(1.0 , 0.0);
		glVertex3f((GLfloat)width + posX - xEpsilon , (float)mHeight - (GLfloat)(height) - posY + yEpsilon , 0.0f);

		glTexCoord2f(0.0 , 0.0);
		glVertex3f((float)(posX + xEpsilon) , (float)mHeight - (GLfloat)(height) - posY + yEpsilon , 0.0f);

		glEnd();

		glPopMatrix();

		glPopAttrib();
	}
}

/************************************************************************************
使用OpenGL中的贴图模式来绘制指定位置上的图像。根据传入的位置以及宽高信息构造相应的目标矩形，
之后从给定的图像中获取相应的贴图信息，并将其施加到当前的目标矩形中并进行绘制即可。
画布上，每行绘制8个图像，图像采用图片墙的形式来排布；
每一行计算出当前一组图像的平均高度，之后采用该高度来对图像进行统一的缩放；
对缩放后的每一行图像进行绘制即可。
************************************************************************************/
void Canvas::Render(List<Image*>& imagePtrList)
{
	// Render all the image to picture wall
	long yPos = mHeightEpsilon;

	int rowSize = 8;
	int rowNums = imagePtrList.GetListSize() / rowSize + 1;

	int imageBaseIndex = 0;

	for(int row = 0 ; row < rowNums ; ++row)
	{
		imageBaseIndex = row * rowSize;

		int subRowSize = min(8 , imagePtrList.GetListSize() - imageBaseIndex);

		int totalHeight = 0;
		for(int i = 0 ; i < subRowSize ; ++i)
		{
			totalHeight += (*imagePtrList.GetItemPtr(imageBaseIndex + i))->GetHeight();
		}
		float avgHeight = (float)totalHeight / (float)rowSize;

		float totalWidth = 0.0f;
		for(int i = 0 ; i < subRowSize ; ++i)
		{
			totalWidth += (float)(*imagePtrList.GetItemPtr(imageBaseIndex + i))->GetWidth() * (avgHeight / (float)(*imagePtrList.GetItemPtr(imageBaseIndex + i))->GetHeight());
		}

		if (totalWidth > 0.0f)
		{
			avgHeight *= (float)(mWidth - mBarWidth) / totalWidth;
		}

		float xPos = 0;
		float imageScale = 1.0f;
		for(int i = 0 ; i < subRowSize ; ++i)
		{
			imageScale = ((float)avgHeight / (float)(*imagePtrList.GetItemPtr(imageBaseIndex + i))->GetHeight());
			Render(xPos , yPos , (int)((float)(*imagePtrList.GetItemPtr(imageBaseIndex + i))->GetWidth() * imageScale) , (int)((float)(*imagePtrList.GetItemPtr(imageBaseIndex + i))->GetHeight() * imageScale) , (*imagePtrList.GetItemPtr(imageBaseIndex + i)));
			xPos += (*imagePtrList.GetItemPtr(imageBaseIndex + i))->GetWidth() * imageScale;
		}

		yPos += (int)avgHeight;
	}

	mTotalHeight = yPos - mHeightEpsilon;
}

/************************************************************************************
外部可见的图像绘制接口，内部主要调用Render以及滚动条绘制接口来实现
************************************************************************************/
void Canvas::Draw(List<Image*>& imagePtrList)
{
	Render(imagePtrList);

	DrawScrollBar();
}

/************************************************************************************
根据接收到的UI偏移值（鼠标中键的滚动值）来翻动当前的图片墙
当输入参数大于0时下翻；
当输入参数小于0时上翻；
图像的翻动实现主要借助于修改整体绘制时的高度偏移值mHeightEpsilon。
************************************************************************************/
void Canvas::Scroll(int delta)
{
	if (mTotalHeight <= 0)
	{
		return;
	}

	if (delta > 0)
	{
		mHeightEpsilon += 10;
	}
	else
	{
		mHeightEpsilon -= 10;
	}

	mHeightEpsilon = min(0 , mHeightEpsilon);
	mHeightEpsilon = max(-(mTotalHeight - mHeight) , mHeightEpsilon);
}

/************************************************************************************
重置画布。主要是重置图片墙绘制时的高度偏移
************************************************************************************/
void Canvas::Reset()
{
	mHeightEpsilon = 0;
}

/************************************************************************************
记录传入的画布大小的参数，并在绘制时使用
************************************************************************************/
void Canvas::SetSize(int width , int height)
{
	mWidth = width;
	mHeight = height;
}

Canvas::Canvas()
{
	mWidth = 800;
	mHeight = 600;

	mBarWidth = 20;

	mTotalHeight = 0;
	mHeightEpsilon = 0;
}

Canvas::~Canvas()
{

}