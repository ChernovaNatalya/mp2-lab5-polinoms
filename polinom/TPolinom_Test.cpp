#include <iostream>
#include <ctime>
#include "TList.h"
#include "TPolinom.h"
using namespace std;

int main()
{
	
	cout << "TList" << endl;
	TList<int> t;
	cout << "Insert First 1, 2" << endl;
	t.InsertFirst(1);
	t.InsertFirst(2);
	cout << t << endl;
	cout << "Delete First" << endl;
	t.DeleteFirst();
	cout << t << endl;
	cout << "InsertLast 3, 4" << endl;
	t.InsertLast(3);
	t.InsertLast(4);
	cout << t << endl;
	cout << "Go Next" << endl;
	t.GoNext();
	cout << t << endl;
	cout << "Go Next" << endl;
	t.GoNext();
	cout << t << endl;
	cout << "Insert Current Element" << endl;
	t.InsertCurrent(5);
	cout << t << endl;
	cout << "Delete Current" << endl;
	t.DeleteCurrent();
	cout << t << endl;
	try {
		cout << "Go Next" << endl;
		t.GoNext();
		cout << t << endl;
	}
	catch (...) { 
		cout << " Error!!! End is: " << t.IsEnd() << endl << endl; 
	}
	cout << "Reset" << endl;
	t.Reset();
	cout << t << endl;
	cout << "IsEmpty? = " << t.IsEmpty() << endl << endl;

	cout << "Delete First until It's Empty" << endl;
	while (!t.IsEmpty()) {
		t.DeleteFirst();
		cout << t;
	}
	cout << "IsEmpty: " << t.IsEmpty() << endl << endl;
	cout << endl << endl << endl;
	
	
	cout << "THeadList" << endl;
	THeadList<int> h1;
	cout << "Insert First 1, 2" << endl;
	h1.InsertFirst(1);
	h1.InsertFirst(2);
	cout << h1 << endl;
	cout << "Delete First" << endl;
	h1.DeleteFirst();
	cout << h1 << endl;
	cout << "InsertLast 3, 4" << endl;
	h1.InsertLast(3);
	h1.InsertLast(4);
	cout << h1 << endl;
	cout << "Go Next" << endl;
	h1.GoNext();
	cout << h1 << endl;
	cout << "Go Next" << endl;
	h1.GoNext();
	cout << h1 << endl;
	cout << "Insert Current Element" << endl;
	h1.InsertCurrent(5);
	cout << h1 << endl;
	cout << "Delete Current Element" << endl;
	h1.DeleteCurrent();
	cout << h1 << endl;
	try {
		cout << "Go Next" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << "Error!!! End is:" << h1.IsEnd() << endl << endl; }
	try {
		cout << "Go Next" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << "Error!!! End is:" << h1.IsEnd() << endl << endl; }
	try {
		cout << "GoNext" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << "Error!!! End is:" << h1.IsEnd() << endl << endl; }
	try {
		cout << "Go Next" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << "Error!!! End is:" << h1.IsEnd() << endl << endl; }
	cout << "Reset" << endl;
	h1.Reset();
	cout << h1 << endl;
	cout << "IsEmpty: " << h1.IsEmpty() << endl << endl;

	cout << "Delete First until It's Empty" << endl;
	while (!t.IsEmpty()) {
		h1.DeleteFirst();
		cout << h1;
	}
	cout << "IsEmpty: " << h1.IsEmpty() << endl << endl;
	cout << endl << endl << endl;



	cout << "TMonom" << endl;
	TMonom m1(4, 1, 2, 2);
	TMonom m2(4, 1, 2, 2);
	cout << "m1: " << m1 << endl;
	cout << "m2: " << m2 << endl;
	cout << "m1 == m2 " << (m1 == m2) << endl << endl;
	m2.SetCoef(3);
	cout << "m1: " << m1 << endl;
	cout << "m2: " << m2 << endl;
	cout << "m1 == m2 " << (m1 == m2) << endl;
	cout << "m1 < m2 " << (m1 < m2) << endl;
	cout << "m1 > m2 " << (m1 > m2) << endl << endl;
	m1.SetIndex(11);
	cout << "m1: " << m1 << endl;
	cout << "m2: " << m2 << endl;
	cout << "m1 == m2 " << (m1 == m2) << endl;
	cout << "m1 < m2 " << (m1 < m2) << endl;
	cout << "m1 > m2 " << (m1 > m2) << endl << endl;
	cout << endl << endl << endl;

	
	cout << "TPolinom" << endl;
	TPolinom p1;
	p1.AddMonom(TMonom(3, 1, 2, 3));
	p1.AddMonom(TMonom(4, 5, 6, 7));
	TPolinom p2;
	p2.AddMonom(TMonom(3, 1, 2, 3));
	p2.AddMonom(TMonom(4, 5, 6, 7));
	cout << "p1" << endl << p1 << endl << endl;
	cout << "p2" << endl << p2 << endl << endl;
	cout << "p1 == p2 " << (p1 == p2) << endl;
	p2.AddMonom(TMonom(3, 2, 7, 2));
	p2.AddMonom(TMonom(2, 4, 3, 6));
	p2.AddMonom(TMonom(1, 5, 8, 3));
	p1.Clear();
	p1.AddMonom(TMonom(1, 3, 6, 3));
	cout << "p1" << endl << p1 << endl << endl;
	cout << "p2" << endl << p2 << endl << endl;
	cout << "p1 == p2 " << (p1 == p2) << endl;

	/*
	unsigned int start_time = clock();
	int n = 6000;
	TPolinom p;
	for (int i = 0; i < n; i++) {
		p.AddMonom(TMonom(i, i, i, i));
	}
	//cout << p << endl;
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	cout << search_time;
	*/
}