/******************************************************************
文件名：		FuncsLib.h
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		程序中一些常用的函数库的的实现。
******************************************************************/

#ifndef __FuncsLib_H__
#define __FuncsLib_H__

#include <string>
using namespace std;
#include "DataStruct.h"

#pragma warning (disable: 4251)

/*
公共方法中主要实现了对某一目录内所有文件进行遍历与扫描
*/
class  FuncsLib
{
public:
	static bool     IsFileExist(const char* pFileName , bool throwErrorMsg);
	static bool     IsFolderExistA(const char* pFolderString);
	static void     FindFiles(char* pDstPath , char* pDstFilePostfix , List<string>* pDstStringList , bool isRecursive);
	static void     ListDstFilesInFolder(char* pDstFloderString , char* pDstFilePostfix , List<string>* pDstStrList , bool isRecursive = false);
	static bool     FindDstFile(char* pDstFolder , char* pDstFileName , char* pDstFileFullPath , bool isRecursive);
};

#endif // __FuncsLib_H__