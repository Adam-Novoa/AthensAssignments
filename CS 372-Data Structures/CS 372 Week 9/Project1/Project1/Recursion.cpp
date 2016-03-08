/*
Adam Novoa
CS 372
Recursion
10/19/2014
*/
#include <iostream>

using namespace std;

unsigned a(int n)
{
	// #21
	if (n < 0)
		return 0;
	if (n < 10)
		return 1;
	else
		return 1 + a(n/10);
}

void printReverse(int n)
{
	// #23
	if (n == 0)
	{
		cout << endl;
		return;
	}
	else
	{
		cout << n % 10;
		printReverse(n / 10);
		return;
	}
}
typedef int ArrayType;
void reverseArray(ArrayType a[], int first, int last)
{
	// #27
	if (first >= last)
	{
		return;
	}

	int temp = a[first];
	a[first] = a[last];
	a[last] = temp;

	reverseArray(a, ++first, --last);
	return;
}

int sumArray(ArrayType a[], int n)
{
	// #28
	if (n == 0)
		return 0;
	return a[n-1] + sumArray(a, n - 1);
}
typedef int element;
int location(ArrayType a[], int first, int last, element elm)
{
	// #29
	if (first >= last)
		return 0;
	if (a[first] == elm)
		return first;
	if (a[last] == elm)
		return last;
	location(a, ++first, --last, elm);
}
int GCD(int a, int b)
{
	// #33
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	int q = a / b;
	int r = a % b;
	if (r == 0)
	{
		return b;
	}
	else
		return GCD(b, r);
}


int main()
{

	cout << a(1234543) << endl;
	printReverse(1234543);

	ArrayType a[20];
	for (int i = 0; i < 20; i++)
	{
		a[i] = i;
	}

	reverseArray(a, 0, 19);
	for (int i = 0; i < 20; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	
	cout <<"The sum of the array is: " << sumArray(a, 20) << endl;

	cout << "The location of 5 is: " << location(a, 0, 19, 5) << endl;
	cout << "The location of 50 is: " << location(a, 0, 19, 50) << endl;

	cout << "The GCD of 5551, 56 is: " << GCD(5551, 56) << endl;

	system("pause");
	return 0;
}
/*
Output
7
3454321
19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
The sum of the array is: 190
The location of 5 is: 14
The location of 50 is: 0
The GCD of 5551, 56 is: 7
Press any key to continue . . .
*/