/******************************************************************
文件名：		RPResult.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		检索结果实现类。其主要负责对于检索结果列表进行R-P曲线的分析与计算，其
作为RPResultDlg对象的成员来将RP曲线可视化绘制到窗口中。
******************************************************************/

#include "stdafx.h"
#include "RPResult.h"

/************************************************************************************
判断两个指定索引的图像是否属于同一类
************************************************************************************/
inline bool IsSameClass(int srcClass , int dstIndex)
{
	return srcClass == (dstIndex / 100);
}

/************************************************************************************
计算RP曲线操作
根据返回的检索结果计算本次检索的RP曲线。主要实现通过从前向后进行遍历，统计其中与目标图像关联的图像（
属于同一类的图像）的数量，并依次生成相应的RP值，存入RP曲线列表即可。
Recall = 当前遍历点之前与目标图像关联的图像的数量 / 数据库中与目标图像关联的图像的数量
Precision = 当前遍历点之前与目标图像关联的图像的数量 / 当前遍历点前的图片数量
************************************************************************************/
void RPResult::ComputeRP(int srcIndex , List<Image*>& resultList)
{
	mRPDataList.EmptyList();

	RPData rpData;

	int srcClass = srcIndex / 100;

	float relevantImageNums = 0.0f;

	mbIsValid = false;

	for (int i = 0 ; i < resultList.GetListSize() ; ++i)
	{
		rpData.recall = relevantImageNums * 0.01f;

		Image* pImage = *resultList.GetItemPtr(i);
		if (IsSameClass(srcClass , pImage->GetImageIndex()))
		{
			relevantImageNums += 1.0f;
		}

		rpData.precision = relevantImageNums / (float)(i + 1);

		mRPDataList.AddItem(rpData);

		if (rpData.precision > 0.0f)
		{
			mbIsValid = true;
		}
	}
}

/************************************************************************************
输出当前检索结果到外部文件中
************************************************************************************/
void RPResult::OutputResult(ofstream& outFile)
{
	if (mbIsValid == false)
	{
		return;
	}

	outFile<<"Time: "<<mUsedTime<<endl;
	

	int xDim = 100;
	float* valueList = new float[xDim];
	float xStep = 0.01f;
	float xValue = 0.0f;

	for(int i = 0 ; i < xDim ; ++i)
	{
		// 在结果数组中找中当前X坐标处下的位置
		int intX0 = 0;
		for(int j = mRPDataList.GetListSize() - 1 ; j >= 0 ; --j)
		{
			if (xValue >= mRPDataList.GetItemPtr(j)->recall)
			{
				intX0 = j;
				break;
			}
		}

		// 使用intX0与intX0+1来插值出当前处的位置，注意处理最后一个值的情况
		if(intX0 >= mRPDataList.GetListSize() - 1)
		{
			valueList[i] = mRPDataList.GetItemPtr(intX0)->precision;
		}
		else
		{
			float epsilon = (xValue - mRPDataList.GetItemPtr(intX0)->recall) / (mRPDataList.GetItemPtr(intX0 + 1)->recall - mRPDataList.GetItemPtr(intX0)->recall);
			valueList[i] = (1.0f - epsilon) * mRPDataList.GetItemPtr(intX0)->precision + epsilon * mRPDataList.GetItemPtr(intX0 + 1)->precision;
		}

		xValue += xStep;
	}

	outFile<<"RP: "<<xDim<<endl;
	for(int i = 0 ; i < xDim ; ++i)
	{
		outFile<<valueList[i]<<" ";
	}

	outFile<<endl;

	delete []valueList;
}

RPResult::RPResult()
{
	mUsedTime = 0;
}