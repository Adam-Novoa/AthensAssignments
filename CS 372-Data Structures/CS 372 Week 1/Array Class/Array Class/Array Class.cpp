/*
Adam Novoa
CS 372
Array Class
8/25/2014
*/

#include<iostream>

using namespace std;

class arrayClass
{
private:
	int size;
	double *ptr;

public:
	arrayClass(int value = 5)
	{
		if (value > 0)
		{
			ptr = new double[value];
			size = value;
		}
		else if (value <= 0)
		{
			cout << "Error the size of the array must be greater than zero." << endl;
			cout << "Array size set to 5" << endl;
			ptr = new double[5];
			size = 5;
		}
		initArray();
	}

	void initArray()
	{
		for (int i = 0; i < size; i++)
		{
			*(ptr + i) = 0;
		}
	}

	void setVal(int index, double val)
	{
		if (index >= size || index < 0)
		{
			cout << "Error index outside of array." << endl;
			return;
		}
		*(ptr + index) = val;
		return;
	}

	double getVal(int index)
	{
		if (index >= size || index < 0)
		{
			cout << "Error index outside of array." << endl;
			return 0;
		}
		return *(ptr + index);
	}

	double highest()
	{
		double tempHigh = *ptr;

		for (int i = 1; i < size; i++)
		{
			if (*(ptr + i) > tempHigh)
			{
				tempHigh = *(ptr + i);
			}
		}
		return tempHigh;
	}

	double lowest()
	{
		double tempLow = *ptr;

		for (int i = 1; i < size; i++)
		{
			if (*(ptr + i) < tempLow)
			{
				tempLow = *(ptr + i);
			}
		}
		return tempLow;
	}

	int nonZero()
	{
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (*(ptr + i) != 0)
				count++;
		}
		return count;
	}

	double avg(int divisor)
	{
		
		double total = 0;
		for (int i = 0; i < size; i++)
		{
			total += *(ptr + i);
		}
		
		if (divisor <= 0)
		{
			return total / size;
		}
		else
		{
			return total / divisor;
		}
	}
};



int main()
{
	int run = 0;
	while (run < 2)
	{
		int size;
		int choice = 0;
		int index;
		int val;
		cout << "Please enter the size of the array." << endl;
		cin >> size;

		arrayClass L(size);

		while (choice != -1)
		{
			cout << "Please select an option." << endl;
			cout << "1. Set the value of an element of the array." << endl;
			cout << "2. View the value of an element of the array." << endl;
			cout << "3. View the Highest value of the array." << endl;
			cout << "4. View the Lowest value of the array." << endl;
			cout << "5. View the average value of the array." << endl;
			cout << "6. View the average value of all nonzero elements of the array." << endl;
			cout << "-1. QUIT." << endl;

			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Please enter the index of the element." << endl;
				cin >> index;
				cout << "Please enter the value for the element." << endl;
				cin >> val;
				L.setVal(index, val);
				break;
			case 2:
				cout << "Please enter the index of the element." << endl;
				cin >> index;
				cout << L.getVal(index) << endl;
				break;
			case 3:
				cout << "The highest value of the array is " << L.highest() << endl;
				break;
			case 4:
				cout << "The lowest value of the array is " << L.lowest() << endl;
				break;
			case 5:
				cout << "The average value of the array is " << L.avg(size) << endl;
				break;
			case 6:
				cout << "The average value of all nonzero elements is " << L.avg(L.nonZero()) << endl;
				break;
			case -1:
				break;
			default:
				cout << "Error selection is not available." << endl;
				break;
			}
		}
		run++;
	}




	system("pause");
	return 0;
}
/*Output as follows

Please enter the size of the array.
4
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
0
Please enter the value for the element.
91
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
2
Please enter the value for the element.
-50
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
9
Please enter the value for the element.
6
Error index outside of array.
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
-5
Please enter the value for the element.
2
Error index outside of array.
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
1
Please enter the value for the element.
1089
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
2
Please enter the index of the element.
0
91
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
2
Please enter the index of the element.
6
Error index outside of array.
0
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
3
The highest value of the array is 1089
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
4
The lowest value of the array is -50
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
5
The average value of the array is 282.5
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
6
The average value of all nonzero elements is 376.667
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
-1
Please enter the size of the array.
-9
Error the size of the array must be greater than zero.
Array size set to 5
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
3
Please enter the value for the element.
50
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
2
Please enter the value for the element.
-90
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
1
Please enter the value for the element.
-180
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
1
Please enter the index of the element.
0
Please enter the value for the element.
80
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
2
Please enter the index of the element.
1
-180
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
3
The highest value of the array is 80
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
4
The lowest value of the array is -180
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
5
The average value of the array is -28
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
6
The average value of all nonzero elements is -35
Please select an option.
1. Set the value of an element of the array.
2. View the value of an element of the array.
3. View the Highest value of the array.
4. View the Lowest value of the array.
5. View the average value of the array.
6. View the average value of all nonzero elements of the array.
-1. QUIT.
-1
Press any key to continue . . .
*/