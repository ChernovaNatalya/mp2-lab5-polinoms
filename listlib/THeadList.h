#pragma once
#include "TList.h"
using namespace std;


template<class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;  // заголовок, pFirst - звено за pHead
public:
	THeadList();
	~THeadList();
	void InsertFirst(T item); // вставка звеньев после заголовка
	void DeleteFirst(); // удалить первое звено
	void Clear();
	void Reset();
	void GoNext();
};

template<class T>
THeadList<T>::THeadList():TList<T>()
{
	pHead = new TNode<T>();
}

template<class T>
THeadList<T>::~THeadList()
{
	delete this->pHead;
}

template <class T>
void THeadList<T>::InsertFirst(T item)
{
	TList<T>::InsertFirst(item);
}

template <class T>
void THeadList<T>::DeleteFirst()
{
	TList<T>::DeleteFirst();
	if (length != 0) {
		pHead = pFirst;
	}
	else {
		pHead = NULL;
	}
}

template<class T>
void THeadList<T>::Reset()
{
	TList<T>::Reset();
	pPrevious = pLast;
}

template <class T>
void THeadList<T>::Clear() {

	Reset();
	while (length > 0) { 
		DeleteFirst(); 
	}
	pCurrent = pStop; 
	pPrevious = pStop; 
	pLast = pStop;
	pFirst = pStop;
	length = 0;
}

template<class T>
void THeadList<T>::GoNext()
{
	if (pCurrent->pNext == pStop) {
		THeadList<T>::Reset();
	}
	else {
		TList<T>::GoNext();
	}
}