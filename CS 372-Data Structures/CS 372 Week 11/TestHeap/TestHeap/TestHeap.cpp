/*
Adam Novoa
Heap
CS 372
11/9/2014
*/

#include<iostream>
#include<fstream>

using namespace std;

class heap
{
	typedef int VT;
private:
	static const int CAPACITY = 100;
	VT val[CAPACITY];// ID number
	int priorty[CAPACITY];// priorty
	int order[CAPACITY];// order values came in
	int size;
	int count;

public:
	heap()
	{
		for (int i = 0; i < CAPACITY; i++)
		{
			val[i] = 0;
			priorty[i] = -1;
			order[i] = 9999;
		}
		size = 0;
		count = 0;
	}

	heap(heap &h)
	{
		for (int i = 0; i < CAPACITY; i++)
		{
			val[i] = h.val[i];
			priorty[i] = h.priorty[i];
			order[i] = h.order[i];
		}
		size = h.size;
		count = h.count;
	}
	bool push(VT num, int pri)
	{
		if (size < CAPACITY)
		{
			val[size] = num;
			priorty[size] = pri;
			order[size] = count;
			count++, size++;
			shuffle();
			return true;
		}
		return false;
	}

	int getsize()
	{
		return size;
	}

	VT pop()
	{
		VT temp = val[0];
		val[0] = val[size - 1];
		priorty[0] = priorty[size - 1];
		order[0] = order[size - 1];
		val[size - 1] = 0;
		priorty[size - 1] = 0;
		order[size - 1] = 0;
		size--;
		shuffle();
		return temp;
	}
	void shuffle()
	{
		bool done = true;
		int pos = 0;
		while (!done || (pos + 1) * 2 - 1 < getsize())
		{
			if ((pos + 1) * 2 - 1 >= getsize())
			{
				done = true;
				pos = 0;
			}
			if (priorty[pos] < priorty[(pos + 1) * 2 - 1] || priorty[pos] < priorty[(pos + 1) * 2])// a child is greater than parrent
			{
				done = false;
				VT tempVal = val[pos];
				int tempPri = priorty[pos];
				int tempOrder = order[pos];

				if (priorty[(pos + 1) * 2 - 1] < priorty[(pos + 1) * 2])// right child is greater than left
				{
					priorty[pos] = priorty[(pos + 1) * 2];
					val[pos] = val[(pos + 1) * 2];
					order[pos] = order[(pos + 1) * 2];
					priorty[(pos + 1) * 2] = tempPri;
					val[(pos + 1) * 2] = tempVal;
					order[(pos + 1) * 2] = tempOrder;
				}
				else // left child is greater than right
				{
					priorty[pos] = priorty[(pos + 1) * 2 - 1];
					val[pos] = val[(pos + 1) * 2 - 1];
					order[pos] = order[(pos + 1) * 2 - 1];
					priorty[(pos + 1) * 2 - 1] = tempPri;
					val[(pos + 1) * 2 - 1] = tempVal;
					order[(pos + 1) * 2 - 1] = tempOrder;
				}
			}
			else if (priorty[pos] == priorty[(pos + 1) * 2 - 1])
			{
				if (order[pos] > order[(pos + 1) * 2 - 1])
				{
					done = false;
					VT tempVal = val[pos];
					int tempPri = priorty[pos];
					int tempOrder = order[pos];

					priorty[pos] = priorty[(pos + 1) * 2 - 1];
					val[pos] = val[(pos + 1) * 2 - 1];
					order[pos] = order[(pos + 1) * 2 - 1];
					priorty[(pos + 1) * 2 - 1] = tempPri;
					val[(pos + 1) * 2 - 1] = tempVal;
					order[(pos + 1) * 2 - 1] = tempOrder;
					done = false;
				}
			}
			else if (priorty[pos] == priorty[(pos + 1) * 2])
			{
				if (order[pos] > order[(pos + 1) * 2])
				{
					done = false;
					VT tempVal = val[pos];
					int tempPri = priorty[pos];
					int tempOrder = order[pos];

					priorty[pos] = priorty[(pos + 1) * 2];
					val[pos] = val[(pos + 1) * 2];
					order[pos] = order[(pos + 1) * 2];
					priorty[(pos + 1) * 2] = tempPri;
					val[(pos + 1) * 2] = tempVal;
					order[(pos + 1) * 2] = tempOrder;
					done = false;
				}
			}
			pos++;
		}
		return;
	}

	void clear()
	{
		for (int i = 0; i < CAPACITY; i++)
		{
			val[i] = 0;
			priorty[i] = -1;
			order[i] = 9999;
		}
		size = 0;
		count = 0;
	}
};



ifstream infile;
int main()
{
	heap id;
	int idNbr;
	int priority;
	char trash;
	infile.open("HeapPriortyNbrs.dat");


	for (int i = 1; i <= 100; i++)
	{
		infile >> idNbr;
		infile >> trash;
		infile >> priority;
		id.push(idNbr, priority);
	}
	cout << "Set 1" << endl;
	for (int i = 1; i <= 25; i++)
	{
		cout << id.pop() << " ";
	}
	cout << endl;
	id.clear();

	for (int i = 1; i <= 100; i++)
	{
		infile >> idNbr;
		infile >> trash;
		infile >> priority;
		id.push(idNbr, priority);
	}
	cout << "Set 2" << endl;
	for (int i = 1; i <= 25; i++)
	{
		cout << id.pop() << " ";
	}
	cout << endl;
	id.clear();

	infile >> idNbr;
	infile >> trash;
	infile >> priority;
	while (!infile.eof())
	{
		id.push(idNbr, priority);
		infile >> idNbr;
		infile >> trash;
		infile >> priority;
	}
	cout << "Set 3" << endl;
	for (int i = 1; i <= 25; i++)
	{
		cout << id.pop() << " ";
	}
	cout << endl;
	id.clear();

	system("pause");
	return 0;
}