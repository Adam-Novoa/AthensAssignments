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
	element* eval(element* tp)
	{
		if (tp->down->el == "cons")
		{
			return cons(tp->down);
		}
		else if (tp->down->el == "car")
		{
//			tp = tp->down->down;
			return car(tp->down);
		}
		else if (tp->down->el == "cdr")
		{
			tp = tp->down->down;
			return cdr(tp);
		}
		return tp;
	}
	element* car(element* tp)// Done?
	{
		element* t = newElement();
		if (tp->down->down->el == "cons")
		{
			t->el = cons(tp->down->down)->down->down->down->el;
		}
		else if (tp->down->down->el == "car")
		{
			t->el = car(tp->down)->down->down->down->el;
		}
		else if (tp->down->down->el == "cdr")
		{
			tp = tp->down->down->down;
			
			t->el = cdr(tp)->down->el;
		}
		else
		{
			t->el = tp->down->down->el;
		}
		return t;
	}
	element* cdr(element* tp)
	{
		if (tp->down != NULL && tp->down->el == "cons")
		{
			cons(tp->down);
		}
		else if (tp->down != NULL && tp->down->el == "car")
		{
			car(tp->down);
		}
		else if (tp->down != NULL && tp->down->el == "cdr")
		{
			tp = tp->down->down;
			cdr(tp);
		}
		tp->down = tp->down->right;
		return tp;
	}
	element* cons(element* tp)
	{
		if (tp->down != NULL && tp->down->el == "cons")
		{
			cons(tp->down);
		}
		else if (tp->down != NULL && tp->down->el == "car")
		{
			car(tp->down);
		}
		else if (tp->down != NULL && tp->down->el == "cdr")
		{
			tp = tp->down->down;
			cdr(tp);
		}
		if (tp->down->el == "(")
		{

		}


		return tp;
	}
	void print(element* tp)
	{
		if (tp->el == "(")
		{
			cout << tp->el;
			print(tp->down);
			if (tp->right != NULL)
			{
				depth++;
				print(tp->right);
				depth--;
			}
			if (tp == head)//fix
			{
				cout << endl;
			}
		}
		else
		{
			cout << tp->el;
			if (tp->down != NULL)
			{
				depth++;
				print(tp->down);
				depth--;
			}
		//	cout << tp->el;
			if (tp->right != NULL)
			{
				depth++;
				print(tp->right);
				depth--;
			}
		}
		if (depth == 0)// && tp->down->el != "cons")
		{
			cout << endl;
		}
		return;
	}

};

int main()
{
	List l;
//	l.build("(car '( a b c d))");
//	l.print(l.eval(l.build("(car (cdr(cdr'(rstz))))")));
	l.print(l.build("(car'((r)stz))"));
	l.print(l.eval(l.build("(cons'(r) '(stz))")));
	l.print(l.build("(cons ( car '(rv)) (cdr '(tx)))"));
	l.print(l.build("(cdr( cdr( cdr( cdr '(rstz))) ))"));
	l.print(l.eval(l.build("(cons'r '(stz))")));
	system("pause");
	return 0;
}