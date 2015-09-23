/******************************************************************
文件名：		BeeColonyAlgo.h
创建人：		王钊伟，张佳婕，钟文祺，单汇丰
加注日期：	2013-4-5
描述：		实现了蜂群算法的主类。其中包括使用蜂群算法对数据库图像列表进行检索并返回对应的结果。
******************************************************************/

#ifndef __BEECOLONYALGO_H__
#define __BEECOLONYALGO_H__

#include "Image.h"
#include "DataStruct.h"

class BeeColonyAlgo
{
private:
	int mColonySize;			// 蜂群的规模
	int mDomainSize;			// 单个蜂个体对应的领域的大小
	float* mInitBeesDistance;	// 初始化蜂群的距离列表

	float mBestBeeThreshold;	// 最优蜂所对应的相似度阈值（若距离小于此值说明得到了较好的蜂个体）
	int* mInitBeesPosition;		// 初始蜂群所对应的全局位置列表
	
public:
	/*
	函数名：	PerformRetrieval
	功能：	实现对指定的目标图片在给定的图像库列表上进行检索操作，并将结果返回到对应的有序列表上
	输入：	参数1：指定的目标图片的指针；参数2：目标图像库的列表；参数3：返回结果的图像指针列表
	输出：	空
	*/
	void PerformRetrieval(Image* pSrcImage , List<Image>& srcImageList , List<Image*>& sortedImageList);

public:
	BeeColonyAlgo(int colonySize = 50 , int domainSize = 200 , float bestBeeThreshold = 0.1f);
	~BeeColonyAlgo();
};

#endif