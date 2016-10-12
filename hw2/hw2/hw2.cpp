// hw2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;
void Bit_Sieve(int nth) {
	int limit = nth < 6 ? 25 : (int)(nth*(log(nth) + log(log(nth))));
	int count = 0;
	int total = limit + 1;
	int sqrtLimit = (int)sqrt(limit) + 1;
	vector<unsigned int> is_prime((total >> 5) + 1);
	for (int i = 0; i < (total >> 5) + 1; i++)
		is_prime.push_back(0x0);
	for (int i = 2; i < sqrtLimit; i++) {
		if ((is_prime[i >> 5] & (1 << (i & 31))) == 0) {
			for (int j = i*i; j <= total; j += i) {
				is_prime[j >> 5] |= (unsigned int)1 << (j & 31);
			}
		}
	}
	for (int i = 2; i < total; i++) {
		if ((is_prime[i >> 5] & (1 << (i & 31))) == 0) {
			count++;
			if (count == nth) {
				cout << i << endl;
				break;
			}
		}
	}
}
void Local_Bit_Sieve(int nth) {
	int limit = nth < 6 ? 25 : (int)(nth*(log(nth) + log(log(nth))));
	int sqrtLimit = (int)sqrt(limit) + 1;
	vector<unsigned int> is_prime((sqrtLimit >> 5) + 1);
	for (int i = 0; i < (sqrtLimit >> 5) + 1; i++)
		is_prime.push_back(0x0);
	for (int i = 2; i*i < sqrtLimit; i++) {
		if ((is_prime[i >> 5] & (1 << (i & 31))) == 0) {
			for (int j = i*i; j <= sqrtLimit; j += i) {
				is_prime[j >> 5] |= (unsigned int)1 << (j & 31);
			}
		}
	}
	vector<unsigned int> smallPrimes;
	for (int i = 2; i < sqrtLimit; i++) {
		if ((is_prime[i >> 5] & (1 << (i & 31))) == 0) {
			smallPrimes.push_back(i);
		}
	}
	int segSize = max(sqrtLimit, 256 * 256);
	vector<unsigned int> allPrimes(smallPrimes);
	int high = segSize << 5;
	for (int low = sqrtLimit; low <= limit + high; low += high) {
		vector<unsigned int> primeSeg(segSize);
		for (int i = 0; i < segSize + 1; i++)
			primeSeg.push_back(0x0);
		for (int i = 0; i < smallPrimes.size(); i++) {
			int initValue = low%smallPrimes[i];
			for (int j = (initValue == 0 ? initValue : smallPrimes[i] - initValue); j < high; j += smallPrimes[i]) {
				primeSeg[j >> 5] |= (unsigned int)1 << (j & 31);
			}
		}
		for (int i = 0; i < high; i++) {
			if ((primeSeg[i >> 5] & (1 << (i & 31))) == 0)
				allPrimes.push_back(i+low);
		}
		if (allPrimes.size() > nth) {
			cout << allPrimes[nth-1] << endl;
			break;
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int nth;
	cin >> nth;
	double time1 = clock();
	Bit_Sieve(nth);
	double time2 = clock();
	cout << "duration = " << (double)(time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	double time3 = clock();
	Local_Bit_Sieve(nth);
	double time4 = clock();
	cout << "duration = " << (double)(time4 - time3) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}

