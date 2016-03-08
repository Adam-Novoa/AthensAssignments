/*
Adam Novoa
Hash Program
CS 372
11/16/2014
*/

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;


struct entry
{
	string name = "";
	string number = "";
	entry *ptr = NULL;
};

entry* newEntry();
int hashKey(string key);
void fill(entry table[]);
void insert(entry table[], string name, string number, int key);
void print(entry table[]);
void search(entry table[]);

ifstream infile;
int collisions = 0;

int main()
{
	entry table[31];
	fill(table);

	print(table);
	search(table);

	system("pause");
	return 0;
}

entry* newEntry()
{
	entry *t;
	t = new entry;
	t->name = "";
	t->number = "";
	t->ptr = NULL;
	return t;
}

int hashKey(string key)
{
	int index = key[0];
	for (int i = 1; i < key.length(); i++)
	{
		index = (key[i] * index) + 7919;
	}
	if (index < 0)
		return -(index%31);
	return (index % 31);
}

void fill(entry table[])
{
	infile.open("Phone.txt");
	char end;
	char t;
	while (!infile.eof())
	{
		string name = "";
		string number = "";
		while (infile.peek() < '0' || infile.peek() > '9')
		{
			infile.get(t);
			name += t;
		}
		while (name.back() == ' ')
		{
			name.resize(name.length() - 1);
		}
		infile >> number;
		int key = hashKey(name);
		insert(table, name, number, key);
		infile.get(end);
	}
	infile.close();
}

void insert(entry table[], string name, string number, int key)
{
	if (table[key].name == "")
	{
		table[key].name = name;
		table[key].number = number;
		return;
	}
	else
	{
		collisions++;
		entry *t = newEntry();
		t->name = name;
		t->number = number;

		entry *p = &table[key];
		entry *c = table[key].ptr;
		while (c != NULL)
		{
			p = c;
			c = c->ptr;
		}
		p->ptr = t;
	}
	return;
}

void print(entry table[])
{
	int index = 0;
	while (index < 31)
	{
		if (table[index].name != "")
		{
			cout << left << setw(20) << table[index].name << table[index].number << endl;
			entry *p = table[index].ptr;
			while (p != NULL)
			{
				cout << left << setw(20) << p->name << p->number << endl;
				p = p->ptr;
			}
		}
		index++;
	}
	cout << "Collisions found: " << collisions << endl;
	return;
}

void search(entry table[])
{
	string search = "";

	while (search != "-9")
	{
		search = "";
		cout << "Please enter a name to search for or -9 to quit." << endl;
		char temp = ' ';
		cin.get(temp);
		while (temp != '\n')
		{
			search += temp;
			cin.get(temp);
		}
		int key = hashKey(search);
		if (table[key].name == search)
		{
			cout << "The number for " << search << " is " << table[key].number << endl;
		}
		else if (search != "-9")
		{
			entry *p = table[key].ptr;
			while (p != NULL)
			{
				if (p->name == search)
				{
					cout << "The number for " << search << " is " << p->number << endl;
					break;
				}
				else
					p = p->ptr;
			}
			if (p == NULL)
			{
				cout << "Sorry this name is not in the system." << endl;
			}
		}
	}
	return;
}
/*
Output
Legg T.             587-2839
Big Tow             384-5624
Hoos R. Dadie       818-3821
Smelly Tau          707-7281
Hauser M.           606-2940
Malioneyh P. J.     287-4344
Tobe Cir            613-2414
Stone Rock          544-2372
stephens reynolds   696-9231
oe vey              177-1423
TooB OrNot          283-5214
james wilis thomas  261-8342
G P Morier          832-4562
john marshall       888-2891
Taylor marie        939-1512
SixOne Other        843-2343
Morier G. E.        544-2319
Tyosn Chicken       602-3152
Mighty Mouse        222-2222
mack russell        123-1234
Twoseeor knocksee   823-8321
Zevent Heaven       834-2563
Lewis Michelle Tee  828-2148
Hofstra M.          601-3225
lea high lee        266-8324
Moto hasey          823-8000
Currie W. D.        701-4281
Collisions found: 8
Please enter a name to search for or -9 to quit.
oe vey
The number for oe vey is 177-1423
Please enter a name to search for or -9 to quit.
joe
Sorry this name is not in the system.
Please enter a name to search for or -9 to quit.
-9
Press any key to continue . . .
*/