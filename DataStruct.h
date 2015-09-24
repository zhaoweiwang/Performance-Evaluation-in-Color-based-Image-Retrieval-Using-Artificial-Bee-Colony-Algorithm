/******************************************************************
文件名：		DataStruct.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		程序中用到的一些常用数据结构实现（对于模板等的使用主要代码均放置于头文件内部）
******************************************************************/

#ifndef __DataStruct_H__
#define __DataStruct_H__

#define S_ERROR -1L
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }

#pragma warning (disable: 4251)

/******************************************************************
自定义实现的链表模板类，用来实现图像库的存储
******************************************************************/
#define INITIAL_LIST_SIZE 5
template<class dataType>
class  List
{
private:
	UINT      mMaxSize;
	UINT      mCurSize;
	dataType* mpBuffer;

public:
	void      SetListSize(UINT listSize);
	dataType* GetListBufferPointer();
	UINT      GetListSize();
	UINT      AddItem(dataType& itemData);
	void      GetItem(UINT itemIndex , dataType* itemDataPtr);
	dataType* GetItemPtr(UINT itemIndex);
	void      CompactList();
	void      EmptyList();

	List<dataType>& operator = (List<dataType>& list);
	dataType& operator[](UINT dataIndex);

	void      Reset();

public:
	List();
	~List();
};

template<class dataType>
dataType& List<dataType>::operator[](UINT dataIndex)
{
	if(mCurSize > dataIndex && dataIndex >= 0)
	{
		return mpBuffer[dataIndex];
	}
	return mpBuffer[0];
}

template<class dataType>
List<dataType>& List<dataType>::operator = (List<dataType>& list)
{
	SAFE_DELETE_ARRAY(mpBuffer);

	mCurSize = list.GetListSize();
	mMaxSize = mCurSize;

	mpBuffer = new dataType[mMaxSize];

	for(UINT i = 0 ; i < mCurSize ; ++i)
	{
		mpBuffer[i] = list.mpBuffer[i];
	}

	return *this;
}

template<class dataType>
dataType* List<dataType>::GetListBufferPointer()
{
	return mpBuffer;
}

template<class dataType>
UINT List<dataType>::GetListSize()
{
	return mCurSize;
}

template<class dataType>
void List<dataType>::SetListSize(UINT listSize)
{
	mCurSize = listSize;

	if(mCurSize >= mMaxSize)
	{
		mMaxSize = mCurSize;

		SAFE_DELETE_ARRAY(mpBuffer);

		mpBuffer = new dataType[mMaxSize];
	}
}

template<class dataType>
void List<dataType>::Reset()
{
	SetListSize(0);
}

template<class dataType>
void List<dataType>::EmptyList()
{
	mCurSize = 0;
	SAFE_DELETE_ARRAY(mpBuffer);
	mMaxSize = INITIAL_LIST_SIZE;
	mpBuffer  = new dataType[mMaxSize];
}

template<class dataType>
UINT List<dataType>::AddItem(dataType& itemData)
{
	if(mCurSize >= mMaxSize)
	{
		mMaxSize *= 2;
		dataType* tempList = new dataType[mMaxSize];

		for(UINT i = 0 ; i < mCurSize ; ++i)
		{
			tempList[i] = mpBuffer[i];
		}
		SAFE_DELETE_ARRAY(mpBuffer);

		mpBuffer = tempList;
	}

	mpBuffer[mCurSize++] = itemData;

	return mCurSize - 1;
}

template<class dataType>
void List<dataType>::GetItem(UINT itemIndex , dataType* itemDataPtr)
{
	if(itemIndex >= 0 && itemIndex < mCurSize)
	{
		*itemDataPtr = mpBuffer[itemIndex];
	}
}

template<class dataType>
dataType* List<dataType>::GetItemPtr(UINT itemIndex)
{
	if(itemIndex >= 0 && itemIndex < mCurSize)
	{
		return &mpBuffer[itemIndex];
	}

	return NULL;
}

template<class dataType>
void List<dataType>::CompactList()
{
	dataType* tempList = new dataType[mCurSize];

	//memcpy(tempList , mpBuffer , sizeof(dataType) * mCurSize);

	for(UINT i = 0 ; i < mCurSize ; ++i)
	{
		tempList[i] = mpBuffer[i];
	}

	SAFE_DELETE_ARRAY(mpBuffer);
	mpBuffer = tempList;
	mMaxSize = mCurSize;
}

template<class dataType>
List<dataType>::List()
{
	mMaxSize = INITIAL_LIST_SIZE;
	mCurSize = 0;
	mpBuffer  = new dataType[mMaxSize];
}

template<class dataType>
List<dataType>::~List()
{
	SAFE_DELETE_ARRAY(mpBuffer);
}

#endif //__DataStruct_H__