/******************************************************************
文件名：		Image.h
创建人：		王钊伟，张佳婕，钟文祺，单汇丰
加注日期：	2013-4-5
描述：		主要图像类的实现。该类中实现了单个图像所对应的大多数操作，比如图像的加载、特征值的提取、
基于牲值的图像匹配等。
******************************************************************/
#ifndef __IMAGEPARSER_H__
#define __IMAGEPARSER_H__
#include <GL/glew.h>

struct RGBValue
{
	unsigned char r , g , b;

	RGBValue()
	{
		r = 0;
		g = 0; 
		b = 0;
	}

	RGBValue(unsigned char aa , unsigned char bb , unsigned char cc)
	{
		r = aa;
		g = bb;
		b = cc;
	}
};

struct HSVValue
{
	float h , s , v;

	HSVValue()
	{
		h = 0.0f;
		s = 0.0f;
		v = 0.0f;
	}

	HSVValue(float a , float b , float c)
	{
		h = a;
		s = b;
		v = c;
	}
};

class Image
{
private:
	char mPath[MAX_PATH];	// 图像对象的路径
	char mName[MAX_PATH];	// 图像对象的名字
	unsigned char* mpData;	// 图像对象的具体数据空间
	int mWidth;				// 图像对象的宽和高
	int mHeight;	
	int mIndex;				// 图像对象所对应的数据库中的索引

	GLuint mGLIndex;		// 图像对象所对应的OpenGL贴图索引，在渲染时使用

	double mHistogram[256];	// 直方图特征向量空间
	double mEntropy[3];		// 颜色熵特征向量空间
	double mMoment[9];		// 颜色矩特征向量空间

	double mWeight[3];		// 三种特征值在最终的综合特征值中所占的比重，默认情况下为，0.3, 0.3 , 0.4

	double mDistance;		// 当前图像对象与其它图像进行匹配操作之后的获得的距离（也即不相似度）
	bool mIsFlagged;		// 标记当前图像是否被操作

private:
	/*
	函数名：	RGB2HSV
	功能：	将像素值从RGB空间转换到HSV空间
	输入：	参数1: RGB像素值
	输出：	HSVValue：HSV像素值
	*/
	HSVValue RGB2HSV(RGBValue& rgb);
	/*
	函数名：	ExtractHistogram
	功能：	提取图像的直方图特征值
	输入：	空
	输出：	空
	*/
	void ExtractHistogram();

	/*
	函数名：	ExtractEntropy
	功能：	提取图像的颜色熵特征
	输入：	空
	输出：	空
	*/
	void ExtractEntropy();

	/*
	函数名：	ExtractMoment
	功能：	提取图像的颜色矩特征
	输入：	空
	输出：	空
	*/
	void ExtractMoment();

	/*
	函数名： Normalize
	功能：	对图像的三种特征值进行归一并单位化操作
	输入：	空
	输出：	空
	*/
	void Normalize();

	/*
	函数名：	DebugOutputDescriptor
	功能：	用作调试使用，输出图像的特征值
	输入：	空
	输出：	空
	*/
	void DebugOutputDescriptor();

public:
	/*
	函数名：	LoadImage
	功能：	加载当前图像的数据（内部目录）
	输出：	空
	输入：	空
	*/
	void LoadImage();

	/*
	函数名：	LoadImage
	功能：	加载当前图像的数据（外部目录）
	输出：	空
	输入：	空
	*/
	void LoadOutImage();

	/*
	函数名：	GetWidth, GetHeight
	功能：	得到当前图像的宽和高
	输入：	空
	输出：	图像的宽和高
	*/
	int GetWidth();
	int GetHeight();

	/*
	函数名：	InitImage
	功能：	初始化图像的属性
	输入：	参数1: 图像的名称；参数2：图像的数据库索引
	输出：	空
	*/
	void InitImage(const char* pName , int index);

	/*
	函数名：	GetGLIndex
	功能：	获得图像的OpenGL索引
	输入：	空
	输出：	OpenGL中的设备索引
	*/
	GLuint GetGLIndex();

	/*
	函数名：	ExtractDescriptor
	功能：	提取图像的特征值（所有）
	输入：	空
	输出：	空
	*/
	void ExtractDescriptor();

	/*
	函数名：	Match
	功能：	将当前图像与另外一图像进行匹配，并在其成员变量中保存相似度
	输入：	参数1： 另一图像的对象指针
	输出：	空
	*/
	void Match(Image* pImage);

	/*
	函数名：	GetDistance
	功能：	获取当前图像上一次匹配之后的相似度值
	输入：	空
	输出：	上一次匹配时得到的相似度
	*/
	double GetDistance();

	/*
	函数名：	SetFlagged
	功能：	对当前图像进行标记，以防止对其重复操作
	输入：	空
	输出：	空
	*/
	void SetFlagged();

	/*
	函数名：	IsFlagged
	功能：	查询当前图像是否已经被标记（处理过）
	输入：	空
	输出：	bool，是否已被标记
	*/
	bool IsFlagged();

	/*
	函数名：	GetImageIndex
	功能：	获取当前图像在数据库中所对应的索引
	输入：	空
	输出：	int，数据库中的索引对应值
	*/
	int GetImageIndex();

	/*
	函数名：	GetHistogramValue
	功能：	得到直方图特征向量中某个维度上的具体值（在进行特征值绘制时使用）
	输入：	参数1：特征向量的维度索引
	输出：	float，特征值
	*/
	float GetHistogramValue(int index);

	/*
	函数名：	GetEntropyValue
	功能：	得到颜色熵特征向量中某个维度上的具体值（在进行特征值绘制时使用）
	输入：	参数1：特征向量的维度索引
	输出：	float，特征值
	*/
	float GetEntropyValue(int index);

	/*
	函数名：	GetMomentValue
	功能：	得到颜色矩特征向量中某个维度上的具体值（在进行特征值绘制时使用）
	输入：	参数1：特征向量的维度索引
	输出：	float，特征值
	*/
	float GetMomentValue(int index);

public:
	Image();
	~Image();

};
#endif