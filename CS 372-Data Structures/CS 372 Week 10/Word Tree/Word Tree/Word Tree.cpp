/*
Adam Novoa
CS 372
Word Tree
10/26/2014
*/

#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

ifstream infile;
ofstream outfile;

struct Node
{
	string word;
	Node *Lchild;
	Node *Rchild;
	int count;
	double rel; // relative %
};

Node* myNewNode();
void insert(string temp);
string newWord();
void wordToCount(Node *c);
void printSize(int &n, Node *c);
void countTree(Node temp);
void removeHigh(Node *c);

int wordCount = 0;
Node *wordHead = NULL;
Node *countHead = NULL;
int main()
{
	

	wordHead;
	countHead;
	infile.open("Bill of Rights.txt");
	outfile.open("Top100.dat");
	
	while (!infile.eof())
	{
		string temp = newWord();
		if (temp != "")
		{
			wordCount++;
			insert(temp);
		}
	}
	wordToCount(wordHead);
	int n = 100;
	outfile << left << setw(15) << "Word" << "Count" << "	" << "Relative"<< endl;
	printSize(n, countHead);
	outfile << endl;
	
	double percent = 0.15;
	while (percent > 0)
	{
		Node *c = countHead;
		Node *p = NULL;
		while (c != NULL)
		{
			p = c;
			c = c->Rchild;
		}
		percent -= p->rel;
		removeHigh(p);
	}
	n = 100;
	outfile << "\nAfter top 15% of words removed" << endl;
	outfile << left << setw(15) << "Word" << "Count" << "	" << "Relative" << endl;
	printSize(n, countHead);
	outfile << endl;
	return 0;
}

Node* myNewNode()
{
	Node *t;
	t = new Node;
	t->word = " ";
	t->Lchild = NULL;
	t->Rchild = NULL;
	t->count = 1;
	double rel = 0;
	return t;
}

void insert(string temp)
{
	Node *t = myNewNode();
	t->word = temp;
	t->count = 1;
	Node *c = wordHead;
	Node *p = NULL;
	if (wordHead == NULL)
	{
		wordHead = t;
		return;
	}
	while (c != NULL)
	{
		p = c;
		if (c->word == t->word)
		{
			c->count++;
			return;
		}
		else if (c->word > t->word)
			c = c->Lchild;
		else if (c->word < t->word)
			c = c->Rchild;
	}
	if (c == NULL)
	{
		if (p->word < t->word)
			p->Rchild = t;
		else
			p->Lchild = t;
	}
	return;
}

string newWord()
{
	string word ="";
	char temp;
	infile.get(temp);
	temp = tolower(temp);
	while (!infile.eof() && !isalpha(temp) && temp != '-')
	{
		infile.get(temp);
		temp = tolower(temp);
	}
	while (isalpha(temp) || temp == '-')
	{
		word += temp;
		infile.get(temp);
		temp = tolower(temp);
	}
	return word;
}

void countTree(Node *temp)
{
	Node *t = myNewNode();
	t->word = temp->word;
	t->count = temp->count;
	t->rel = t->count / (double)wordCount;
	Node *c = countHead;
	Node *p = NULL;
	if (countHead == NULL)
	{
		countHead = t;
		return;
	}
	while (c != NULL)
	{
		p = c;
		if (c->count == t->count)
		{
			t->Lchild = c->Lchild;
			c->Lchild = t;
			return;
		}
		else if (c->count > t->count)
			c = c->Lchild;
		else if (c->count < t->count)
			c = c->Rchild;
	}
	if (c == NULL)
	{
		if (p->count < t->count)
			p->Rchild = t;
		else
			p->Lchild = t;
	}
	return;
}

void wordToCount(Node *c)
{
	if (c == NULL)
	{
		return;
	}
	countTree(c);
	wordToCount(c->Lchild);
	wordToCount(c->Rchild);
	return;
}

void printSize(int &n, Node *c)
{
	if (c == NULL || n == 0)
		return;
	printSize(n, c->Rchild);
	if (n != 0)
	{
		outfile << left << setw(15) << c->word << c->count << "	" <<fixed << showpoint << setprecision(2) << c->rel*100 << endl;
		n--;
		printSize(n, c->Lchild);
	}
	return;
}

void removeHigh(Node *c)
{
	Node *p = NULL;
	Node *t = NULL;
	if (c->Lchild == NULL)
	{
		delete(c);
		return;
	}
	else
	{
		
		t = c->Lchild;
		while (t->Rchild != NULL)
		{
			p = t;
			t = t->Rchild;
		}
		if (p)
		{
			c->word = t->word;
			c->count = t->count;
			c->rel = t->rel;
			p->Rchild = t->Lchild;
			delete(t);
		}
	}
	return;
}
/*
Output from Top100.dat
Word           Count	Relative
the            71	9.87
of             50	6.95
to             31	4.31
and            23	3.20
in             23	3.20
be             23	3.20
or             17	2.36
shall          17	2.36
a              13	1.81
by             13	1.81
amendment      11	1.53
states         11	1.53
constitution   8	1.11
nor            8	1.11
for            6	0.83
united         6	0.83
law            6	0.83
any            5	0.70
right          5	0.70
people         5	0.70
not            5	0.70
no             5	0.70
as             4	0.56
time           4	0.56
public         4	0.56
jury           4	0.56
have           4	0.56
congress       4	0.56
amendments     3	0.42
without        3	0.42
their          3	0.42
ratified       3	0.42
rights         3	0.42
legislatures   3	0.42
articles       3	0.42
at             3	0.42
against        3	0.42
all            3	0.42
bill           2	0.28
witnesses      2	0.28
when           2	0.28
which          2	0.28
war            2	0.28
trial          2	0.28
that           2	0.28
state          2	0.28
several        2	0.28
said           2	0.28
property       2	0.28
process        2	0.28
proposed       2	0.28
person         2	0.28
persons        2	0.28
otherwise      2	0.28
original       2	0.28
powers         2	0.28
on             2	0.28
militia        2	0.28
life           2	0.28
is             2	0.28
its            2	0.28
houses         2	0.28
his            2	0.28
house          2	0.28
government     2	0.28
free           2	0.28
form           2	0.28
following      2	0.28
excessive      2	0.28
district       2	0.28
criminal       2	0.28
crime          2	0.28
held           2	0.28
common         2	0.28
cause          2	0.28
but            2	0.28
been           2	0.28
an             2	0.28
america        2	0.28
preamble       1	0.14
x              1	0.14
witness        1	0.14
with           1	0.14
where          1	0.14
wherein        1	0.14
what           1	0.14
well           1	0.14
were           1	0.14
will           1	0.14
warrants       1	0.14
viii           1	0.14
vii            1	0.14
value          1	0.14
vi             1	0.14
violated       1	0.14
viz            1	0.14
use            1	0.14
v              1	0.14
unusual        1	0.14
upon           1	0.14


After top 15% of words removed
Word           Count	Relative
to             31	4.31
and            23	3.20
in             23	3.20
be             23	3.20
or             17	2.36
shall          17	2.36
a              13	1.81
by             13	1.81
amendment      11	1.53
states         11	1.53
constitution   8	1.11
nor            8	1.11
for            6	0.83
united         6	0.83
law            6	0.83
any            5	0.70
right          5	0.70
people         5	0.70
not            5	0.70
no             5	0.70
as             4	0.56
time           4	0.56
public         4	0.56
jury           4	0.56
have           4	0.56
congress       4	0.56
amendments     3	0.42
without        3	0.42
their          3	0.42
ratified       3	0.42
rights         3	0.42
legislatures   3	0.42
articles       3	0.42
at             3	0.42
against        3	0.42
all            3	0.42
bill           2	0.28
witnesses      2	0.28
when           2	0.28
which          2	0.28
war            2	0.28
trial          2	0.28
that           2	0.28
state          2	0.28
several        2	0.28
said           2	0.28
property       2	0.28
process        2	0.28
proposed       2	0.28
person         2	0.28
persons        2	0.28
otherwise      2	0.28
original       2	0.28
powers         2	0.28
on             2	0.28
militia        2	0.28
life           2	0.28
is             2	0.28
its            2	0.28
houses         2	0.28
his            2	0.28
house          2	0.28
government     2	0.28
free           2	0.28
form           2	0.28
following      2	0.28
excessive      2	0.28
district       2	0.28
criminal       2	0.28
crime          2	0.28
held           2	0.28
common         2	0.28
cause          2	0.28
but            2	0.28
been           2	0.28
an             2	0.28
america        2	0.28
preamble       1	0.14
x              1	0.14
witness        1	0.14
with           1	0.14
where          1	0.14
wherein        1	0.14
what           1	0.14
well           1	0.14
were           1	0.14
will           1	0.14
warrants       1	0.14
viii           1	0.14
vii            1	0.14
value          1	0.14
vi             1	0.14
violated       1	0.14
viz            1	0.14
use            1	0.14
v              1	0.14
unusual        1	0.14
upon           1	0.14
unless         1	0.14
unreasonable   1	0.14
*/