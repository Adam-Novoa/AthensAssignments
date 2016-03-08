/*
Adam Novoa
CS 414
Abstract Data Type (List)
10/03/2015
*/

#include <iostream>
#include <string>

using namespace std;

struct element
{
	string el;
	element* down;
	element* right;
};

class List
{
private:
	
	element* head;
	int depth;

public:
	char* temp;
	element* build(string t)
	{
		depth = 0;

		head = newElement();
		
		for (int i = 0; i < t.size(); i++)
		{
			if (t[i] == ' ')
			{
				for (int j = i; j < t.size(); j++)
				{
					t[j] = t[j + 1];
				}
				t.resize((t.size() - 1));
			}
		}

		temp = &t[0];
		head->down = construct();
		head = head->down;
		return head;
	}
	element* constructData()
	{
		element* tp = newElement();
		tp->el = *temp;
		++temp;
		if (tp->el == "(")
		{
			tp->down = constructData();
			tp->right = constructData();
		}
		else if (isalpha(*temp))
		{
			tp->right = constructData();
			return tp;
		}

		else if (tp->el == ")")
		{
			if (*temp == '(')
			{

			}
			else
			{
				return tp;
			}
		}
		return tp;
	}/*
	element* constructCom()
	{

	}
	*/
	element* construct()
	{
		element* tp = newElement();
		
		if (*temp == ')')
		{
			tp->el = *temp;
			tp->down = NULL;
			tp->right = NULL;
			temp++;
			return tp;
		}
		else if (*temp == '\'')// is data
		{
			temp++;
			return constructData();
		}
		else if (*temp == '(')//is command
		{
			string t = "";
			element* com = newElement();
			tp->el = *temp;
			temp++;
			t = *temp;
			t += *(temp + 1);
			t += *(temp + 2);
			temp += 2;
			if (t == "con")
			{
				t += *(++temp);
				com->el = t;
				tp->down = com;
				++temp;
				com->down = construct();
				com->right = construct();
				tp->right = construct();
			}
			else
			{
				com->el = t;
				tp->down = com;
				++temp;
				com->down = construct();
				tp->right = construct();
			}
		}
		
		return tp;
	}

	List()
	{
		head = NULL;
	}
	element* newElement()
	{
		element* tp = new element;
		tp->down = NULL;
		tp->right = NULL;
		tp->el = "";
		return tp;
	}
	void print(element* tp)
	{
		if (tp->down != NULL)
		{
			cout << tp->el;
			print(tp->down);
			if (tp->right != NULL)
			{
				print(tp->right);
			}
		}
		else
		{
			cout << tp->el;
			if (tp->right != NULL)
			{
				print(tp->right);
			}
		}
		return;
	}

};

int main()
{
	List l;
	l.print(l.build("(car'(rstz))"));
	cout << endl;
	l.print(l.build("(cdr '(rstz))"));
	cout << endl;
	l.print(l.build("(cons 'u '(vwz))"));
	cout << endl;
	l.print(l.build("(car(cdr'(rstz))"));
	cout << endl;
	l.print(l.build("(cdr(cdr(cdr'(rstz)))"));
	cout << endl;
	l.print(l.build("(cdr(cdr(cdr(cdr'(rstz))))"));
	cout << endl;
	l.print(l.build("(car(car'((rs)(tx))))"));
	cout << endl;
	l.print(l.build("(cons '(xs) '((tx)))"));
	cout << endl;
	l.print(l.build("(cdr(cons(car'(r)) '(stx)))"));
	cout << endl;
	l.print(l.build("(cons (car '(rv)) (cdr '(tx)))"));
	cout << endl;
	system("pause");
	return 0;
}