/*
Adam Novoa
CS 372
GenList Linklist
10/12/2014
*/

#include<iostream>
#include<iomanip>

using namespace std;

class List
{
	typedef int VT;
private:
	struct LL
	{
		VT val;
		LL *flinky;
		LL *blinky;
	};

	LL *head;
	LL *tail;
	LL *pos;
	int used;

	LL* newNode()
	{
		LL *t;
		t = new LL;
		t->val = 0;
		t->flinky = NULL;
		t->blinky = NULL;
		return t;
	}

public:
	List()
	{
		head = NULL;
		tail = NULL;
		pos = NULL;
		used = 0;
	}
	List(List &s)
	{
		head = NULL;
		tail = NULL;
		pos = NULL;
		used = 0;

		if (int tpos = s.getPos())//Might be a bad idea
		{
			s.front();
			insertAfter(s.getElement());
			while (s.next())
			{
				insertAfter(s.getElement());
			}
			s.setPos(tpos);
		}
	}
	VT getElement()
	{
		if (pos)
		{
			return pos->val;
		}
		return 0;
	}
	bool setPos(int index)	//test
	{
		LL *c = head;
		for (; index; index--)// == for (index = index; index!=0; index--)
		{
			if (c)
			{
				pos = c;
				c = c->flinky;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	bool front()
	{
		if (head)
		{
			pos = head;
			return true;
		}
		return false;
	}
	bool end()
	{
		if (tail)
		{
			pos = tail;
			return true;
		}
		return false;
	}
	bool prev()
	{
		if (pos && pos->blinky)
		{
			pos = pos->blinky;
			return true;
		}
		return false;
	}
	bool next()
	{
		if (pos && pos->flinky)
		{
			pos = pos->flinky;
			return true;
		}
		return false;
	}
	int getPos()
	{
		int count = 0;
		if (pos)
		{
			count++;
			LL *temp = head;
			while (temp && temp != pos)
			{
				temp = temp->flinky;
				count++;
			}
		}
		return count;
	}
	bool insertBefore(VT val)	//maybe not bool
	{
		if (prev())
		{
			insertAfter(val);
		}
		else
		{
			LL *t = newNode();
			t->val = val;
			if (pos)
			{
				t->flinky = pos;
				pos->blinky = t;
				head = t;
				pos = t;
				used++;
			}
			else
			{
				head = t;
				tail = t;
				pos = t;
				used++;
			}
		}
		return true;
	}
	bool insertAfter(VT val)	//maybe not bool
	{
		LL *t = newNode();
		t->val = val;
		if (pos)
		{
			if (pos->flinky)
			{
				t->flinky = pos->flinky;//sets t to point forward to the element after pos
				t->blinky = pos;		//sets t to point back to pos;
				pos->flinky->blinky = t;//sets the element after pos to point back to t
				pos->flinky = t;		//sets pos to point forward to t
				pos = t;
				used++;
			}
			else
			{
				t->flinky = NULL;		//sets t to point forward to NULL t already does but safety
				t->blinky = pos;		//sets t to point back to pos
				pos->flinky = t;		//sets pos to point forward to t
				tail = t;				//sets the end of the list to t
				pos = t;
				used++;
			}
		}
		else
		{
			head = t;//sets t to be the only element in the list
			tail = t;
			pos = t;
			used++;
		}
		return true;
	}
	int size()
	{
		return used;
	}
	bool operator==(List& b)
	{
		if (used != b.size())
		{
			return false;
		}
		LL *tpos1 = pos;//temp pos for this object
		LL *tpos2 = b.pos;//temp pos for object b

		front();
		b.front();
		
		do{
			if (pos->val != b.pos->val)
			{
				pos = tpos1;
				b.pos = tpos2;
				return false;
			}
		}while (next() && b.next());
		pos = tpos1;
		b.pos = tpos2;
		return true;
	}
	bool operator!=(List& b)
	{
		return !operator==(b);
	}
	bool empty()
	{
		return !size();
	}
	bool replace(VT val)	//test
	{
		if (pos)
		{
			pos->val = val;
			return true;
		}
		return false;
	}
	bool erase()	//test
	{
		if (pos)
		{
			LL *t = pos;
			if (pos->blinky && pos->flinky)//middle of list
			{
				pos->blinky->flinky = pos->flinky;
				pos->flinky->blinky = pos->blinky;
				pos = pos->blinky;
			}
			else if (pos->flinky)//front of list
			{
				head = pos->flinky;
				pos = pos->flinky;
				pos->blinky = NULL;
			}
			else if (pos->blinky)//end of list
			{
				tail = pos->blinky;
				pos = pos->blinky;
				pos->flinky = NULL;
			}
			else
			{
				pos = NULL;
				head = NULL;
				tail = NULL;
			}
			delete t;
			used--;
			return true;
		}
		return false;
	}
	void clear()	//test
	{
		if (tail)
		{
			LL *t = tail;
			while (t)
			{
				while (t->blinky)
				{
					t = t->blinky;
					delete t->flinky;
					used--;
				}
				delete t;
				used--;
				t = NULL;
			}
			tail = NULL;
			head = NULL;
			pos = NULL;
		}
	}
	void reverse()	//unfinished
	{
		if (pos)
		{
			List temp;
			int tpos = getPos();
			front();
			temp.insertAfter(pos->val);
			while (next())
			{
				temp.insertAfter(pos->val);
			}
			clear();
			insertAfter(temp.getElement());
			while (temp.prev())
			{
				insertAfter(temp.getElement());
			}
			setPos(tpos);
		}
		return;
	}
	void swap(List& b)	//unfinished
	{
		List t = b;
		b.head = head;
		b.tail = tail;
		head = t.head;
		tail = t.tail;
		return;
	}

	friend ostream& operator<<(ostream& out, List& l);

	void operator=(List &s)//Needed asignment operator overload
	{
		head = NULL;
		tail = NULL;
		pos = NULL;
		used = 0;

		if (int tpos = s.getPos())//Might be a bad idea
		{
			s.front();
			insertAfter(s.getElement());
			while (s.next())
			{
				insertAfter(s.getElement());
			}
			s.setPos(tpos);
		}
		return;
	}
};

ostream& operator<<(ostream& out, List& l)	//unfinished
{
	int Tpos = l.getPos();
	l.front();
	do
	{
		int val = l.getElement();
		out << left << val << " ";
	} while (l.next());

	l.setPos(Tpos);
	return out;
}


int main()
{
	List a, b;  int endit;

	for (int i = 1; i <= 20; i++)
		a.insertAfter(i);
	cout << "List a : " << endl;
	cout << "  " << a << endl;
	cout << "Number of elements in a - " << a.size() << endl;

	for (int i = 1; i <= 20; i++)
		b.insertBefore(i);
	cout << "List b : " << endl;
	cout << "  " << b << endl;
	cout << "Number of elements in b - " << b.size() << endl;

	if (a == b)
		cout << "List a & b are equal" << endl;
	else
		cout << "List a & b are Not equal" << endl;

	a.front();
	b.front();
	cout << "First elmenet in list a & b: " << a.getElement() << ", "
		<< b.getElement() << endl;
	for (int i = 0; i < a.size(); a.next(), i++);
	for (int i = 0; i < b.size(); b.next(), i++);
	cout << "Last elmenet in list a & b: " << a.getElement() << ", "
		<< b.getElement() << endl;
	cout << endl << endl << " Start of new stuff" << endl;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	a.front();
	b.front();
	endit = a.size() / 2;
	for (int i = 1; i<endit; i++)
	{
		a.next();
		b.next();
	}

	cout << "New position in Obj 'a' position = " << a.size() / 2 << endl;

	for (int i = 1; i<8; i++)
	{
		a.erase();
		b.replace(i);
	}

	cout << "Modified Object 'a' " << endl;
	cout << "List a: " << a << endl;

	List c(b);
	cout << "Copy Constructor c(b)" << endl;
	cout << "List b : " << b << endl;
	cout << "List c : " << c << endl;

	if (c == b)
		cout << "List c & b are equal" << endl;
	else
		cout << "List c & b are Not equal" << endl;


	List e;
	e = c;
	cout << "Object 'c' assigned to Object 'e':" << endl;
	cout << "List c : " << c << endl;
	cout << "List e : " << e << endl;

	List d;
	d = a;
	d.front();
	endit = d.size() / 2;
	for (int i = 1; i <= endit; i++)
	{
		d.next();
		d.erase();
	}
	cout << "Results after some erases: Object d  " << endl;
	cout << "List d : " << d << endl;

	d.front();
	endit = d.size();
	for (int i = 1; i < endit; d.next(), i++)
	{
		d.insertBefore(d.getElement() * 2);
		d.next();
	}
	cout << "Results after some Replaces on d " << endl;
	cout << "List d : " << d << endl;

	a.front();
	endit = a.size();
	for (int i = 1; i < endit; a.next(), i++)
	{
		a.insertBefore(a.getPos() + a.getElement());
		a.next();
		a.erase();
	}
	cout << "Results after some weird stuff on list a" << endl;
	cout << "List a : " << a << endl;

	List alist(b);
	alist.clear();
	for (int i = 1; i <= 10; i++)
		alist.insertAfter(i);
	alist.front();
	cout << "New List alist with positions above: " << endl;
	for (int i = 1; i <= 10; i++) {
		cout << setw(5) << alist.getPos();
		alist.next();
	}
	cout << endl;
	alist.front();
	for (int i = 1; i <= 10; i++) {
		cout << setw(5) << alist.getElement();
		alist.next();
	}
	cout << endl;

	alist.reverse();
	cout << "Reverse New List alist : " << endl;
	cout << "  " << alist << endl;

	List newa;
	for (int i = 1; i <= 20; i++)
		newa.insertAfter(i * 3);
	cout << "List alist and newa before swap " << endl;
	cout << " " << alist << endl;
	cout << " " << newa << endl;
	alist.swap(newa);
	cout << "List alist and newa after swap " << endl;
	cout << " " << alist << endl;
	cout << " " << newa << endl;


	cout << endl << "  check out boundary conditions" << endl;
	List sq;
	cout << "number of elements in empty sq list = " << sq.size() << endl;
	sq.front();
	sq.erase();
	cout << "empty sq values " << sq << endl;
	sq.insertBefore(999);
	cout << "sq values " << sq << endl;
	sq.next(); sq.next();
	cout << "sq.getElement() = " << sq.getElement() << endl;
	cout << "sq values " << sq << endl;
	system("pause");   //This statement not needed in code blocks, just VS.
	return 0;
}
/*
Output
List a :
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Number of elements in a - 20
List b :
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
Number of elements in b - 20
List a & b are Not equal
First elmenet in list a & b: 1, 20
Last elmenet in list a & b: 20, 1


Start of new stuff
a = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
b = 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
New position in Obj 'a' position = 10
Modified Object 'a'
List a: 1 2 3 11 12 13 14 15 16 17 18 19 20
Copy Constructor c(b)
List b : 20 19 18 17 16 15 14 13 12 7 10 9 8 7 6 5 4 3 2 1
List c : 20 19 18 17 16 15 14 13 12 7 10 9 8 7 6 5 4 3 2 1
List c & b are equal
Object 'c' assigned to Object 'e':
List c : 20 19 18 17 16 15 14 13 12 7 10 9 8 7 6 5 4 3 2 1
List e : 20 19 18 17 16 15 14 13 12 7 10 9 8 7 6 5 4 3 2 1
Results after some erases: Object d
List d : 1 15 16 17 18 19 20
Results after some Replaces on d
List d : 2 1 30 15 32 16 34 17 36 18 38 19 20
Results after some weird stuff on list a
List a : 2 4 6 15 17 19 21 23 25 27 29 31 20
New List alist with positions above:
1    2    3    4    5    6    7    8    9    10
1    2    3    4    5    6    7    8    9    10
Reverse New List alist :
10 9 8 7 6 5 4 3 2 1
List alist and newa before swap
10 9 8 7 6 5 4 3 2 1
3 6 9 12 15 18 21 24 27 30 33 36 39 42 45 48 51 54 57 60
List alist and newa after swap
3 6 9 12 15 18 21 24 27 30 33 36 39 42 45 48 51 54 57 60
10 9 8 7 6 5 4 3 2 1

check out boundary conditions
number of elements in empty sq list = 0
empty sq values 0
sq values 999
sq.getElement() = 999
sq values 999
Press any key to continue . . .
*/