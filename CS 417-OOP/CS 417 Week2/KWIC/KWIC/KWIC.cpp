/*
02/05/2015
Adam Novoa
CS 417
Key Word In Context
*/

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;

string articles[3] = { "the", "a", "an"};

struct word
{
	string W;
	int count;
};

class KWIC
{
private:
	vector<word> text;
	bool noArticle;
	bool frequency;
public:
	KWIC()
	{
		noArticle = false;
		frequency = false;
		begin();
	}
	KWIC(string commands)
	{
		noArticle = false;
		frequency = false;
		string tempCom = "";
		for (int i = 0; i < commands.length(); i++)// change to read entire command before checking if valid
		{
			tempCom += commands[i];
			if (tempCom == "-na")
			{
				noArticle = true;
				tempCom = "";
			}
			else if (tempCom == "-f")
			{
				frequency = true;
				tempCom = "";
			}
			if (commands[i + 1] == ' ')
			{
				i++;
			}
		}
		begin();
	}
	void begin()
	{
		const int size = 1000;
		char words[size];
		string temp = "";
		cout << "Please enter the text to read." << endl;
		cin.getline(words, size - 1);
		int index = 0;
		while (words[index] != '\0')
		{
			while (isalpha(words[index]))
			{
				temp += tolower(words[index]);
				index++;
			}
			if (temp.length() > 0)
			{
				add(temp);
				temp = "";
			}
			else//words[index] is ' ' or '\n'
			{
				index++;
			}
		}
		if (frequency == true)
		{
			fequencyT();
		}
		else
		{
			context();
		}
	}
	void add(string temp)
	{
		bool isNew = true;
		word t;
		t.W = temp;
		t.count = 0;
		
		for (int i = 0; i < text.size(); i++)
		{
			if (temp == text[i].W)
			{
				isNew = false;
				text[i].count++;
			}
		}
		if (isNew)
		{
			t.count = 1;
			text.push_back(t);
		}
		else
		{
			text.push_back(t);
		}
		return;
	}
	void fequencyT()
	{
		if (noArticle == false)
		{
			for (int i = 0; i < text.size(); i++)
			{
				if (text[i].count > 0)
				{
					cout << left << setw(15) << text[i].W << text[i].count << endl;
				}
			}
		}
		else
		{
			for (int i = 0; i < text.size(); i++)
			{
				if (text[i].count > 0 && text[i].W != articles[0] && text[i].W != articles[1] && text[i].W != articles[2])
				{
					cout << left << setw(15) << text[i].W << text[i].count << endl;
				}
			}
		}
		return;
	}

	void context()
	{
		cout << left << "Word           Context" << endl;
		if (noArticle == false)
		{
			for (int i = 0; i < text.size(); i++)
			{
				cout << setw(15) << text[i].W;
				for (int j = -3; j < 4; j++)
				{
					if (i + j<text.size() && i + j >= 0)
					cout << text[i + j].W << " ";
				}
				cout << endl;
			}
		}
		else
		{
			for (int i = 0; i < text.size(); i++)
			{
				if (text[i].W != articles[0] && text[i].W != articles[1] && text[i].W != articles[2])
				{
					cout << setw(15) << text[i].W;
					for (int j = -3; j < 4; j++)
					{
						if (i + j < text.size() && i + j >= 0)
							cout << text[i + j].W << " ";
					}
					cout << endl;
				}
			}
		}
	}
};


int main()
{
	char temp[20];
	string com = "";
	cout << "Please enter -na to skip articles." << endl;
	cout << "Enter -f for a fequency table." << endl;
	cout << "Or enter nothing for a plain KWIC" << endl;
	cin.getline(temp, 19, '\n');
	int i = 0;
	while (temp[i] != '\0')
	{
		com += temp[i];
		i++;
	}
	
	KWIC list(com);

	system("pause");
	return 0;
}
/*
Output

Please enter -na to skip articles.
Enter -f for a fequency table.
Or enter nothing for a plain KWIC
-f -na
Please enter the text to read.
The quick brown fox jumps over the lazy dog. The quick fox
quick          2
brown          1
fox            2
jumps          1
over           1
lazy           1
dog            1
Press any key to continue . . .

Please enter -na to skip articles.
Enter -f for a fequency table.
Or enter nothing for a plain KWIC
-f
Please enter the text to read.
The quick brown fox jumps over the lazy dog. The quick fox
the            3
quick          2
brown          1
fox            2
jumps          1
over           1
the            1
lazy           1
dog            1
Press any key to continue . . .

Please enter -na to skip articles.
Enter -f for a fequency table.
Or enter nothing for a plain KWIC
-na
Please enter the text to read.
The quick brown fox jumps over the lazy dog.
Word           Context
quick          the quick brown fox jumps
brown          the quick brown fox jumps over
fox            the quick brown fox jumps over the
jumps          quick brown fox jumps over the lazy
over           brown fox jumps over the lazy dog
lazy           jumps over the lazy dog
dog            over the lazy dog
Press any key to continue . . .

Please enter -na to skip articles.
Enter -f for a fequency table.
Or enter nothing for a plain KWIC

Please enter the text to read.
The quick brown fox jumps over the lazy dog.
Word           Context
the            the quick brown fox
quick          the quick brown fox jumps
brown          the quick brown fox jumps over
fox            the quick brown fox jumps over the
jumps          quick brown fox jumps over the lazy
over           brown fox jumps over the lazy dog
the            fox jumps over the lazy dog
lazy           jumps over the lazy dog
dog            over the lazy dog
Press any key to continue . . .
*/