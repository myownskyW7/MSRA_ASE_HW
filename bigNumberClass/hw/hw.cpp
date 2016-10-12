// hw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "BigNum.h"
using namespace std;

int main(int argc, _TCHAR* argv[])
{
	BigNum a(1000);
	string str = "12345678987654321111";
	BigNum b(str);
	BigNum c(b);
	BigNum d;
	d = b;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	cout << d << endl;
	while (1) {
		cin >> a;
		cin >> b;
		cout << a + b << endl;
		/*bool bl = a > b;
		cout << bl << endl;
		bl = c == d;
		cout << bl << endl;*/
		cout << a - b << endl;
		cout << a * 10 << endl;
		cout << a * b << endl;
	}
	system("pause");
	return 0;
}

