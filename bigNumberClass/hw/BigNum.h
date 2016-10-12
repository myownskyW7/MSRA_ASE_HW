#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigNum
{
	private:
		vector<int> number;
		int sign;
	public:
		BigNum() { sign = 0; };
		BigNum(int num);
		BigNum(string num);
		BigNum(const BigNum& bigNum);
		BigNum &operator = (const BigNum& bigNum);
		friend istream& operator>>(istream& in, BigNum& bigNum);
		friend ostream& operator<<(ostream& out, BigNum& bigNum);
		bool unsignedBigger(const BigNum& b) const;
		bool unsignedEqual(const BigNum& b) const;
		bool operator>(const BigNum& b) const;
		bool operator>(const int& b) const;
		bool operator==(const BigNum& b) const;
		bool operator==(const int& b) const;
		BigNum unsignedAdd(const BigNum& b) const;
		BigNum unsignedSub(const BigNum& b) const;
		BigNum operator+(const BigNum& b) const;
		BigNum operator+(int b) const;
		BigNum operator-(const BigNum& b) const;
		BigNum operator-(int b) const;
		BigNum operator*(const BigNum& b) const;
		BigNum operator*(int b) const;
		BigNum operator/(const BigNum& b) const;
		BigNum operator/(int b) const;
};