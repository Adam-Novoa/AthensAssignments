/*
Adam Novoa
CS 414
Recursive Descent Parser pt2
11/12/2015
*/

#include <iostream>
#include <string>

using namespace std;

bool DecList();
bool DecListP();
bool Decl();
bool IdList();
bool IdListP();
bool Type();
bool ScalarType();
bool Rest();
bool Bound();
bool Sign();
bool ScalarTypeList();
bool ScalarTypeListP();
bool ID();
bool IntLit();

bool match(string k);

string sentence;
int LH;
_String_iterator<_String_val<_Simple_types<char>>> ptr;

int main()
{
	cout << "Enter string to parse or exit to quit." << endl;
	getline(cin, sentence);

	ptr = sentence.begin();
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
		
		if (DecList())
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

bool DecList()
{
	cout << "entering DecList() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (Decl() && DecListP())
		return true;
	else
		return false;

}

bool DecListP()
{
	cout << "entering DecListP() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (sentence[LH] == ';')
	{
		if (match(";") && Decl() && DecListP())
			return true;
		else
			return false;
	}
	else
		return true;//nothing
}
bool Decl()
{
	cout << "entering Decl() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (IdList() && match(":") && Type())
		return true;
	else
		return false;
}
bool IdList()
{
	cout << "entering IdList() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (ID() && IdListP())
		return true;
	else
		return false;
}
bool IdListP()
{
	cout << "entering IdListP() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (sentence[LH] == ',')
	{
		if (match(",") && ID() && IdListP())
			return true;
		else false;
	}
	else
		return true;
}


bool Type()
{
	cout << "entering Type() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (match("array") && match("(") && ScalarTypeList() && match(")") && match("of") && Type())
	{
		return true;
	}
	else if (ScalarType())
	{
		return true;
	}
	else
		return false;
}

bool ScalarType()
{
	cout << "entering ScalarType() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (ID() && Rest())
		return true;
	else
		return false;
}
bool Rest()
{
	cout << "entering Rest() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (match("..") && Bound())
		return true;
	else
		return true;
}
bool Bound()
{
	cout << "entering Bound() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (Sign() && IntLit())
		return true;
	else if (ID())
		return true;
	else
		return false;
}
bool Sign()
{
	cout << "entering Sign() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (match("+"))
	{
		return true;
	}
	else if (match("-"))
	{
		return true;
	}
	else
		return true;
}
bool ScalarTypeList()
{
	cout << "entering ScalarTypeList() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (ScalarType() && ScalarTypeListP())
		return true;
	else
		return false;
}
bool ScalarTypeListP()
{
	cout << "entering ScalarTypeListP() -> ";
	for (int i = LH; i < (int)sentence.size(); i++)
	{
		cout << sentence[i];
	}
	cout << endl;

	if (sentence[LH] == ',')
	{
		if (match(",") && ScalarType() && ScalarTypeListP())
			return true;
		else false;
	}
	else
		return true;
}

bool match(string k)//test
{
	int i = LH;
	while (sentence[i] == ' ' && i < (int)sentence.size())
	{
		LH++;
	}
	string temp = "";
	if (LH + (int)k.size() <= (int)sentence.size())
	{
		for (int i = 0; i < (int)k.size(); i++)
		{
			temp += sentence[LH + i];
		}
	
		if (temp == k)
		{
			LH += (int)k.size();
			return true;
		}
		else
			return false;
	}
	return false;
}

bool ID()
{
	if (isalpha(sentence[LH]))
	{
		while (isalpha(sentence[LH]))
		{
			LH++;
		}
		return true;
	}
	else
		return false;
}

bool IntLit()
{
	if (isalnum(sentence[LH]) && !isalpha(sentence[LH]))// fix to is num
	{
		while (isalnum(sentence[LH]) && !isalpha(sentence[LH]))
		{
			LH++;
		}
		return true;
	}
	else
		return false;
}