/*
Adam Novoa
CS 372
Array Work Out Program 1
10/5/2014
*/

#include<iostream>
#include<fstream>

using namespace std;

void table_print(int *p, int sz);
void table_add1(int *p, int sz);
void table_fill(int*p, int sz, int v);
void table_print_rev(int*p, int sz);
void table_copy(int *r, int *s, int sz);
int table_min(int *p, int sz);
int table_max(int *p, int sz);
int table_avg(int *p, int sz);
bool table_contain(int *p, int sz, int v);


ifstream infile;

int main()
{
	const int Max = 20;
	
	int *p = new int [Max];
	int *s = new int [Max];
	int *tp;

	table_fill(p, Max, 10);
	cout << endl << "Fill array with 10 " << endl;
	table_print(p, Max);  cout << endl << endl;


	cout << endl << "Add 1 to first 10 elements " << endl;
	table_add1(p, 10);
	table_print(p, Max);  cout << endl << endl;

	tp = s;   // save pointer
	for (int i = 1; i <= Max; i++)
	{
		table_fill(s, 1, i);
		s++;
	}
	cout << endl << "Fill array with 1 to 20 " << endl;
	s = tp;   // restore pointer
	table_print(s, Max);  cout << endl << endl;

	cout << endl << "Print reverse order " << endl;
	table_print_rev(s, Max);  cout << endl << endl;

	table_fill(p, Max, 0);
	cout << endl << "Zero out array " << endl;
	table_print(p, Max);  cout << endl << endl;

	s = p;        // What's happening here?
	for (int i = Max; i >= 0; i--)
	{
		table_add1(s, i);
	}

	cout << endl << "Fill array with ???? " << endl;
	table_print(p, Max);  cout << endl << endl;

	cout << endl << "Print reverse order " << endl;
	table_print_rev(p, Max);  cout << endl << endl;

	for (int i = 0; i<Max / 2 + 1; i++)
	{
		s = p + 10 + i;
		table_fill(s, 1, i * 2);
		s = p + 10 - i;
		table_fill(s, 1, i * 3);
	}
	cout << endl << "Fill array with <-> " << endl;
	table_print(p, Max);  cout << endl << endl;

	cout << endl << "Min for previous table " << table_min(p, 15);
	cout << endl << "Max for previous table " << table_max(p + 10, 9);
	cout << endl << "Average for previous table " << table_avg(p + 5, 12);
	
	// Begin new code for problem 1
	cout << endl << endl;
	int tAvg = table_avg(p, Max);
	tp = p;
	int belowCount = 0;
	for (int i = 0; i < Max; i++, p++)
	{
		if (*p < tAvg)
		{
			belowCount++;
		}
	}
	p = tp;
	cout << "Number of elements below the average: " << belowCount << endl << endl;

	// Begin new code for problem 2
	int *c = new int[12];
	infile.open("scores.txt"); // Holds scores from assignment
	tp = c;
	for (int i = 0; i < 12; i++, c++)
	{
		infile >> *c;
	}
	c = tp;
	int avg = 0;
	for (int i = 0; i < 12; i++, c++)
	{
		if (i == 3 || i == 7)
		{
			avg += *c * 2;
		}
		else if (i == 11)
		{
			avg += *c * 3;
		}
		else
		{
			avg += *c;
		}
	}
	avg /= 16;
	cout << "Student average: " << avg << endl;




	system("pause");
	return 0;
}

void table_print(int *p, int sz)
{
	int *tp = p;
	for (int i = 0; i < sz; i++, p++)
	{
		cout << *p << " ";
	}
	p = tp;
	return;
}

void table_add1(int *p, int sz)
{
	int *tp = p;
	for (int i = 0; i < sz; i++, p++)
	{
		*p += 1;
	}
	p = tp;
	return;
}

void table_fill(int*p, int sz, int v)
{
	int *tp = p;
	for (int i = 0; i < sz; i++, p++)
	{
		*p = v;
	}
	p = tp;
	return;
}

void table_print_rev(int*p, int sz)
{
	int *tp = p;
	p = p + sz-1;
	for (int i = 0; i < sz; i++, p--)
	{
		cout << *p << " ";
	}
	p = tp;
	return;
}

void table_copy(int *r, int *s, int sz)
{
	int *tr = r;
	int *ts = s;
	for (int i = 0; i < sz; i++, r++, s++)
	{
		*r = *s;
	}
	r = tr;
	s = ts;
	return;
}

int table_min(int *p, int sz)
{
	int *tp = p;
	int lowest = *p;
	for (int i = 0; i < sz; i++, p++)
	{
		if (*p < lowest)
		{
			lowest = *p;
		}
	}
	p = tp;
	return lowest;
}

int table_max(int *p, int sz)
{
	int *tp = p;
	int highest = *p;
	for (int i = 0; i < sz; i++, p++)
	{
		if (*p > highest)
		{
			highest = *p;
		}
	}
	p = tp;
	return highest;
}

int table_avg(int *p, int sz)
{
	int *tp = p;
	int sum = 0;
	for (int i = 0; i < sz; i++, p++)
	{
		sum += *p;	
	}
	p = tp;
	return sum/sz;
}

bool table_contain(int *p, int sz, int v)
{
	int *tp = p;
	for (int i = 0; i < sz; i++, p++)
	{
		if (*p == v)
		{
			p = tp;
			return true;
		}
	}
	p = tp;
	return false;
}

/*
Output



Fill array with 10
10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10


Add 1 to first 10 elements
11 11 11 11 11 11 11 11 11 11 10 10 10 10 10 10 10 10 10 10


Fill array with 1 to 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20


Print reverse order
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1


Zero out array
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0


Fill array with ????
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1


Print reverse order
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20


Fill array with <->
30 27 24 21 18 15 12 9 6 3 0 2 4 6 8 10 12 14 16 18


Min for previous table 0
Max for previous table 16
Average for previous table 7

Number of elements below the average: 9

Student average: 86
Press any key to continue . . .
*/