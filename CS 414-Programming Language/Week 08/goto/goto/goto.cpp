/*
Adam Novoa
CS 414
*/

#include <iostream>

using namespace std;
void func();

int main()
{
	int n = 1;
	int x = 0;
L1:
	x += n;
	if (n < 100)
	{
		n++;
		goto L1;
	}
	cout << x << endl;

	bool flag = true;
	if (true)
	{
	
		int i = 0;
		if (true)
		{
			int x = 0;
			goto L2;
		}
	}
L2:
	func();
L3:

	system("pause");
	return 0;
}

void func()
{
	int i = 0;
	//goto L3; does not work L3 out of scope
	return;
}