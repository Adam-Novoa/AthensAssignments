/*
Adam Novoa
CS 414
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

void changeMe(const int& x);
int compare(const void* x, const void* y);
int sum(int n);

int main()
{
	enum colors {black, white, red, blue};
	colors c1 = black;
	colors c2 = white;
	c1 = c2;
	c1 = black;
	if (c1 == c2)
	{
		cout << c1 << " = " << c2 << endl;
	}
	if (c1 != c2)
	{
		cout << c1 << " != " << c2 << endl;
	}
	if (c1 < c2)
	{
		cout << c1 << " < " << c2 << endl;
	}
	if (c1 > c2)
	{
		cout << c1 << " > " << c2 << endl;
	}
	// The only valid operators are assignment and logic operators

	int x = 1;
	cout << "Starting x value = " << x << endl;
	changeMe(x);
	cout << "Ending x value = " << x << endl;

	int ary[] = { 10, 50, 20, 60, 30, 70, 40, 80, 50, 90 };
	qsort (ary, 10, sizeof(int), compare);
	
	for (int i = 0; i < 10; i++)
	{
		cout << ary[i] << endl;
	}

	cout << sum(100) << endl;

	system("pause");
	return 0;
}

void changeMe(const int& x)
{
	// Can not change values that are passed by const.
//	x += 1;
	cout << "Changed x value = "<< x << endl;
	return;
}

int compare(const void* x, const void* y)
{
	if (*(int*)x < *(int*)y)
	{
		return -1;
	}
	if (*(int*)x == *(int*)y)
	{
		return 0;
	}

	return 1;
}

int sum(int n)
{
	if (n == 1)
	{
		return n;
	}
	return n + sum(n - 1);
}