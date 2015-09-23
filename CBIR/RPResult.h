/******************************************************************
文件名：		RPResult.h
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		检索结果实现类。其主要负责对于检索结果列表进行R-P曲线的分析与计算，其
作为RPResultDlg对象的成员来将RP曲线可视化绘制到窗口中。
******************************************************************/

#ifndef __RPRESULT_H__
#define __RPRESULT_H__

#include "DataStruct.h"
#include "Image.h"
#include <fstream>

using namespace std;
/*
R-P值对象
*/
struct RPData
{
	float recall;
	float precision;
};

class RPResult
{
public:
	List<RPData> mRPDataList;	// RP值对象列表

	float mUsedTime;			// 检索耗时
		
	bool mbIsValid;				// 合法标记

public:
	/*
	函数名：	ComputeRP
	功能：	对当前的结果列表，计算其对应的RP曲线
	输入：	参数1：源图片的索引（用来计算图像所对应的类别）；参数2：检索结果列表
	输出：	空
	*/
	void ComputeRP(int srcIndex , List<Image*>& resultList);

	/*
	函数名：	OutputResult
	功能：	输出当前存储的检索结果到外部文件中
	输入：	外部目标文件的引用
	输出：	空
	*/
	void OutputResult(ofstream& outFile);

public:
	RPResult();

};

#endif