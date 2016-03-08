/*
Adam Novoa
CS 472
1/22/2015
*/

#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;
class League
{
public:
	class Team
	{
	private:
		int teamId;
		string teamName;
		string teamMascot;
		string Multiverse;
		int victories;
		int losses;
		int points;
	public:
		Team()
		{
			teamId = 0;
			teamName = "";
			teamMascot = "";
			Multiverse = "";
			victories = 0;
			losses = 0;
			points = 0;
		}
		void operator=(Team &T)
		{
			teamId = T.teamId;
			teamName = T.teamName;
			teamMascot = T.teamMascot;
			Multiverse = T.Multiverse;
			victories = T.victories;
			losses = T.losses;
			points = T.points;
			return;
		}
		bool operator==(Team &T)
		{
			if (victories == T.victories)
			{
				return true;
			}
			return false;
		}
		int getPoints()
		{
			points = victories;
			return points;
		}

		friend istream &operator>>(istream &input, Team &T)
		{
			char trash;
			input >> T.teamId;
			input >> trash;
			char k = ' ';
			k = input.peek();
			while (k != ',')
			{
				input.get(k);
				T.teamName += k;
				k = input.peek();
			}
			input >> trash;
			k = input.peek();
			while (k != ',')
			{
				input.get(k);
				T.teamMascot += k;
				k = input.peek();
			}
			input >> trash;
			k = input.peek();
			while (k != ',')
			{
				input.get(k);
				T.Multiverse += k;
				k = input.peek();
			}
			input >> trash;
			input >> T.victories;
			input >> trash;
			input >> T.losses;
			return input;
		}
		friend ostream &operator<<(ostream & output, Team &T)
		{
			output << T.teamId << "," << T.teamName << "," << T.teamMascot << "," << T.Multiverse << ", " << T.victories << ", " << T.losses <<", " << T.getPoints() <<  endl;
			return output;
		}
		bool operator>(Team &T)
		{
			if (getPoints() > T.getPoints())
			{
				return true;
			}
			return false;
		}
	};
private:
	ifstream infile;
	ofstream outfile;
	vector<Team> team;
public:
	League()
	{
		infile.open("Williams.Marlene.assn01.P2.txt");
		team.resize(9);
		for (int i = 0; i < 9; i++)
		{
			infile >> team[i];
		}
	}
	void write()
	{
		outfile.open("result.txt");
		for (int i = 0; i < 9; i++)
		{
			outfile << team[i];
		}
	}
	int getPoints(int index)
	{
		return team[index].getPoints();
	}
	void sort()
	{
		int i, j;
		Team temp;
		for (i = 0; i < team.size(); i++)
		{
			for (j = 0; j < team.size() - 1; j++)
			{
				if (team[j + 1] > team[j])
				{
					temp = team[j];
					team[j] = team[j + 1];
					team[j + 1] = temp;
				}
			}
		}
	}
	void top(int i)
	{
		
		if (i > 0 && i < team.size())
		{
			sort();
			for (int x = 0; x < i; x++)
			{
				cout << team[x];
			}
		}
		return;
	}
};
int main()
{
	League L;
	L.write();
	L.top(4);

	system("pause");
	return 0;
}

/*
Output for top 4 teams
164, Alabama, Elephants, Champions, 10, 0, 10
112, Pisgah, Eagles, RubberThumpers, 9, 1, 9
100, Fyffe, Devils, StarWarriors, 8, 2, 8
199, EastLimestone, Indians, Tuchanka, 7, 3, 7
Press any key to continue . . .
*/