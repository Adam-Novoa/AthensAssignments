/*
Adam Novoa
Queue Class
CS 372
9/29/2014
*/

#include<iostream>

using namespace std;

class List
{
	typedef char VT;
private:
	const static int SIZE = 26;
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
			ary[i] = ' ';
		}
		return;
	}
	List(List &s)
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
	bool operator==(List& b)
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
	bool operator!=(List& b)
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
			ary[i] = ' ';
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
	void swap(List& b)
	{
		List temp(b);
		int Tpos = b.getPos();
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

	friend ostream& operator<<(ostream& out, List& l);
};

ostream& operator<<(ostream& out, List& l)
{
	int Tpos = l.getPos();

	for (int i = 0; i < l.size(); i++)
	{
		l.setPos(i);
		char val = l.getElement();
		out << left << val << " ";
	}
	l.setPos(Tpos);
	return out;
}

class Queue
{
private:
	typedef char VT;
	List list1;

public:
	Queue()
	{

	}
	void front()
	{
		list1.front();
		return;
	}
	void next()
	{
		if (list1.next())
		{

		}
		else
		{
			list1.front();
		}
		return;
	}
	void erase()
	{
		list1.erase();
	}
	void insert(VT val)
	{
		list1.insertAfter(val);
		return;
	}
	int size()
	{
		return list1.size();
	}

	friend ostream& operator<<(ostream& out, Queue& Q);
};
ostream& operator<<(ostream& out, Queue& Q)
{
	out << Q.list1;
	return out;
}


int main()
{
	Queue suitors;
	char temp = 'A';
	for (int i = 0; i <= 26; i++)
	{
		suitors.insert(temp + i);
	}
	suitors.front();
	while (suitors.size() > 1)
	{
		cout << "Suitors remaining." << endl;
		cout << suitors << endl;
		for (int i = 0; i < 2; i++)
		{
			suitors.next();
		}
		suitors.erase();
	}
	cout << "Winning suitor." << endl;
	cout << suitors << endl;

	system("pause");
	return 0;
}
/*
output
Suitors remaining.
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
Suitors remaining.
A B D E F G H I J K L M N O P Q R S T U V W X Y Z
Suitors remaining.
A B D E G H I J K L M N O P Q R S T U V W X Y Z
Suitors remaining.
A B D E G H J K L M N O P Q R S T U V W X Y Z
Suitors remaining.
A B D E G H J K M N O P Q R S T U V W X Y Z
Suitors remaining.
A B D E G H J K M N P Q R S T U V W X Y Z
Suitors remaining.
A B D E G H J K M N P Q S T U V W X Y Z
Suitors remaining.
A B D E G H J K M N P Q S T V W X Y Z
Suitors remaining.
A B D E G H J K M N P Q S T V W Y Z
Suitors remaining.
B D E G H J K M N P Q S T V W Y Z
Suitors remaining.
B D G H J K M N P Q S T V W Y Z
Suitors remaining.
B D G H K M N P Q S T V W Y Z
Suitors remaining.
B D G H K M P Q S T V W Y Z
Suitors remaining.
B D G H K M P Q T V W Y Z
Suitors remaining.
B D G H K M P Q T V Y Z
Suitors remaining.
D G H K M P Q T V Y Z
Suitors remaining.
D G K M P Q T V Y Z
Suitors remaining.
D G K M Q T V Y Z
Suitors remaining.
D G K M Q T Y Z
Suitors remaining.
G K M Q T Y Z
Suitors remaining.
G K Q T Y Z
Suitors remaining.
G K Q T Z
Suitors remaining.
G Q T Z
Suitors remaining.
G Q T
Suitors remaining.
G T
Winning suitor.
G
Press any key to continue . . .
*/