/*
Adam Novoa
CS 372
List template
11/9/2014
*/

#include<iostream>
#include<iomanip>

using namespace std;

template <typename VT>
class List
{
private:
	const static int SIZE = 20;
	VT ary[SIZE];
	int pos;
	int used;

public:
	List()
	{
		pos = 0;
		used = 0;
		for (int i = 0; i < SIZE; i++)
		{
			ary[i] = 0;
		}
		return;
	}
	template <typename VT>
	List(List<VT>&s)
	{
		used = 0;
		pos = getPos();
		for (int i = 0; i < SIZE; i++)
		{
			if (s.setPos(i))
				used++;
			ary[i] = s.getElement();
		}
		setPos(pos);
		used = 0;
	}

	VT getElement()
	{
		if (pos < used && pos >= 0)
		{
			return ary[pos];
		}
		else
		{
			return 0;
		}
	}
	bool setPos(int index)
	{
		if (index < used && index >= 0)
		{
			pos = index;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool front()
	{
		if (used > 0)
		{
			setPos(0);
			return true;
		}
		else
		{
			return false;
		}
	}
	bool end()
	{
		if (used > 0)
		{
			setPos(used - 1);
		}
		else
		{
			return false;
		}
	}
	bool prev()
	{
		if (pos > 0)
		{
			pos--;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool next()
	{
		if (pos < used - 1)
		{
			pos++;
			return true;
		}
		else
		{
			return false;
		}
	}
	int getPos()
	{
		return pos;
	} 
	bool insertBefore(VT val)
	{
		if (used == 0)
		{
			ary[0] = val;
			used++;
			pos = 0;
			return true;
		}
		else if (used < SIZE)
		{
			for (int i = used; i >= pos; i--)
			{
				ary[i] = ary[i - 1];
			}
			ary[pos] = val;
			used++;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool insertAfter(VT val)
	{

		if (used == 0)
		{
			ary[0] = val;
			used++;
			pos = 0;
			return true;
		}
		else if (used < SIZE && pos >= 0)
		{
			for (int i = used; i >= pos + 1; i--)
			{
				ary[i] = ary[i - 1];
			}
			ary[pos + 1] = val;
			used++;
			pos++;
			return true;
		}
		else
		{
			return false;
		}
	}

	int size()
	{
		return used;
	}
	template <typename VT>
	bool operator==(List<VT>& b)
	{
		bool flag = false;

		if (used != b.size())
		{
			return false;
		}
		if (pos != b.getPos())
		{
			return false;
		}
		int Tpos = b.getPos();
		for (int i = 0; i < used; i++)
		{
			b.setPos(i);
			if (ary[i] != b.getElement())
			{
				return false;
			}
		}
		return true;
	}
	template <typename VT>
	bool operator!=(List<VT>& b)
	{
		return !(operator==(b));
	}

	bool empty()
	{
		return !used;
	}

	void replace(VT val)
	{
		ary[pos] = val;
	}
	bool erase()
	{
		if (used > 0)
		{
			for (int i = pos; i < used; i++)
			{
				ary[i] = ary[i + 1];
			}
			used--;
			if (pos != used)
				return true;
			else
			{
				pos--;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	void clear()
	{
		for (int i = 0; i < used; i++)
		{
			ary[i] = 0;
		}
		used = 0;
		pos = 0;
	}
	void reverse()
	{
		int temp[SIZE];
		for (int i = 0; i < used; i++)
		{
			temp[i] = ary[i];
		}
		for (int i = 0; i < used; i++)
		{
			ary[i] = temp[used - (i + 1)];
		}
	}
	template <typename VT>
	void swap(List<VT>& b)
	{
		List <VT>temp(b);
		int Tpos = b.getPos();
		temp.setPos(0);
		temp.used = b.size();
		b.clear();
		for (int i = 0; i < SIZE; i++)
		{
			if (i < used)
			{
				b.insertAfter(ary[i]);
			}
			temp.setPos(i);
			ary[i] = temp.getElement();
		}
		b.setPos(Tpos);
		used = temp.size();
	}
	template <typename VT>
	friend ostream& operator<<(ostream& out, List<VT>& l);

};

template <typename VT>
ostream& operator<<(ostream& out, List<VT>& l)
{
	int Tpos = l.getPos();

	for (int i = 0; i < l.size(); i++)
	{
		l.setPos(i);
		int val = l.getElement();
		out << left << val << " ";
	}
	l.setPos(Tpos);
	return out;
}

int main()
{
	List<int> a, b;  int endit;
	
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

	List<int> c(b);
	cout << "Copy Constructor c(b)" << endl;
	cout << "List b : " << b << endl;
	cout << "List c : " << c << endl;

	if (c == b)
		cout << "List c & b are equal" << endl;
	else
		cout << "List c & b are Not equal" << endl;


	List<int> e;
	e = c;
	cout << "Object 'c' assigned to Object 'e':" << endl;
	cout << "List c : " << c << endl;
	cout << "List e : " << e << endl;

	List<int> d;
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

	List<int> alist(b);
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

	List<int> newa;
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
	List<int> sq;
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
List a: 1 2 3 4 5 6 7 8 9 17 18 19 20
Copy Constructor c(b)
List b : 20 19 18 17 16 15 14 13 12 7 10 9 8 7 6 5 4 3 2 1
List c :
List c & b are Not equal
Object 'c' assigned to Object 'e':
List c :
List e :
Results after some erases: Object d
List d : 1 3 5 7 9 18 20
Results after some Replaces on d
List d : 2 1 6 3 10 5 14 7 18 9 36 18 20
Results after some weird stuff on list a
List a : 1 2 5 4 9 6 13 8 17 17 28 19 92
New List alist with positions above:
0    1    2    3    4    5    6    7    8    9
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
empty sq values
sq values 999
sq.getElement() = 999
sq values 999
Press any key to continue . . .
*/