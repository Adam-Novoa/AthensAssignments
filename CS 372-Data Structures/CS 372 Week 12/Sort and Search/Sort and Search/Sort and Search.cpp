/*
Adam Novoa
Sorts Search
CS 372
11/17/2014
*/

#include<iostream>
#include<cstdlib>

using namespace std;

void bubbleSort(int[]);
void selectionSort(int[]);
void quickSort(int[], int size, int);
int partition(int data[], int n, int pivotIndex);

const int size = 10000;

int main()
{
	int numbers[10000];
	int sort[10000];
	for (int i = 0; i < size; i++)
	{
		numbers[i] = (rand() % 200000) + 1;
		sort[i] = numbers[i];
	}
	bubbleSort(numbers);
	selectionSort(numbers);
	quickSort(sort, 0, size - 1);
	
	
	system("pause");
	return 0;
}

void bubbleSort(int numbers[])
{
	int sort[10000];
	for (int i = 0; i < size; i++)
	{
		sort[i] = numbers[i];
	}
	bool done = false;
	while (done != true)
	{
		done = true;
		for (int i = 0; i < size-1; i++)
		{
			if (sort[i] > sort[i + 1])
			{
				done = false;
				int temp = sort[i];
				sort[i] = sort[i + 1];
				sort[i + 1] = temp;
			}
		}
	}
	return;
}

void selectionSort(int numbers[])
{
	int sort[10000];
	for (int i = 0; i < size; i++)
	{
		sort[i] = numbers[i];
	}

	for (int i = size; i > 0; i--)
	{
		int index = 0;
		int largest = sort[0];
		for (int j = 0; j < i; j++)
		{
			if (sort[j]>largest)
			{
				largest = sort[j];
				index = j;
			}
		}
		int temp = sort[i - 1];
		sort[i - 1] = largest;
		sort[index] = temp;
	}
	return;
}

void quickSort(int data[], int begin, int end)
{
	if (begin < end)
	{
		int middle = partition(data, begin, end);
		quickSort(data, begin, middle);
		quickSort(data, middle + 1, end);
	}
	return;
}

int partition(int data[], int begin, int end)
{
	int pivot = data[begin];
	int small = end;
	int big = begin;
	int temp;

	while (big < small)
	{
		/*
		while (data[small] >= pivot)
		{
			small--;
		}
		temp = data[small];
		data[small] = pivot;
		pivot = temp;
		while (data[big] < pivot)
		{
			big++;
		}
		temp = data[big];
		data[big] = pivot;
		pivot = temp;
		*/

		while (data[small] >= pivot)
		{
			small--;
		}
//		temp = data[big];
//		data[big] = data[small];



		while (data[big] < pivot)
		{
			big++;
		}
//		temp = data[big];

		if (small < big)
		{
			temp = data[small];
			data[small] = data[big];
			data[big] = temp;
		}


	}
	return small;
}