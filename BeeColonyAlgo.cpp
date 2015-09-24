/******************************************************************
文件名：		BeeColonyAlgo.cpp
创建人：		王钊伟，张佳婕，钟文祺，单汇丰
加注日期：	2013-4-5
描述：		实现了蜂群算法的主类。其中包括使用蜂群算法对数据库图像列表进行检索并返回对应的结果。
******************************************************************/

#include "stdafx.h"
#include "BeeColonyAlgo.h"

int mColonySize;
int mDomainSize;

/************************************************************************************
基于蜂群算法的图像检索的实现：
1. 在给定的蜂群规模下随机生成相应的初始化蜂群（主要是各种蜂个体的位置）
2. 计算初始化蜂群中的每个个体与目标图像之间的相似度
3. 若是初始蜂群中含有符合条件的最优蜂，则得到了合法的初始蜂群，进行5操作
4. 若是初始蜂群中不含有符合条件的最优蜂，则返回1重新生成蜂群并执行后续操作
5. 取最蜂群中的最优蜂，并在其周围的领域内做搜索，并计算相似度
6. 返回最优蜂的领域搜索结果
************************************************************************************/
void BeeColonyAlgo::PerformRetrieval(Image* pSrcImage , List<Image>& srcImageList , List<Image*>& sortedImageList)
{
	// 如果当前目标图片为空时，则直接退出
	if (pSrcImage == NULL)
	{
		return;
	}

	// 得到图像库的大小
	int imageNums = srcImageList.GetListSize();

	// 标记位，用来记录当前的蜂群是否合法
	bool isValidColony = false;

	// 对全局进行搜索，得到合法的初始蜂群
	int bestBeePosition = 0;
	while(isValidColony == false)
	{
		// 使用随机化方法来初始化蜂群的位置
		for(int i = 0 ; i < mColonySize ; ++i)
		{
			mInitBeesPosition[i] = rand() % srcImageList.GetListSize();
		}

		// 计算初始蜂群的相似度
		float minDistance = 99999.0f;
		for(int i = 0 ; i < mColonySize ; ++i)
		{
			pSrcImage->Match(srcImageList.GetItemPtr(mInitBeesPosition[i]));
			mInitBeesDistance[i] = pSrcImage->GetDistance();

			if (minDistance > mInitBeesDistance[i])
			{
				minDistance = mInitBeesDistance[i];
				bestBeePosition = mInitBeesPosition[i];
			}
		}

		// 通过与阈值进行比较以判断当前的蜂群是否合法
		if (minDistance < mBestBeeThreshold)
		{
			isValidColony = true;
		}
	}

	// 取得蜂群中的最优个体，并计算出其合法的领域（主要是处理数据库首尾时的特殊情况）
	int startIndex;
	startIndex = max(0 , bestBeePosition - mDomainSize / 2);
	if (startIndex + mDomainSize > srcImageList.GetListSize())
	{
		startIndex = srcImageList.GetListSize() - mDomainSize;
	}

	// 在当前的领域内进行解的搜索
	for(int i = startIndex ; i < startIndex + mDomainSize ; ++i)
	{
		srcImageList.GetItemPtr(i)->Match(pSrcImage);
	}

	// 对领域内的搜索结果进行排序
	sortedImageList.EmptyList();
	double minDistance;
	int minImageIndex;
	for (int i = 0 ; i < mDomainSize ; ++i)
	{
		minDistance = 99999.0f;
		minImageIndex = 0;

		// 遍历以搜索当前最匹配度最高（距离最小）的图片，并对其进行标记以避免重复搜索
		for (int j = startIndex ; j < startIndex + mDomainSize ; ++j)
		{
			if(srcImageList.GetItemPtr(j)->IsFlagged() == false)
			{
				if (srcImageList.GetItemPtr(j)->GetDistance() < minDistance)
				{
					minImageIndex = j;
					minDistance = srcImageList.GetItemPtr(j)->GetDistance();
				}
			}
		}

		// 将当前最相近的图片加入到列表中，并修改其标记值（该值会有每次Match操作时重置）
		Image* pImage = srcImageList.GetItemPtr(minImageIndex);
		sortedImageList.AddItem(pImage);
		srcImageList.GetItemPtr(minImageIndex)->SetFlagged();
	}
}

/************************************************************************************
构造函数的实现
************************************************************************************/
BeeColonyAlgo::BeeColonyAlgo(int colonySize, int domainSize , float bestBeeThreshold)
{
	mColonySize = colonySize;
	mDomainSize = domainSize;
	mBestBeeThreshold = bestBeeThreshold;

	mInitBeesPosition = new int[mColonySize];
	mInitBeesDistance = new float[mColonySize];
}

/************************************************************************************
析构函数的实现
************************************************************************************/
BeeColonyAlgo::~BeeColonyAlgo()
{
	SAFE_DELETE_ARRAY(mInitBeesPosition);
	SAFE_DELETE_ARRAY(mInitBeesDistance);
}