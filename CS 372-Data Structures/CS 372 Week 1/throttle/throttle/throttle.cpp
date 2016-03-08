/*
Adam Novoa
CS 372
Throttle
8/25/2014
*/

#include<iostream>

using namespace std;

class throttle
{
private:
	int position;
	int max_position;
public:
	throttle(int value = 5)
	{
		position = 0;
		if (value > 0)
		{
			max_position = value;
		}
		else
		{
			while (value <= 0)
			{
				cout << "Error enter a size greater than zero." << endl;
				cin >> value;
			}
			max_position = value;
		}
	}

	void shift(int value)
	{
		position += value;

		if (position < 0)
		{
			position = 0;
		}
		else if (position > max_position)
		{
			position = max_position;
		}
	}

	double flow()
	{
		return position / double(max_position);
	}

	bool isOn()
	{
		return flow();
	}

	void shutOff()
	{
		position = 0;
	}

	int getPos()
	{
		return position;
	}
};



int main()
{
	int size;
	cout << "Please enter a size for the throttle." << endl;
	cin >> size;
	throttle test(size);

	int val;
	do
	{
		cout << "Please enter an amout to shift by." << endl;
		cin >> val;
		test.shift(val);

		cout << "Your current throttle is " << test.getPos() << endl;
		cout << "Your current flow is " << test.flow() << endl;

	} while (test.isOn());

	system("pause");
	return 0;
}
/*Output as follows

Please enter a size for the throttle.
7
Please enter an amout to shift by.
5
Your current throttle is 5
Your current flow is 0.714286
Please enter an amout to shift by.
6
Your current throttle is 7
Your current flow is 1
Please enter an amout to shift by.
-3
Your current throttle is 4
Your current flow is 0.571429
Please enter an amout to shift by.
-15
Your current throttle is 0
Your current flow is 0
Press any key to continue . . .
*/