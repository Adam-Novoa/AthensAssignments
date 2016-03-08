/*
Adam Novoa
CS 372
inPostFix
10/19/2014
*/

#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

class Queue
{
private:
	typedef char VT;
	VT ary[30];
	double bry[30];
	int used;
	int pos;
	const int MAX = 30;

public:
	Queue()
	{
		for (int i = 0; i < MAX; i++)
		{
			ary[i] = ' ';
		}
		for (int i = 0; i < MAX; i++)
		{
			bry[i] = 0;
		}
		pos = 0;
		used = 0;
	}
	
	void inQueue(VT val)
	{
		if (used < MAX)
		{
			ary[used] = val;
			used++;
		}
		return;
	}
	void inQueue(double val)
	{
		if (used < MAX)
		{
			bry[used] = val;
			used++;
		}
		return;
	}
	VT deQueue()
	{
		VT temp = ary[0];
		if (used > 0)
		{
			for (int i = 0; i < used - 1; i++)
			{
				ary[i] = ary[i + 1];
			}
			used--;
		}
		return temp;
	}
	double deQueueN()
	{
		double temp = bry[0];
		if (used > 0)
		{
			for (int i = 0; i < used - 1; i++)
			{
				bry[i] = bry[i + 1];
			}
			used--;
		}
		return temp;
	}
	void insertBefore(double val ,int pos)
	{
		if (used > 0)
		{
			for (int i = pos; i < used - 1; i++)
			{
				bry[i+1] = bry[i];
			}
			used++;
			bry[pos] = val;
		}
	}
	bool empty()
	{
		if (used != 0)
			return true;
		return false;
	}
	VT getElement(int val)
	{
		return ary[val];
	}
	int size()
	{
		return used;
	}
	void insert(VT val,int pos)
	{
		ary[pos] = val;
	}
};

class Stack
{
private:
	const int MAX = 30;
	int Apos;
	int Aused;
	int Bpos;
	int Bused;
	char ary[30];
	double bry[30];
	char temp;
public:
	Stack()
	{
		for (int i = 0; i < MAX; i++)
		{
			ary[i] = ' ';
			bry[i] = 0;
		}
		ary[0] = '$';
		Apos = 1;
		Aused = 1;
		Bpos = -1;
		Bused = 0;
	}
	bool end()
	{
		if (Aused)
			Apos = Aused - 1;
		if (Bused)
			Bpos = Bused - 1;
		return true;
	}
	void push(char op)
	{
		if (Aused < MAX)
		{

			Aused++;
			end();
			ary[Apos] = op;
		}
		return;
	}
	
	void push(double val)
	{
		if (Bused < MAX)
		{
			end();
			Bused++;
			Bpos++;
			bry[Bpos] = val;
		}
		return;
	}
	char pop()
	{
		end();
		char op = ary[Apos];
		erase();
		return op;
	}
	double popN()
	{
		end();
		double val = bry[Bpos];
		erase();
		return val;
	}
	void erase()
	{
		if (Aused > 1)
		{
			Apos--;
			Aused--;
		}
		else if (Aused == 1)
		{
			Aused--;
			Apos = 0;
		}

		if (Bused > 0)
		{
			bry[Bpos] = 0;
			Bpos--;
			Bused--;
		}
		
		return;
	}
	char getlast()
	{
		return ary[Apos];
	}
	bool empty()
	{
		if (Bused)
		{
			return Bused;
		}
		else if (Aused > 1)
			return Aused;
		return false;
	}
};

ifstream infile;
ofstream outfile;

char read();
Queue inToPost();
int opPriorty(char ch);
void print(Queue a);
void solve(Queue post);

int main()
{
	infile.open("data.txt");
	outfile.open("result.txt");

	while (!infile.eof())
	{
		Queue temp = inToPost();
		solve(temp);
		outfile << endl;
	}
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}

char read()
{
	char temp;
	infile.get(temp);
	while (temp == ' ')
		infile.get(temp);
	return temp;
}

Queue inToPost()
{
	Queue post;
	Stack ops;
	Stack tempOp;
	char temp = read();
	while (temp != '\n' && temp != -52)
	{
		if (temp >= '0' && temp <= '9')
		{
			post.inQueue(temp);
		}
		else if (temp == '(')
		{
			ops.push(temp);
		}
		else if (opPriorty(temp) == 0)
		{
			while (ops.getlast() != '$' && ops.getlast() != '(')
				post.inQueue(ops.pop());
		}
		else if (opPriorty(temp) > opPriorty(ops.getlast()))
		{
			ops.push(temp);
		}
		else if (opPriorty(temp) == opPriorty(ops.getlast()))
		{
			while (opPriorty(temp) == opPriorty(ops.getlast()))
			{
				post.inQueue(ops.pop());
			}
			ops.push(temp);
		}
		else if (opPriorty(temp) < opPriorty(ops.getlast()))
		{
			while (ops.getlast() != '$' && ops.getlast() != '(')
			{
				post.inQueue(ops.pop());
			}
			if (ops.getlast() == '(')
			{
				ops.pop();
			}
			ops.push(temp);
		}
		temp = read();
	}
	while (ops.getlast() != '$')
	{
		if (ops.getlast() == '(')
			ops.pop();
		post.inQueue(ops.pop());
	}
	return post;
}
int opPriorty(char ch)
{
	if (ch == '(')
		return 0;
	else if (ch == '^')
		return 3;
	else if (ch == '*' || ch == '/')
		return 2;
	else if (ch == '+' || ch == '-')
		return 1;
	else
		return 0;
}


void solve(Queue post)
{
	Stack num;
	char temp;
	do 
	{
		temp = post.deQueue();
		outfile << temp;
		if (temp >= '0' && temp <= '9')
		{
			double value = temp - '0';
			num.push(value);
		}
		else
		{
			if (temp == '^')
			{
				double val2 = num.popN();
				double val1 = num.popN();
				num.push(pow(val1, val2));
			}
			else if (temp == '*')
			{
				double val2 = num.popN();
				double val1 = num.popN();
				num.push(val1*val2);
			}
			else if (temp == '/')
			{
				double val2 = num.popN();
				double val1 = num.popN();
				num.push(val1 / val2);
			}
			else if (temp == '+')
			{
				double val2 = num.popN();
				double val1 = num.popN();
				num.push(val1 + val2);
			}
			else if (temp == '-')
			{
				double val2 = num.popN();
				double val1 = num.popN();
				num.push(val1 - val2);
			}
		}
	} while (post.empty());
	outfile << " = " << num.popN();
	return;
}
/*
Output in result.txt
57+ = 12
62^1+ = 37
38*6+ = 30
54^64^- = -671
537*4/-9- = -9.25
893/2-*4/56*+ = 32
53^4*298*26*84/2^8**5-/52^/4-+ = -1.9924
538*23^/- = 2
33^2^3* = 2187
863/2-*4/56*+3+ = 33
*/