/*
Adam Novoa
CS 372
Link List assignment 1
10/12/2014
*/

#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

ifstream infile;
ofstream outfile;

struct LL
{
	string name;
	float score;
	LL *linky;
};

LL *head = NULL;

int read();
LL* newNode();
void insert(LL* t);
void print(int MaxScore);

int main()
{
	infile.open("namesAndGrades.txt");
	int MaxScore = read();
	outfile.open("result.dat");
	print(MaxScore);
	system("pause");
	return 0;
}

LL* newNode()
{
	LL *t;
	t = new LL;
	t->name = " ";
	t->score = 0;
	t->linky = NULL;
	return t;
}

int read()
{
	LL*t;
	int MaxScore;
	infile >> MaxScore;
	
	while (!infile.eof())
	{
		t = newNode();
		infile >> t->name;
		infile >> t->score;

		insert(t);
	}
	return MaxScore;
}

void insert(LL* t)
{
	LL *c = head;
	LL *p = NULL;
	if (!head)
	{
		head = t;
		return;
	}
	if (head == c && t->score > c->score)	// Try changing "head == c" to !p
	{
		t->linky = c;
		head = t;
		return;
	}
	while (c && c->score > t->score)
	{	
		p = c;
		c = c->linky;
	}
	t->linky = c;
	p->linky = t;
	return;
}

void print(int MaxScore)
{
	outfile << setprecision(3) << showpoint;
	LL* c = head;
	while (c)
	{
		outfile << left << setw(15) << c->name << (c->score / MaxScore) * 100 << endl;
		c = c->linky;
	}
	return;
}
/*
Output in result.dat
Knocktosee     97.0
Taylor         95.7
Vey            95.3
ToSha          94.3
Reynolds       94.0
WayOut         93.0
Marshall       92.3
Mark           92.0
Lee            91.0
Mack           88.3
Moto           87.3
Ace            86.0
Brown          83.3
AceAgain       81.7
Boyanze        78.3
Bozo           67.7
Thomas         65.7
Lion           64.0
Thomson        62.7
Lewis          58.7
*/