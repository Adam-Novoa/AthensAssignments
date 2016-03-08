/*
Interpreter pgrm
CS 414
Adam Novoa
8/23/2015
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const long long fin = 9999999999;

int main()
{
	ifstream infile;
	infile.open("input.txt");
	ofstream outfile;
	outfile.open("result.dat");
	long long numbers[1000];
	long long commands[1000];

	long long temp = 0;
	infile >> temp;
	int numIndex = 0;
	int comIndex = 0;
	int resultIndex = 0;

	while (temp != fin)
	{
		numbers[numIndex] = temp;
		numIndex++;
		infile >> temp;
	}
	do {
		infile >> temp;
		commands[comIndex] = temp;
		comIndex++;
	} while (temp != fin);
	comIndex = 0;

	int op1, op2, op3;

	int com = 0;
	int count = 1000;
	while (com != 9)
	{
		
		com = commands[comIndex] / 1000000000;
		if (com >= 0)
		{
			op1 = (commands[comIndex] / 1000000) % 1000;
			op2 = (commands[comIndex] / 1000) % 1000;
			op3 = commands[comIndex] % 1000;
		}
		else
		{
			op1 = (-1 * commands[comIndex] / 1000000) % 1000;
			op2 = (-1 * commands[comIndex] / 1000) % 1000;
			op3 = -1 * commands[comIndex] % 1000;
		}
		switch (com)
		{
		case 0://move
			numbers[op3] = numbers[op1];
			comIndex++;
			break;
		case 1://add
			if (numbers[op1] + numbers[op2] >= 0)
			{
				numbers[op3] = (numbers[op1] + numbers[op2]) % 10000000000;
			}
			else
			{
				numbers[op3] = (((numbers[op1] + numbers[op2])*-1) % 10000000000)*-1;
			}
			comIndex++;
			break;
		case 2://multiply
			if (numbers[op1] * numbers[op2] >=0)
			{
				numbers[op3] = (numbers[op1] * numbers[op2]) % 10000000000;
			}
			else
			{
				numbers[op3] = (((numbers[op1] * numbers[op2])*-1) % 10000000000)*-1;
			}
			comIndex++;
			break;
		case 3://square
			numbers[op3] = (numbers[op1] * numbers[op1]) % 10000000000;
			comIndex++;
			break;
		case 4://==
			if (numbers[op1] == numbers[op2])
			{
				comIndex = op3;
			}
			else
			{
				comIndex++;
			}
			break;
		case 5://>=
			if (numbers[op1] >= numbers[op2])
			{
				comIndex = op3;
			}
			else
			{
				comIndex++;
			}
			break;
		case 6://x[y] -> z
			numbers[op3] = numbers[op1 + numbers[op2]];
			comIndex++;
			break;
		case 7://incr. and test
			// format iii nnn ddd
			// i = addres of index
			// n = addres upper bound of array
			// d = addres of instruction to loop to
			numbers[op1]++;
			if (numbers[op1] < numbers[op2])
			{
				comIndex = commands[op3];
			}
			else
			{
				comIndex++;
			}
			break;
		case 8://read
			infile >> numbers[op3];
			comIndex++;
			break;
		case 9://stop

			break;
		case -1://minus
			if (numbers[op1] - numbers[op2] >= 0)
			{
				numbers[op3] = (numbers[op1] - numbers[op2]) % 10000000000;
			}
			else
			{
				numbers[op3] = (((numbers[op1] - numbers[op2])*-1) % 10000000000)*-1;
			}
			comIndex++;
			break;
		case -2://divide
			numbers[op3] = numbers[op1] / numbers[op2];
			comIndex++;
			break;
		case -3://square root
			numbers[op3] = sqrt(numbers[op1]);
			comIndex++;
			break;
		case -4://!=
			if (numbers[op1] != numbers[op2])
			{
				comIndex = op3;
			}
			else
			{
				comIndex++;
			}
			break;
		case -5://<
			if (numbers[op1] < numbers[op2])
			{
				comIndex = op3;
			}
			else
			{
				comIndex++;
			}
			break;
		case -6://x -> y[z]
			numbers[op2 + numbers[op3]] = numbers[op1];
			comIndex++;
			break;
		case -8://print
			outfile << numbers[op3] << endl;
			comIndex++;
			break;
		case -9://debug
			comIndex++;
			break;
		default:
			cout << "Error invalid operation pos " << comIndex << endl;
			comIndex++;
			break;
		}
	}
	system("pause");
	return 0;
}