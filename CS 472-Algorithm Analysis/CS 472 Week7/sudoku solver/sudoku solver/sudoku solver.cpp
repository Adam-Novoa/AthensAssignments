/*
Adam Novoa
CS 472
4/13/2015
*/

#include <iostream>
#include <fstream>

using namespace std;


class solver
{
private:
	const static int SIZE = 9;
	int puzzle[SIZE][SIZE];
	bool complete;

public:
	solver()
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				puzzle[i][j] = 0;
			}
		}
		complete = false;
	}

	void read(ifstream &infile)
	{
		char trash;
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				infile >> puzzle[i][j];
				infile >> trash;
			}
		}
		return;
	}

	void print(ofstream &outfile)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				cout << puzzle[i][j];
				cout << ',';
				outfile << puzzle[i][j];
				outfile << ',';
			}
			cout << endl;
			outfile << endl;
		}
		return;
	}

	void solve(int x, int y)
	{
		if (puzzle[y][x] == 0)
		{
			for (int val = 1; val <= 10 && complete == false; val++)
			{
				puzzle[y][x] = val;
				if (val < 10 && isValid())
				{
					if (x < SIZE - 1)
					{
						solve(x + 1, y);
					}
					else if (y < SIZE - 1)
					{
						solve(0, y + 1);
					}
					else
					{
						complete = true;
					}
				}
				if (val == 10)
				{
					puzzle[y][x] = 0;
				}
			}
			return;
		}
		if (complete == false)
		{
			if (x < SIZE - 1)
			{
				solve(x + 1, y);
			}
			else if (y < SIZE - 1)
			{
				solve(0, y + 1);
			}
				}
		return;
	}

	bool isValid()
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (puzzle[i][j] != 0)
				{
					int temp = puzzle[i][j];
					for (int h = j; h < SIZE; h++)
					{
						if (temp == puzzle[i][h] && h != j)
						{
							return false;
						}
					}
				}
			}
		}

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (puzzle[i][j] != 0)
				{
					int temp = puzzle[i][j];
					for (int h = 0; h < SIZE; h++)
					{
						if (temp == puzzle[h][j] && h != i)
						{
							return false;
						}
					}
				}
			}
		}
		
		
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (puzzle[i][j] == 2 && i == 1 && j == 0)
				{
					j = j;
				}
				if (puzzle[i][j] != 0)
				{
					int h;
					int k;
					if (i < 3)
					{
						h = 0;
					}
					else if (i < 6)
					{
						h = 3;
					}
					else if (i < 9)
					{
						h = 6;
					}
					if (j < 3)
					{
						k = 0;
					}
					else if (j < 6)
					{
						k = 3;
					}
					else if (j < 9)
					{
						k = 6;
					}
					
					int temp = puzzle[i][j];
					for (int y = 0; y < 3; y++)
					{
						for (int x = 0; x < 3; x++)
						{
							if (temp == puzzle[h + y][k + x] && (h + y != i || k + x != j))
							{
								return false;
							}
						}
					}
				}	
			}
		}
		return true;
	}

};

int main()
{
	solver s;
	ifstream infile;
	infile.open("puzzle.txt");
	s.read(infile);
	infile.close();

	s.solve(0,0);

	ofstream outfile;
	outfile.open("result.txt");
	if (s.isValid())
	s.print(outfile);
	outfile.close();

	system("pause");
	return 0;
}
/*
puzzle in puzzle.txt
4,0,0,0,2,5,1,0,7,
0,0,6,7,0,0,0,0,0,
0,0,5,0,0,0,0,9,0,
0,0,0,1,0,8,0,6,0,
0,0,7,0,0,0,0,2,0,
0,0,0,0,0,0,0,0,0,
1,0,0,2,0,9,3,0,0,
0,0,0,0,0,0,0,0,5,
0,3,4,0,0,1,0,0,0,

answer to test puzzle
4,8,9,6,2,5,1,3,7,
2,1,6,7,9,3,5,4,8,
3,7,5,8,1,4,6,9,2,
9,2,3,1,5,8,7,6,4,
5,4,7,9,3,6,8,2,1,
8,6,1,4,7,2,9,5,3,
1,5,8,2,4,9,3,7,6,
6,9,2,3,8,7,4,1,5,
7,3,4,5,6,1,2,8,9,
*/