/*
Adam Novoa
CS 372
More Statistician
9/8/2014
*/

#include<iostream>

using namespace std;

class statistician
{
private:
	double sum;
	double length;
	double smallest;
	double largest;

public:

	statistician()
	{
		sum = 0;
		length = 0;
		smallest = 0;
		largest = 0;
	}
	statistician (statistician& s)
	{
		sum = s.getSum();
		length = s.getLength();
		smallest = s.getSmallest();
		largest = s.getLargest();
	}

	double getSum() const
	{
		return sum;
	}
	double getLength() const
	{
		return length;
	}
	double getLargest() const
	{
		return largest;
	}
	double getSmallest() const
	{
		return smallest;
	}
	double getMean() const
	{
		if (getLength())
		{
			return getSum() / getLength();
		}
		else
		{
			return 0;
		}
	}

	void setSum(double temp)
	{
		sum = temp;
		return;
	}
	void setLength(double temp)
	{
		length = temp;
		return;
	}
	void setLargest(double temp)
	{
		if (temp > getLargest())
		{
			largest = temp;
		}
		return;
	}
	void setSmallest(double temp)
	{
		if (temp < getSmallest())
		{
			smallest = temp;
		}
		return;
	}

	void next_number(double temp)
	{
		sum += temp;
		length++;

		if (temp > getLargest())
		{
			largest = temp;
		}
		if (temp < getSmallest())
		{
			smallest = temp;
		}
		return;
	}

	bool operator==(statistician& stat)
	{
		if (sum != stat.getSum())
		{
			return false;
		}
		if (length != stat.getLength())
		{
			return false;
		}
		if (largest != stat.getLargest())
		{
			return false;
		}
		if (smallest != stat.getSmallest())
		{
			return false;
		}
		return true;
	}

	bool operator!=(statistician& stat)
	{
		if (sum != stat.getSum())
		{
			return true;
		}
		if (length != stat.getLength())
		{
			return true;
		}
		if (largest != stat.getLargest())
		{
			return true;
		}
		if (smallest != stat.getSmallest())
		{
			return true;
		}
		return false;
	}

	friend ostream& operator<<(ostream& out, const statistician& stat);
	friend statistician operator+(statistician& stat1, statistician& stat2);

	void erase()
	{
		sum = 0;
		length = 0;
		largest = 0;
		smallest = 0;
		return;
	}
};

int main()
{
	statistician stat1;

	stat1.next_number(5.5);
	stat1.next_number(6.6);
	stat1.next_number(8.8);
	stat1.next_number(-3.4);
	stat1.next_number(-0.5);
	stat1.next_number(4.7);
	stat1.next_number(9.1);

	cout << "Sum = " << stat1.getSum() << endl;
	cout << "Length = " << stat1.getLength() << endl;
	cout << "Mean = " << stat1.getMean() << endl;

	stat1.next_number(5.2);
	stat1.next_number(-3.3);
	stat1.next_number(-8.5);
	stat1.next_number(3.2);
	stat1.next_number(5.5);

	cout << "\nStatistician 1 " << endl << stat1;

	statistician stat2(stat1);

	cout << "\nStatistician 1 " << endl << stat1 << "\nStatistician 2 " << endl << stat2;

	stat2.next_number(13);
	stat2.next_number(21);
	stat2.next_number(71);
	stat2.next_number(47);
	stat2.next_number(12);
	stat2.next_number(25);
	stat2.next_number(24);
	stat2.next_number(23);
	stat2.next_number(24);
	stat2.next_number(32);

	cout << "Sum = " << stat2.getSum() << endl;
	cout << "Length = " << stat2.getLength() << endl;
	cout << "Mean = " << stat2.getMean() << endl;

	cout << "\nStatistician 1 " << endl << stat1 << "\nStatistician 2 " << endl << stat2;

	statistician stat3 = stat1 + stat2;

	cout << "\nStatistician 1 " << endl << stat1 << "\nStatistician 2 " << endl << stat2 << "\nStatistician 3 " << endl << stat3;

	stat2.erase();

	cout << "\nStatistician 1 " << endl << stat1 << "\nStatistician 2 " << endl << stat2 << "\nStatistician 3 " << endl << stat3;

	system("pause");
	return 0;
}

statistician operator+(statistician& stat1, statistician& stat2)
{
	statistician temp;

	temp.setSum(stat1.getSum() + stat2.getSum());

	temp.setLength(stat1.getLength() + stat2.getLength());
	
	if (stat1.getLargest() > stat2.getLargest())
	{
		temp.setLargest(stat1.getLargest());
	}
	else
	{
		temp.setLargest(stat2.getLargest());
	}

	if (stat1.getSmallest() < stat2.getSmallest())
	{
		temp.setSmallest(stat1.getSmallest());
	}
	else
	{
		temp.setSmallest(stat2.getSmallest());
	}	

	return temp;
}

ostream& operator<<(ostream& out, const statistician& stat)
{
	out << "Sum  = " << stat.getSum() << endl
	<< "Length = " << stat.getLength() << endl
	<< "Mean = " << stat.getMean() << endl
	<< "Largest = " << stat.getLargest() << endl
	<< "Smallest = " << stat.getSmallest() << endl;
	
	return out;
}

/*
Output

Sum = 30.8
Length = 7
Mean = 4.4

Statistician 1
Sum  = 32.9
Length = 12
Mean = 2.74167
Largest = 9.1
Smallest = -8.5

Statistician 1
Sum  = 32.9
Length = 12
Mean = 2.74167
Largest = 9.1
Smallest = -8.5

Statistician 2
Sum  = 32.9
Length = 12
Mean = 2.74167
Largest = 9.1
Smallest = -8.5
Sum = 324.9
Length = 22
Mean = 14.7682

Statistician 1
Sum  = 32.9
Length = 12
Mean = 2.74167
Largest = 9.1
Smallest = -8.5

Statistician 2
Sum  = 324.9
Length = 22
Mean = 14.7682
Largest = 71
Smallest = -8.5

Statistician 1
Sum  = 32.9
Length = 12
Mean = 2.74167
Largest = 9.1
Smallest = -8.5

Statistician 2
Sum  = 324.9
Length = 22
Mean = 14.7682
Largest = 71
Smallest = -8.5

Statistician 3
Sum  = 357.8
Length = 34
Mean = 10.5235
Largest = 71
Smallest = -8.5

Statistician 1
Sum  = 32.9
Length = 12
Mean = 2.74167
Largest = 9.1
Smallest = -8.5

Statistician 2
Sum  = 0
Length = 0
Mean = 0
Largest = 0
Smallest = 0

Statistician 3
Sum  = 357.8
Length = 34
Mean = 10.5235
Largest = 71
Smallest = -8.5
Press any key to continue . . .
*/