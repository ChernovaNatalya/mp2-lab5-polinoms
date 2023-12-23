#pragma once
#include <iostream>
#include "TNode.h"

using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pFirst; // ������ �����
	TNode<T>* pCurrent; // ������� �����
	TNode<T>* pPrevious; // ����� ����� �������
	TNode<T>* pLast; // ��������� �����
	TNode<T>* pStop; // �������� ���������, ����������� ����� ������
	int length; // ���������� ������� � ������

public:

	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // ������ ���� ?
	
	// ������� �������
	void InsertFirst(T item); // ����� ������
	void InsertCurrent(T item); // ����� ������� 
	void InsertLast(T item);  // �������� ��������� 

	// �������� �������
	void DeleteFirst(); // ������� ������ ����� 
	void DeleteCurrent(); // ������� ������� �����

	void GoNext(); // ����� ������ �������� �����
	// (=1 ����� ���������� GoNext ��� ���������� ����� ������)

	void Reset(); // ���������� �� ������ ������
	bool IsEnd();  // ������ �������� ?

	T GetCurrentItem(); //�������� ������� ��������
	void SetCurrentItem(T item) { pCurrent->value = item; }  //���������� ������� ��������

	friend ostream& operator<<(ostream& os, const TList<T>& obj) {
		//os << &obj;
		if (obj.length == 0) { 
			os << "length = 0 \n[\n]" << endl; 
			return os; 
		}
		try { 
			os << "first = " << obj.pFirst->value << endl; 
		}
		catch (...) { 
			os << "no first" << endl; 
		}
		try { 
			os << "last = " << obj.pLast->value << endl; 
		}
		catch (...) { 
			os << "no last" << endl; 
		}
		os << "length = " << obj.length << endl;
		TNode<T>* tmp = obj.pFirst;
		os << "{" << endl;
		while (tmp != obj.pStop)
		{

			os << tmp->value;// << " next" << tmp->pNext;
			if (tmp == obj.pCurrent) {
				os << "<-- current";
			}
			if (tmp == obj.pPrevious) {
				os << "<-- pr";
			}
			os << endl;
			tmp = tmp->pNext;
		}
		os << "}" << endl;
		return os;
	}
};
template <class T>
TList<T>::TList()
{
	length = 0;
	pStop = NULL;
	pFirst = NULL;
	pPrevious = NULL;
	pLast = NULL;

}

template <class T>
TList<T>::~TList()
{
	length = 0;
	pStop = NULL;
	pFirst = NULL;
	pPrevious = NULL;
	pLast = NULL;
}

template <class T>
bool TList<T>::IsEmpty()
{
	if (length == 0) {

		return true;
	}
	return false;
}

template <class T>
void TList<T>::InsertFirst(T item) // ����� ������
{
	if (length == 0) {
		TNode<T>* tnd = new TNode<T>();
		tnd->value = item;		
		tnd->pNext = pStop;
		pFirst = tnd;
		pCurrent = pFirst;
		pLast = pFirst;
	}
	else {
		TNode<T>* tnd = new TNode<T>();
		tnd->value = item;
		tnd->pNext = pFirst;
		if (pCurrent == pFirst) {
			pPrevious = tnd;
			pCurrent = pFirst;
		}
		pFirst = tnd;
	}
	length++;
}

template <class T>
void TList<T>::InsertCurrent(T item) // ����� ������� 
{
	if ((length == 0)||(pCurrent == pFirst)) {
		InsertFirst(item);
		return;
	}
	TNode<T>* tnd = new TNode<T>();
	tnd->value = item;
	tnd->pNext = pCurrent;
	pPrevious->pNext = tnd;
	pPrevious = tnd;
	length++;
}

template <class T>
void TList<T>::InsertLast(T item) // �������� ���������
{
	if (IsEmpty()) { 
		InsertFirst(item); 
		return; 
	}
	TNode<T>* tnd = new TNode<T>();
	tnd->value = item;
	tnd->pNext = pStop;
	pLast->pNext = tnd;
	pLast = tnd;
	length++;
}

template <class T>
void TList<T>::DeleteFirst() // ������� ������ �����
{
	if (length == 0) {
		throw "is Empty";
	}
	if (pCurrent == pFirst) {
		pCurrent = pFirst->pNext;
	}
	if (pLast == pFirst) {
		pLast = pFirst->pNext;
	}
	if (pPrevious == pFirst) {
		pPrevious = pFirst->pNext;
	}
	TNode<T>* tnd = pFirst;
	pFirst = pFirst->pNext;
	tnd = nullptr;
	length--;
}

template <class T>
void TList<T>::DeleteCurrent() // ������� ������� �����
{
	if (length == 0) {
		throw "is Empty";
	}
	if (pCurrent == pStop) {
		throw "Currend in end";
	}
	if ((pCurrent == pFirst) && (length == 1)) { 
		DeleteFirst(); 
		length--;  
		return; 
	}
	if (pCurrent->pNext == pStop) {
		pLast = pPrevious;
		pLast->pNext = pStop;
		delete pCurrent;
		Reset();
		length--;
		return;
	}
	TNode<T>* tnd = pCurrent->pNext;
	delete pCurrent;
	pCurrent = tnd;
	pPrevious->pNext = pCurrent;
	tnd = nullptr;
	length--;
}

template <class T>
T TList<T>::GetCurrentItem() //�������� ������� ��������
{
	if (length == 0) {
		throw "It's empty";
	}
	if (pCurrent == pStop)
		throw "It's over";
	return pCurrent->value;
}

template <class T>
void TList<T>::Reset() // ���������� �� ������ ������
{
	pCurrent = pFirst;
	pPrevious = NULL;
}

template <class T>
void TList<T>::GoNext()// ����� ������ �������� �����
	// (=1 ����� ���������� GoNext ��� ���������� ����� ������)
{
	try {
		if (IsEnd()) {
			throw "This is end";
		}
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;
	}
	catch (...) {}
}

template <class T>
bool TList<T>::IsEnd() // ������ �������� ?
{
	if (IsEmpty()) {
		return true;
	}
	if (pCurrent == pStop) {
		return true;
	}
	if (pCurrent->pNext == pStop) { 
		return true; 
	}
	return false;
}





