#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "BigNum.h"
BigNum::BigNum(int num) {
	if (num >= 0) {
		sign = 0;
	}
	else {
		sign = 1;
		num = -num;
	}
	while (num != 0) {
		number.push_back(num % 10);
		num /= 10;
	}
	reverse(number.begin(), number.end());
}
BigNum::BigNum(string num) {
	if (num[0] == '-') {
		sign = 1;
	}
	else {
		sign = 0;
	}
	for (int i = sign; i < num.size(); i++) {
		number.push_back(num[i] - '0'); 
	}
}
BigNum::BigNum(const BigNum& bigNum) {
	sign = bigNum.sign;
	for (int i = 0; i < bigNum.number.size(); i++) {
		number.push_back(bigNum.number[i]);
	}
}
BigNum& BigNum::operator = (const BigNum& bigNum) {
	if (&bigNum != this) {
		sign = bigNum.sign;
		number.clear();
		number.resize(0);
		for (int i = 0; i < bigNum.number.size(); i++) {
			number.push_back(bigNum.number[i]);
		}
		return *this;
	}
	else {
		return *this;
	}
}
istream& operator>>(istream& in, BigNum& bigNum) {
	string num;
	in >> num;
	bigNum.number.swap(vector<int>());
	if (num[0] == '-') {
		bigNum.sign = 1;
	}
	else {
		bigNum.sign = 0;
	}
	for (int i = bigNum.sign; i < num.size(); i++) {
		bigNum.number.push_back(num[i] - '0');
	}
	if (bigNum.sign == 1)
		cout << "negative" << endl;
	return in;
}
ostream& operator<<(ostream& out, BigNum& bigNum) {
	if (bigNum.sign == 1)
		cout << "-";
	for (int i = 0; i < bigNum.number.size(); i++) {
		out << bigNum.number[i];
	}
	return out;
}
bool BigNum::unsignedBigger(const BigNum& b) const {
	if (number.size() > b.number.size()) {
		return true;
	}
	else if(number.size() < b.number.size()){
		return false;
	}
	else {
		for (int i = 0; i<number.size(); i++) {
			if (number[i] > b.number[i]) {
				return true;
			}
			else if (number[i] < b.number[i]) {
				return false;
			}
		}
		return false;
	}
}
bool BigNum::unsignedEqual(const BigNum& b) const {
	if (number.size() == b.number.size()) {
		for (int i = 0; i < number.size(); i++) {
			if (number[i] != b.number[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}
bool BigNum::operator>(const BigNum& b) const {
	if (sign == 0) {
		if (b.sign == 0) {
			return this->unsignedBigger(b);
		}
		else {
			return true;
		}
	}
	else {
		if (b.sign == 0) {
			return false;
		}
		else {
			return !this->unsignedBigger(b);
		}
	}
}
bool BigNum::operator>(const int& b) const {
	BigNum t(b);
	return *this > t;
}
bool BigNum::operator==(const BigNum& b) const {
	return this->unsignedEqual(b) && (sign == b.sign);
}
bool BigNum::operator==(const int& b) const {
	BigNum t(b);
	return *this == t;
}
BigNum BigNum::unsignedAdd(const BigNum& b) const {
	BigNum t1(*this);
	BigNum t2(b);
	BigNum result;
	reverse(t1.number.begin(), t1.number.end());
	reverse(t2.number.begin(), t2.number.end());
	int forward = 0;
	int len_max = max(t1.number.size(), t2.number.size());
	if (t1.number.size() < len_max) {
		for (int i = t1.number.size(); i < len_max; i++) {
			t1.number.push_back(0);
		}
	}
	else if (t2.number.size() < len_max) {
		for (int i = t2.number.size(); i < len_max; i++) {
			t2.number.push_back(0);
		}
	}
	for (int i = 0; i < len_max; i++) {
		result.number.push_back((t1.number[i] + t2.number[i]+forward) % 10);
		forward = (t1.number[i] + t2.number[i] + forward) / 10;
	}
	if (forward == 1) {
		result.number.push_back(forward);
	}
	reverse(result.number.begin(),result.number.end());
	return result;
}
BigNum BigNum::unsignedSub(const BigNum& b) const {
	BigNum t1(*this);
	BigNum t2(b);
	BigNum result;
	reverse(t1.number.begin(), t1.number.end());
	reverse(t2.number.begin(), t2.number.end());
	int backward = 0;
	int len_max = max(t1.number.size(), t2.number.size());
	if (t1.number.size() < len_max) {
		for (int i = t1.number.size(); i < len_max; i++) {
			t1.number.push_back(0);
		}
	}
	else if (t2.number.size() < len_max) {
		for (int i = t2.number.size(); i < len_max; i++) {
			t2.number.push_back(0);
		}
	}
	if (t1 == t2) {
		result.number.push_back(0);
		return result;
	}
	for (int i = 0; i < len_max; i++) {
		if (t1.number[i] - backward >= t2.number[i]) {
			result.number.push_back((t1.number[i] - t2.number[i] - backward));
			backward = 0;
		}
		else {
			result.number.push_back((t1.number[i] - t2.number[i] - backward + 10));
			backward = 1;
		}
	}
	for (int i = result.number.size() - 1; i >= 1; i--) {
		if (result.number[i] != 0)
			break;
		else
			result.number.pop_back();
	}
	reverse(result.number.begin(), result.number.end());
	return result;
}
BigNum BigNum::operator+(int b) const {
	BigNum t(b);
	return this->operator+(t);
}
BigNum BigNum::operator+(const BigNum& b) const {
	if (sign == 0) {
		if (b.sign == 0) {
			return this->unsignedAdd(b);
		}
		else {
			if (this->unsignedEqual(b)) {
				return BigNum(0);
			} else if (this->unsignedBigger(b))
				return this->unsignedSub(b);
			else {
				BigNum t = b.unsignedSub(*this);
				t.sign = 1;
				return t;
			}
		}
	}
	else {
		if (b.sign == 0) {
			if (this->unsignedEqual(b)) {
				return BigNum(0);
			} else if (this->unsignedBigger(b)) {
				BigNum t = this->unsignedSub(b);
				t.sign = 1;
				return t;
			}
			else {
				return b.unsignedSub(*this);
			}
		}
		else {
			BigNum t = this->unsignedAdd(b);
			t.sign = 1;
			return t;
		}
	}
}
BigNum BigNum::operator-(const BigNum& b) const {
	if (sign == 0) {
		if (b.sign == 0) {
			if (this->unsignedEqual(b)) {
				return BigNum(0);
			} else if (this->unsignedBigger(b))
				return this->unsignedSub(b);
			else {
				BigNum t = b.unsignedSub(*this);
				t.sign = 1;
				return t;
			}
		}
		else {
			return this->unsignedAdd(b);
		}
	}
	else {
		if (b.sign == 0) {
			BigNum t = b.unsignedAdd(*this);
			t.sign = 1;
			return t;
		}
		else {
			if (this->unsignedEqual(b)) {
				return BigNum(0);
			}
			else if (this->unsignedBigger(b)) {
				BigNum t = this->unsignedSub(b);
				t.sign = 1;
				return t;
			}
			else {
				return b.unsignedSub(*this);
			}
		}
	}
}
BigNum BigNum::operator-(int b) const {
	BigNum t(b);
	return this->operator-(t);
}
BigNum BigNum::operator*(int b) const {
	BigNum t(*this);
	BigNum result(0);
	int step = 0;
	while (b != 0) {
		int num = b % 10;
		int forward = 0;
		b = b / 10;
		BigNum bigNum;
		for (int i = 0; i < step; i++) {
			bigNum.number.push_back(0);
		}
		for (int i = t.number.size()-1; i >= 0 ; i--) {
			bigNum.number.push_back((t.number[i]*num + forward) % 10);
			forward = (t.number[i] * num + forward) / 10;
		}
		if (forward != 0)
			bigNum.number.push_back(forward);
		reverse(bigNum.number.begin(), bigNum.number.end());
		step++;
		result = result + bigNum;
	}
	return result;
}
BigNum BigNum::operator*(const BigNum& b) const {
	BigNum result(0);
	BigNum t(*this);
	for (int i = 0; i <= b.number.size()-1; i++) {
		result = result*10 + t*b.number[i];
	}
	return result;
}
/*BigNum BigNum::operator/(const BigNum& b) const {

}*/