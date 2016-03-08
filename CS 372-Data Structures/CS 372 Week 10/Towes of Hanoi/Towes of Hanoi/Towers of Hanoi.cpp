/*
Adam Novoa
CS 372
Towers of Hanoi
10/26/2014
*/
#include <iostream>
#include <time.h>
using namespace std;

void move(int n, char S, char D, char T);
double moves = 0;
int main()
{
	system("pause");
	move(100, 'A', 'C', 'B');
	cout << "Moves taken " << moves << endl;
	system("pause");
	return 0;
}

void move(int n, char S, char D, char T)
{	
	if (n == 1)
	{
		moves++;
//		cout << "Move the top disk from " << S << " to " << D << endl;
	}
	else
	{
		move(n - 1, S, T, D);
		move(1, S, D, T);
		move(n - 1, T, D, S);
	}
}
/*
2 secconds for 25 disks
thus 1 seccond = 16777215.5 moves
100 disks requre (2^100) - 1 moves = 1.2676506 * 10 ^ 30 moves
(1.2676506 * 10 ^ 30) / 16777215.5 = 7.555786598 *10^22 seconds
The Big O for this program is O(2^n)
*/