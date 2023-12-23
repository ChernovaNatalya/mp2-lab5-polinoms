#pragma once
struct TMonom
{
	double coef; // коэффициент монома
	int index; // индекс (свертка степеней)


	TMonom() { }

	TMonom(double coef, int degX, int degY, int degZ) {
		this->coef = coef;
		this->index = degX*100 + degY*10 + degZ;
	}

	void SetCoef(int cval) { 
		coef = cval; 
	}
	int GetCoef(void) { 
		return coef; 
	}

	void SetIndex(int ival) { 
		index = ival; 
	}
	int GetIndex(void) { 
		return index; 
	}


	bool operator==(const TMonom& other) {
		if ((index == other.index) && (coef == other.coef)) {
			return true;
		}
		return false;
	}
	
	bool operator>(const TMonom& other) {
		if (index > other.index) {
			return true;
		}
		if (index < other.index) {
			return false;
		}
		if (coef > other.coef) {
			return true;
		}
		return false;
	}

	bool operator<(const TMonom& other) {
		if (index < other.index) {
			return true;
		}
		if (index > other.index) {
			return false;
		}
		if (coef < other.coef) {
			return true;
		}
		return false;
	}

	TMonom  operator=(const TMonom& other) {
		if (*this == other) {
			return *this;
		}
		this->coef = other.coef;
		this->index = other.index;
		return *this;
	}
	friend ostream& operator<<(ostream& os, const TMonom& obj) {
		if (&obj == nullptr) { 
			return os; 
		}
		os << obj.coef;
		int in = obj.index;
		if ((in / 100 != 0) && (in / 100 != 1)) {
			os<<"x^";
			os<<std::to_string(in/100);
		}
		if (in / 100 == 1) {
			os << "x";
		}
		in %= 100;
		if ((in / 10 != 0) && (in / 100 != 1)) {
			os << "y^";
			os << std::to_string(in / 10);
		}
		if (in / 10 == 1) {
			os << "y";
		}
		in %= 10;
		if ((in != 0) && (in != 1)) {
			os << "z^";
			os << std::to_string(in);
		}
		if (in == 1) {
			os << "z";
		}
		return os;
	}
};