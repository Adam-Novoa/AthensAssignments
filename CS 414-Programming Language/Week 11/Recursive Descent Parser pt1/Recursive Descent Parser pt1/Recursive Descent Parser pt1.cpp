/*
Adam Novoa
CS 414
Recursive Descent Parser pt1
11/12/2015
*/

#include <iostream>
#include <string>

using namespace std;
bool S();
bool A();
bool AP();
bool B();
bool match(char k);

string sentence;
int LH;

int main()
{
	cout << "Enter string to parse or exit to quit." << endl;
	getline(cin, sentence);

	while (sentence != "exit")
	{

		for (int i = 0; i < (int)sentence.size(); i++)
		{
			if (sentence[i] == ' ')
			{
				for (int j = i; j < (int)sentence.size() - 1; j++)
				{
					sentence[j] = sentence[j + 1];
				}
				sentence.resize(sentence.size() - 1);
			}
		}
		LH = 0;
		if (S())
		{
			cout << "True\n\n";
		}
		else
		{
			cout << "False\n\n";
		}
		cout << "Enter string to parse or exit to quit." << endl;
		getline(cin, sentence);

	}
	system("pause");
	return 0;
}

bool S()
{
	cout << "entering S() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;
	if (sentence[LH] == '[')
	{
		if (match('[') && A() && S() && match(']'))
		{
			return true;
		}
		else
			return false;
	}
	else if (sentence[LH] == '(')
	{
		if (match('(') && B() && match(')') && S())
		{
			return true;
		}
		else
			return false;
	}
	else
		return true;
}

bool A()
{
	cout << "entering A() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (sentence[LH] == 'a')
	{
		if (match('a') && AP())
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool AP()
{
	cout << "entering AP() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (sentence[LH] == '#')
	{
		if (match('#') && A() && AP())
		{
			return true;
		}
		else
			return false;
	}
	else
		return true;
}

bool B()
{
	cout << "entering B() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (sentence[LH] == '?')
	{
		if (match('?') && S() && match(','))
		{
			return true;
		}
		else
			return false;
	}
	else if (sentence[LH] == '.')
	{
		if (match('.') && S())
		{
			return true;
		}
		else
			return false;
	}
	else if (sentence[LH] == 'b')
	{
		if (match('b'))
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool match(char k)
{
	if (sentence[LH] == k)
	{
		if (LH < (int)sentence.size())
		{
			LH++;
			return true;
		}
		else
			return false;
	}
	return false;
}