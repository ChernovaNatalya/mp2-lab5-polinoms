#pragma once
#include <string>
#include "THeadList.h"
#include "TMonom.h"

const int nonDisplayedZeros = 4; // ���������� �������������� ����� ��� ������ ������������ ��������
// ���-�� �������� ����� ������� = 6 - nonDisplayedZeros


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other); // ������������
	TPolinom& operator+(TPolinom& q); // �������� ���������

	// ������������� ����� �����������:
	void AddMonom(TMonom newMonom); // ���������� ������
	TPolinom MultMonom(TMonom monom); // ��������� �������
	TPolinom AddPolinom(TPolinom& other); // ���������� ��������
	TPolinom operator*(double coef); // ��������� �������� �� �����
	TPolinom operator* (TPolinom& other); // ��������� ���������
	bool operator==(TPolinom& other); // ��������� ��������� �� ���������
	string ToString(); // ������� � ������
};

TPolinom::TPolinom() :THeadList<TMonom>::THeadList()
{
	//� ��� ���-�� ����?
}

TPolinom::TPolinom(TPolinom& other) :THeadList<TMonom>::THeadList()
{
	TNode<TMonom>* tnd = other.pCurrent;
	TMonom tmon;
	other.Reset();

	while (!other.IsEnd()) {
		TMonom tmon = other.pCurrent->value;
		InsertLast(tmon);
		other.GoNext();
	}
	if (!other.IsEmpty()) {
		TMonom tmon = other.pCurrent->value;
		InsertLast(tmon);
	}
	while (other.pCurrent != tnd) {
		other.GoNext();
		GoNext();
	}
	length = other.length;
	tnd = nullptr;
	return;
}

TPolinom& TPolinom::operator=(TPolinom& other)
{
	Clear();
	if (other.IsEmpty()) {
		return *this;
	}
	TNode<TMonom>* st = other.pCurrent;
	TMonom tmp;
	other.Reset();
	while (!other.IsEnd()) {
		tmp = other.pCurrent->value;
		InsertLast(tmp);
		other.GoNext();
	}
	tmp = other.pCurrent->value;
	InsertLast(tmp);
	other.GoNext();
	while (other.pCurrent != st) {
		other.GoNext(); GoNext();
	}
	length = other.length;
	st = nullptr;
	return *this;
}

void TPolinom::AddMonom(TMonom m)
{
	if (m.GetCoef() == 0) return;
	Reset();
	TMonom* monom = new TMonom(m);
	if (!IsEmpty()) {
		while ((GetCurrentItem().index < m.index) && (!IsEnd())) GoNext();
		if (GetCurrentItem().index == m.index) {
			pCurrent->value.coef += m.coef;
			if (pCurrent->value.coef == 0) {
				DeleteCurrent();
				length++;
				return;
			}
			return;
		}
		if (IsEnd()) {
			if (GetCurrentItem().index > m.index) {
				InsertFirst(m);
			}
			else {
				InsertLast(*monom);
				return;
			}
		}
		else InsertCurrent(*monom);

	}
	else  InsertFirst(*monom);
}

TPolinom TPolinom::MultMonom(TMonom monom)
{
	if (IsEmpty()) {
		return *this;
	}
	TPolinom tmp(*this);
	Clear();
	tmp.Reset();
	while (!tmp.IsEnd())
	{
		if (tmp.pCurrent->value == monom) {
			AddMonom(monom);
		}
		tmp.GoNext();
	}
	if (tmp.pCurrent->value == monom) {
		AddMonom(monom);
	}
	return *this;
}

TPolinom& TPolinom::operator+(TPolinom& other)
{
	if (other.IsEmpty()) {
		return *this;
	}
	if (this->IsEmpty()) {
		return other;
	}
	if (length >= other.length) {
		TPolinom* tmp = new TPolinom(*this);
		other.Reset();
		while (!other.IsEnd()) {
			tmp->AddMonom(other.GetCurrentItem());
			other.GoNext();
		}
		if (!other.IsEmpty()) {
			tmp->AddMonom(other.GetCurrentItem());
		}
		return *tmp;
	}
	else {
		return (other + *this);
	}
	return *this;
}

TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	return (*this + other);
}

bool TPolinom::operator==(TPolinom& other)
{
	if (length != other.length) {
		return false;
	}
	Reset();
	other.Reset();
	for (int i = 0; i < length; i++) {
		TMonom a, b;
		a = other.GetCurrentItem();
		b = GetCurrentItem();
		GoNext();
		other.GoNext();
		if (!(a == b)) {
			return false;
		}
	}
	return true;
}

TPolinom TPolinom::operator*(double coef)
{
	Reset();
	if (IsEmpty()) {
		return *this;
	}
	TPolinom* tmp = new TPolinom(*this);
	tmp->Reset();
	while (!tmp->IsEnd()) {
		tmp->pCurrent->value.coef *= coef;
		tmp->GoNext();
	}
	tmp->pCurrent->value.coef *= coef;
	return *tmp;
}

string TPolinom::ToString()
{
	string result = "";
	if (IsEmpty()) return result;
	Reset();
	TMonom tmp;
	while (!IsEnd())
	{
		tmp = GetCurrentItem();
		result += std::to_string(tmp.GetCoef());
		int a = tmp.GetIndex();
		if ((a / 100 != 0) && (a / 100 != 1)) {
			result += "X^";
			result += std::to_string(a / 100);
		}
		if (a / 100 == 1) {
			result += "X";
		}
		a %= 100;
		if ((a / 10 != 0) && (a / 10 != 1)) {
			result += "Y^";
			result += std::to_string(a / 10);
		}
		if (a / 10 == 1) { 
			result += "Y"; 
		}
		a %= 10;
		if ((a != 0) && (a != 1)) { 
			result += "Z^"; 
			result += std::to_string(a); 
		}
		if (a == 1) { 
			result += "Z"; 
		}
		result += ' ';
		GoNext();
	}
	tmp = GetCurrentItem();
	result += std::to_string(tmp.GetCoef());
	int a = tmp.GetIndex();
	if ((a / 100 != 0) && (a / 100 != 1)) { 
		result += "X^"; 
		result += std::to_string(a / 100); 
	}
	if (a / 100 == 1) { 
		result += "X"; 
	}
	a %= 100;
	if ((a / 10 != 0) && (a / 10 != 1)) { 
		result += "Y^"; 
		result += std::to_string(a / 10); 
	}
	if (a / 10 == 1) { 
		result += "Y"; 
	}
	a %= 10;
	if ((a != 0) && (a != 1)) { 
		result += "Z^"; 
		result += std::to_string(a); 
	}
	if (a == 1) { 
		result += "Z"; 
	}
	return result;
}

TPolinom::TPolinom(string str)
{
	bool st = 0;
	char c;
	int i = 0;
	TMonom m;

	int* mon_ind = new int[3];
	mon_ind[0] = 0; mon_ind[1] = 0; mon_ind[2] = 0;
	int w = 0;
	int p = 1;
	while (i < str.size()) {
		c = str[i];
		if (c == ' ') { 
			i++; 
			continue; 
		}
		if ((c == '-') || (c == '+')) {
			if (c == '+') {
				p = 1;
			}
			else {
				p = -1;
			}
			i++;
			continue;
		}

		if ((c >= '0') && (c <= '9')) {
			size_t d = 0;
			double a = stod(&str[i], &d);
			if (!st) m.SetCoef(p * a);
			i += d;
			continue;
		}
		if (c == 'X') {
			if ((i + 1 < str.size()) && (str[i + 1] != 'Y')) {
				w++;
			}
			if ((i + 1 < str.size()) && (str[i + 1] == '^')) {
				i += 2;
				size_t d = 0;
				int a = stoi(&str[i], &d);
				i += d;
				mon_ind[0] = a;
			}
			else { 
				mon_ind[0] = 1; 
				i++; 
			}
			w++;
			c = str[i];
		}
		if (c == 'Y') {
			if ((i + 1 < str.size()) && (str[i + 1] != 'Z')) {
				w++;
			}
			if ((i + 1 < str.size()) && (str[i + 1] == '^')) {
				i += 2;
				size_t d = 0;
				int a = stoi(&str[i], &d);
				i += d;
				mon_ind[1] = a;
			}
			else { mon_ind[1] = 1; i++; }
			w++;
			c = str[i];
		}
		if (c == 'Z') {
			if ((i + 1 < str.size()) && (str[i + 1] == '^')) {
				i += 2;
				size_t d = 0;
				int a = stoi(&str[i], &d);
				i += d;
				mon_ind[2] = a;
			}
			else { mon_ind[2] = 1; i++; }
			w++;
			c = str[i];
		}
		if (w >= 3) {
			m.SetIndex(mon_ind[0] * 100 + mon_ind[1] * 10 + mon_ind[2]);
			mon_ind[0] = 0;
			mon_ind[1] = 0;
			mon_ind[2] = 0;
			AddMonom(m);
			m.coef = 0;
			w = 0;
			i++;
			continue;
		}
		i++;
	}
}
