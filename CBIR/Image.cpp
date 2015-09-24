/******************************************************************
文件名：		Image.cpp
创建人：		王钊伟，张佳婕，钟文祺，单汇丰
加注日期：	2013-4-5
描述：		主要图像类的实现。该类中实现了单个图像所对应的大多数操作，比如图像的加载、特征值的提取、
基于牲值的图像匹配等。
******************************************************************/
#include "stdafx.h"
#include "Image.h"
#include "SOIL.h"
#include "FuncsLib.h"
#include "iostream"

/************************************************************************************
加载图像。
通过当前图片对象中设置的属性，如名称、地址等加载相应的图像数据
1. 使用SOIL库来加载图像到内存中，并将其中的具体数据存储到mpData中以供特征提取使用；
2. 使用SOIL库来加载图像到显存中，并记录相应的OpenGL索引，以便在进行绘制时使用；
************************************************************************************/
void Image::LoadImage()
{
	if (strlen(mName) <= 0)
	{
		return;
	}

	char imageFullName[MAX_PATH];
	sprintf_s(imageFullName , sizeof(char) * MAX_PATH , "%s/%s" , mPath , mName);

	int imageChannel;
	mpData = SOIL_load_image(imageFullName , &mWidth , &mHeight , &imageChannel , SOIL_LOAD_RGB);
	if(mpData == NULL)
	{
		MessageBoxA(NULL , "Fail to load the image!" , "Error" , MB_OK);
	}

	mGLIndex = SOIL_load_OGL_texture(imageFullName , SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if(mGLIndex == 0)
	{
		MessageBoxA(NULL , "Fail to load the image!" , "Error" , MB_OK);
	}
}

/************************************************************************************
加载图像（与上函数相同，只不过这里不是用当前应用程序的相对路径，而是在外部用全局的绝对路径）
通过当前图片对象中设置的属性，如名称、地址等加载相应的图像数据
1. 使用SOIL库来加载图像到内存中，并将其中的具体数据存储到mpData中以供特征提取使用；
2. 使用SOIL库来加载图像到显存中，并记录相应的OpenGL索引，以便在进行绘制时使用；
************************************************************************************/
void Image::LoadOutImage()
{
	if (strlen(mName) <= 0)
	{
		return;
	}

	char imageFullName[MAX_PATH];
	sprintf_s(imageFullName , sizeof(char) * MAX_PATH , "%s" , mName);

	int imageChannel;
	mpData = SOIL_load_image(imageFullName , &mWidth , &mHeight , &imageChannel , SOIL_LOAD_RGB);
	if(mpData == NULL)
	{
		MessageBoxA(NULL , "Fail to load the image!" , "Error" , MB_OK);
	}

	mGLIndex = SOIL_load_OGL_texture(imageFullName , SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if(mGLIndex == 0)
	{
		MessageBoxA(NULL , "Fail to load the image!" , "Error" , MB_OK);
	}
}

/************************************************************************************
图像的特征值提取。
主要包括以下主要操作：
1. 提取颜色直方图特征值
2. 提取颜色熵特征值
3. 提取颜色矩特征值
4. 单位化上三种独立的特征值，并根据各自的权重而得到最终的综合特征值
5. 输出调试信息（release版本无）
************************************************************************************/
void Image::ExtractDescriptor()
{
	if (mpData)
	{
		// 提取图片的灰度直方图特征值
		ExtractHistogram();

		// 提取图片的颜色熵特征值
		ExtractEntropy();

		// 提取图片的颜色矩特征值
		ExtractMoment();

		// 根据不同特征值所对应的权重来单位化各部分特征值
		Normalize();

		// 输出图片的特征值调试信息
		DebugOutputDescriptor();
	}
}

/************************************************************************************
将像素值由RGB空间转换到HSV空间
具体操作实现可以参考：https://zh.wikipedia.org/wiki/HSL%E5%92%8CHSV%E8%89%B2%E5%BD%A9%E7%A9%BA%E9%97%B4#.E4.BB.8E_RGB_.E5.88.B0_HSL_.E6.88.96_HSV_.E7.9A.84.E8.BD.AC.E6.8D.A2
************************************************************************************/
HSVValue Image::RGB2HSV(RGBValue& rgb)
{
	HSVValue hsv;
	float r , g , b;
	r = (float)rgb.r / 255.0f;
	g = (float)rgb.g / 255.0f;
	b = (float)rgb.b / 255.0f;

	float fMin , fMax;
	fMin = min(min(r , g) , b);
	fMax = max(max(r , g) , b);

	// 计算其中的H
	if (r == g && r == b)	// max == min
	{
		hsv.h = 0.0f;
	}
	else
	{
		if (r > g && r > b)	// max == r
		{
			if (g >= b)		// max == r && g >= b
			{
				hsv.h = 60.0f * (g - b) / (fMax - fMin);
			}
			else			// max == r && g < b
			{
				hsv.h = 60.0f * (g - b) / (fMax - fMin) + 360.0f;
			}
		}
		else
		{
			if (g > r && g > b)		// max == g
			{
				hsv.h = 60.0f * (b - r) / (fMax - fMin) + 120.0f;
			}
			else					// max == b
			{
				hsv.h = 60.0f * (r - g) * (fMax - fMin) + 240.0f;
			}
		}
	}

	// 计算其中的S
	hsv.s = (fMax <= 0.0f) ? 0.0f : 1.0f - fMin / fMax;

	// 计算其中的V
	hsv.v = fMax;

	return hsv;
	
}

/************************************************************************************
提取图像的直方图特征。
计算256维度的颜色直方图，并将其存储在Image的成员变量mHistogram中以备使用。
其主要计算原理：
遍历图像中的每个像素，得到其对应的三个通道上的颜色值，通过RGB空间中的颜色值计算对应的颜色阶；
更新相应的颜色阶数组。最后在颜色阶数组中的数量即可得到最终的直方图特征值。
************************************************************************************/
void Image::ExtractHistogram()
{
	ZeroMemory(mHistogram , sizeof(double) * 256);

	unsigned char r, g, b;

	int Lumi = 0; 

	for (int i = 0 ; i < mHeight ; ++i)
	{
		for (int j = 0 ; j < mWidth ; ++j)
		{
			int baseIndex = (i * mWidth + j) * 3;
			r = mpData[baseIndex + 0];
			g = mpData[baseIndex + 1];
			b = mpData[baseIndex + 2];

			// 得到当前像素在HSV空间下的值
			HSVValue hsv = RGB2HSV(RGBValue(r , g , b));
			int gradeH = 0 , gradeS = 0 , gradeV = 0;

			// 处理H通道分量，共处理为16阶
			if(hsv.h <= 15.0f || hsv.h > 345.0f)
			{
				gradeH = 0;
			}
			if(hsv.h <= 25.0f && hsv.h > 15.0f)
			{
				gradeH = 1;
			}
			if(hsv.h <= 45.0f && hsv.h > 25.0f)
			{
				gradeH = 2;
			}
			if(hsv.h <= 55.0f && hsv.h > 45.0f)
			{
				gradeH = 3;
			}
			if(hsv.h <= 80.0f && hsv.h > 55.0f)
			{
				gradeH = 4;
			}
			if(hsv.h <= 108.0f && hsv.h > 80.0f)
			{
				gradeH = 5;
			}
			if(hsv.h <= 140.0f && hsv.h > 108.0f)
			{
				gradeH = 6;
			}
			if(hsv.h <= 165.0f && hsv.h > 140.0f)
			{
				gradeH = 7;
			}
			if(hsv.h <= 190.0f && hsv.h > 165.0f)
			{
				gradeH = 8;
			}
			if(hsv.h <= 220.0f && hsv.h > 190.0f)
			{
				gradeH = 9;
			}
			if(hsv.h <= 255.0f && hsv.h > 220.0f)
			{
				gradeH = 10;
			}
			if(hsv.h <= 275.0f && hsv.h > 255.0f)
			{
				gradeH = 11;
			}
			if(hsv.h <= 290.0f && hsv.h > 275.0f)
			{
				gradeH = 12;
			}
			if(hsv.h <= 316.0f && hsv.h > 290.0f)
			{
				gradeH = 13;
			}
			if(hsv.h <= 330.0f && hsv.h > 316.0f)
			{
				gradeH = 14;
			}
			if(hsv.h <= 345.0f && hsv.h > 330.0f)
			{
				gradeH = 15;
			}

			// 处理S通道分量，共处理为4阶
			if(hsv.s <= 0.15 && hsv.s > 0.0f)
			{
				gradeS = 0;
			}
			if(hsv.s <= 0.4 && hsv.s > 0.15f)
			{
				gradeS = 1;
			}
			if(hsv.s <= 0.75 && hsv.s > 0.4f)
			{
				gradeS = 2;
			}
			if(hsv.s <= 1.0 && hsv.s > 0.75f)
			{
				gradeS = 3;
			}

			// 处理V通道分量，共处理为4阶
			if(hsv.v <= 0.15 && hsv.v > 0.0f)
			{
				gradeV = 0;
			}
			if(hsv.v <= 0.4 && hsv.v > 0.15f)
			{
				gradeV = 1;
			}
			if(hsv.v <= 0.75 && hsv.v > 0.4f)
			{
				gradeV = 2;
			}
			if(hsv.v <= 1.0 && hsv.v > 0.75f)
			{
				gradeV = 3;
			}

			// 将HSV归一化
			Lumi = gradeH * 16 + gradeS * 4 + gradeV;

			mHistogram[min(Lumi , 255)] += 1.0f;
		}
	}
}

/************************************************************************************
提取图像的颜色熵特征。
计算3维度的颜色熵值，并将其存储在Image的成员变量mEntropy中以备使用
对于每个像素上的具体操作主要是做非线性的熵变化。
具体的内容可以参见相应的论文。
************************************************************************************/
void Image::ExtractEntropy()
{
	unsigned char r, g, b;

	long rStat[256] = {0}, gStat[256] = {0}, bStat[256] = {0};
	double tempr=0,tempg=0,tempb=0;
	for (int i = 0 ; i < mHeight ; ++i)
	{
		for (int j = 0 ; j < mWidth ; ++j)
		{
			int baseIndex = (i * mWidth + j) * 3;
			r = mpData[baseIndex + 0];
			g = mpData[baseIndex + 1];
			b = mpData[baseIndex + 2];

			rStat[r]++;
			gStat[g]++;
			bStat[b]++;
		}
	}

	for (int i = 0; i < 3 ; ++i)
	{
		mEntropy[i] = 0;
	}

	double sizeEpsilon = 1.0f / (float)(mWidth * mHeight);
	double entropyEpsilon = 1.0f / log(256.0f);
	for (int i = 0 ; i < 256 ; ++i)
	{
		tempr = rStat[i] * sizeEpsilon;
		if (tempr > 0)
		{
			mEntropy[0] += -tempr * (log(tempr) * entropyEpsilon);
		}

		tempg = gStat[i] * sizeEpsilon;
		if (tempg > 0)
		{
			mEntropy[1] += -tempg * (log(tempg) * entropyEpsilon);
		}

		tempb = bStat[i] * sizeEpsilon;
		if (tempb > 0)
		{
			mEntropy[2] += -tempb * (log(tempb) * entropyEpsilon);
		}
	}
}

/************************************************************************************
提取图像的颜色矩特征值。
计算9维度的颜色矩，并将其存储在Image的成员变量mEntropy中以备使用
具体的内容可以参见相应的论文。
************************************************************************************/
void Image::ExtractMoment()
{
	long cr = 0 , cg = 0 , cb = 0;
	unsigned char r , g , b;
	double rMean , gMean , bMean;

	for (int i = 0 ; i < mHeight ; ++i)
	{
		for (int j = 0 ; j < mWidth ; ++j)
		{
			int baseIndex = (i * mWidth + j) * 3;
			r = mpData[baseIndex + 0];
			g = mpData[baseIndex + 1];
			b = mpData[baseIndex + 2];

			cr += (int)r;
			cg += (int)g;
			cb += (int)b;
		}
	}

	double sizeEpsilon = 1.0 / (mWidth * mHeight);
	mMoment[0] = rMean = cr * sizeEpsilon;
	mMoment[1] = gMean = cg * sizeEpsilon;
	mMoment[2] = bMean = cb * sizeEpsilon;

	double cr2 = 0 , cg2 = 0 , cb2 = 0 , cr3 = 0 , cg3 = 0 , cb3 = 0;
	for (int i = 0 ; i < mHeight ; ++i)
	{
		for (int j = 0 ; j < mWidth ; ++j)
		{
			int baseIndex = (i * mWidth + j) * 3;
			r = mpData[baseIndex + 0];
			g = mpData[baseIndex + 1];
			b = mpData[baseIndex + 2];

			cr2 += ((double)r - (double)rMean) * ((double)r - (double)rMean);
			cr3 += fabs(((double)r - (double)rMean)) * ((double)r - (double)rMean) * ((double)r - (double)rMean);
			cg2 += ((double)g - (double)gMean) * ((double)g - (double)gMean);
			cg3 += fabs(((double)g - (double)gMean)) * ((double)g - (double)gMean) * ((double)g - (double)gMean);
			cb2 += ((double)b - (double)bMean) * ((double)b - (double)bMean);
			cb3 += fabs(((double)b - (double)bMean)) * ((double)b - (double)bMean) * ((double)b - (double)bMean);
		}
	}
	mMoment[3] = sqrt(cr2 * sizeEpsilon);
	mMoment[4] = sqrt(cg2 * sizeEpsilon);
	mMoment[5] = sqrt(cb2 * sizeEpsilon);
	mMoment[6] = pow(cr3 * sizeEpsilon , 0.33333333333333333);
	mMoment[7] = pow(cg3 * sizeEpsilon , 0.33333333333333333);
	mMoment[8] = pow(cb3 * sizeEpsilon , 0.33333333333333333);
}

/************************************************************************************
单位化特征向量
对传入的特征向量，将其单位化到一个特定的权重值上。
主要操作：
1. 遍历所有的特征值并求合
2. 根据得到的特征值向量将其单位化
3. 将单位化的特征向量缩放到权重空间上即可 
************************************************************************************/
inline void NormalizeDescriptor(int dim , double* descValue , double weight)
{
	double total = 0;
	for (int i = 0 ; i < dim ; ++i)
	{
		total += descValue[i];
	}

	double scaleEpsilon = weight / total;
	for (int i = 0 ; i < dim ; ++i)
	{
		descValue[i] *= scaleEpsilon;
	}
}

/************************************************************************************
单位化三个独立的特征向量，并得到最终的综合特征向量。
根据权重值，对三种特征向量进行单位化操作
************************************************************************************/
void Image::Normalize()
{
	NormalizeDescriptor(256 , mHistogram , mWeight[0]);
	NormalizeDescriptor(3 , mEntropy , mWeight[1]);
	NormalizeDescriptor(9 , mMoment , mWeight[2]);
}

/************************************************************************************
调试信息的输出
************************************************************************************/
void Image::DebugOutputDescriptor()
{
	// 输出对应的直方图信息
	TRACE("Histogram: ");
	for( int i = 0 ; i < 256 ; ++i)
	{
		TRACE("%f " , mHistogram[i]);
	}
	TRACE("\n");

	// 输出对应的颜色熵值信息
	TRACE("Entropy: ");
	for( int i = 0 ; i < 3 ; ++i)
	{
		TRACE("%f " , mEntropy[i]);
	}
	TRACE("\n");

	// 输出对应的颜色矩信息
	TRACE("Moment: ");
	for( int i = 0 ; i < 9 ; ++i)
	{
		TRACE("%f " , mMoment[i]);
	}
	TRACE("\n");
}

/************************************************************************************
获取当前图像的大小信息
************************************************************************************/
int Image::GetWidth()
{
	return mWidth;
}

int Image::GetHeight()
{
	return mHeight;
}

/************************************************************************************
初始化图像。
主要通过参数来初始化图像的名称、数据库索引
************************************************************************************/
void Image::InitImage(const char* pName , int index)
{
	strcpy_s(mName , pName);
	mIndex = index;
}

/************************************************************************************
OpenGL索引的获取
反回当前图像在OpenGL设备中的索引
************************************************************************************/
GLuint Image::GetGLIndex()
{
	return mGLIndex;
}

/************************************************************************************
图像匹配。
将当前的图像与外部传入的图像进行距离匹配，其需要两张图像均是已经对特征向量进行过单位化操作的基础上
进行。计算方法也较为简单：
直接计算并累加两张图像的特征向量各个维度上的欧氏距离即可，最终以此距离作为最终的不同度(或
1.0 - distance来获取相似度）。此处计算得到的相似度是下一步的检索与排序操作的基础。
************************************************************************************/
void Image::Match(Image* pImage)
{
	mIsFlagged = false;
	mDistance = 0;

	// 累积灰度图部分的相似度
	for(int i = 0 ; i < 256 ; ++i)
	{
		mDistance += pow(mHistogram[i] - pImage->mHistogram[i] , 2.0);
	}

	// 累积颜色熵部分的相似度
	for (int i = 0 ; i < 3 ; ++i)
	{
		mDistance += pow(mEntropy[i] - pImage->mEntropy[i] , 2.0);
	}

	// 累积颜色矩部分的相似度
	for (int i = 0 ; i < 9 ; ++i)
	{
		mDistance += pow(mMoment[i] - pImage->mMoment[i] , 2.0);
	}

	if (mDistance > 0)
	{
		mDistance = sqrt(mDistance);
	}
}

/************************************************************************************
获取图像距离。
返回上一次匹配操作所得到图片之间的距离（或相似度）
************************************************************************************/
double Image::GetDistance()
{
	return mDistance;
}

/************************************************************************************
设置图像的操作标记
************************************************************************************/
void Image::SetFlagged()
{
	mIsFlagged = true;
}

/************************************************************************************
获取图像的操作标记
************************************************************************************/
bool Image::IsFlagged()
{
	return mIsFlagged;
}

/************************************************************************************
获取图像的数据库索引
************************************************************************************/
int Image::GetImageIndex()
{
	return mIndex;
}

/************************************************************************************
获取图像指定维度上的直方图特征值
************************************************************************************/
float Image::GetHistogramValue(int index)
{
	return mHistogram[index];
}

/************************************************************************************
获取图像指定维度上的颜色熵值
************************************************************************************/
float Image::GetEntropyValue(int index)
{
	return mEntropy[index];
}

/************************************************************************************
获取图像指定维度上的颜色矩值
************************************************************************************/
float Image::GetMomentValue(int index)
{
	return mMoment[index];
}

Image::Image()
{
	mpData = NULL;
	sprintf_s(mPath , sizeof(char) * MAX_PATH , "data/image.orig");

	mWeight[0] = 0.3;
	mWeight[1] = 0.3;
	mWeight[2] = 1.0 - mWeight[0] - mWeight[1];

	mDistance = 0;
	mIsFlagged = true;

	mIndex = 0;
}

Image::~Image()
{
	SAFE_DELETE_ARRAY(mpData);
}