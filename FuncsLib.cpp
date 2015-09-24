/******************************************************************
文件名：		FuncsLib.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		程序中一些常用的函数库的的实现。
******************************************************************/

#include "stdafx.h"
#include "FuncsLib.h"
#include "DataStruct.h"
#include <string>
using namespace std;;

bool FuncsLib::IsFileExist(const char* pFileAddName , bool throwErrorMsg)
{
	FILE* filePtr = NULL;
	fopen_s(&filePtr , pFileAddName , "r");

	if(filePtr)
	{
		fclose(filePtr);

		return true;
	}

	if(throwErrorMsg)
	{
		char errorStr[128];
		sprintf_s(errorStr , sizeof(char) * 128 , "Cann't find the file: %s" , pFileAddName);
		MessageBoxA(NULL , errorStr , "Error" , MB_OK | MB_ICONERROR);
	}

	return false;
}

bool FuncsLib::IsFolderExistA(const char* pFolderString)
{
	WIN32_FIND_DATAA wfData;
	bool rValue = false;

	HANDLE hFind = FindFirstFileA(pFolderString , &wfData);

	if((hFind != INVALID_HANDLE_VALUE) && (wfData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = true;
	}

	FindClose(hFind);

	return rValue;
}

bool FuncsLib::FindDstFile(char* pDstFolder , char* pDstFileName , char* pDstFileFullPath , bool isRecursive)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATAA FindFileData;
	strcpy_s(szFind , sizeof(char) * MAX_PATH , pDstFolder);
	strcat_s(szFind , "\\*.*");
	HANDLE hFind = ::FindFirstFileA(szFind , &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		return false;
	}

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// Find file in the sub-folder
			if(isRecursive && FindFileData.cFileName[0] != '.')
			{
				char subFolder[MAX_PATH];
				sprintf_s(subFolder , sizeof(char) * MAX_PATH , "%s\\%s" , pDstFolder , FindFileData.cFileName);
				if(FindDstFile(subFolder , pDstFileName , pDstFileFullPath , isRecursive))
				{
					return true;
				}
			}
		}
		else
		{
			// Test whether current file is the defined files
			if(_stricmp(FindFileData.cFileName , pDstFileName) == 0)
			{

				sprintf_s(pDstFileFullPath , sizeof(char) * MAX_PATH , "%s\\%s" , pDstFolder , pDstFileName);
				return true;
			}
		}

		if(!FindNextFileA(hFind , &FindFileData))
		{
			break;
		}
	}
	FindClose(hFind);

	return false;
}

void FuncsLib::FindFiles(char* pDstPath , char* pDstFilePostfix , List<string>* pDstStringList , bool isRecursive)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATAA FindFileData;
	strcpy_s(szFind , sizeof(char) * MAX_PATH , pDstPath);
	strcat_s(szFind , "\\*.*");
	HANDLE hFind = ::FindFirstFileA(szFind , &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// Ignore the Sub-folder
			if(isRecursive && FindFileData.cFileName[0] != '.')
			{
				char subFolder[MAX_PATH];
				sprintf_s(subFolder , sizeof(char) * MAX_PATH , "%s\\%s" , pDstPath , FindFileData.cFileName);
				FindFiles(subFolder , pDstFilePostfix , pDstStringList , isRecursive);
			}
		}
		else
		{
			if(pDstStringList)
			{
				// Test whether current file is the defined files
				size_t srcStrLength     = strlen(FindFileData.cFileName);
				size_t dstPostfixLength = strlen(pDstFilePostfix);
				if(srcStrLength >= dstPostfixLength && 
				   _stricmp(FindFileData.cFileName + srcStrLength - dstPostfixLength , pDstFilePostfix) == 0)
				{
					string dstItem = FindFileData.cFileName;
					pDstStringList->AddItem(dstItem);
				}
			}
		}

		if(!FindNextFileA(hFind , &FindFileData))
		{
			break;
		}
	}
	FindClose(hFind);
}

void FuncsLib::ListDstFilesInFolder(char* pDstFloderString , char* pDstFilePostfix , List<string>* pDstStringList , bool isRecursive)
{
	FindFiles(pDstFloderString , pDstFilePostfix , pDstStringList , isRecursive);
}