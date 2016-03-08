/*
Adam Novoa
CS 372
Recursive Tree
10/26/2014
*/


#include <iostream>
using namespace std;

void print(char begin, char end, int depth);
void line(char start, char stop);
void spaces(int n);

int main()
{
	print('A', 'a', 0);


	system("pause");
	return 0;
}

void print(char begin, char end, int depth)
{
	if (begin > end)
		return;
	print(begin, end - 1, depth + 1);
	spaces(depth);
	line(begin, end);
	cout << endl;
	
	
	return;
}

void line(char start, char stop)
{
	if (start == stop)
	{
		cout << start;
		return;
	}
	cout << start;
	line(start + 1, stop);
	cout << start;
}

void spaces(int n)
{
	if (n == 0)
	{
		return;
	}
	else
	{
		cout << " ";
		spaces(n - 1);
	}
	return;
}
/*
Output
                                A
                               ABA
                              ABCBA
                             ABCDCBA
                            ABCDEDCBA
                           ABCDEFEDCBA
                          ABCDEFGFEDCBA
                         ABCDEFGHGFEDCBA
                        ABCDEFGHIHGFEDCBA
                       ABCDEFGHIJIHGFEDCBA
                      ABCDEFGHIJKJIHGFEDCBA
                     ABCDEFGHIJKLKJIHGFEDCBA
                    ABCDEFGHIJKLMLKJIHGFEDCBA
                   ABCDEFGHIJKLMNMLKJIHGFEDCBA
                  ABCDEFGHIJKLMNONMLKJIHGFEDCBA
                 ABCDEFGHIJKLMNOPONMLKJIHGFEDCBA
                ABCDEFGHIJKLMNOPQPONMLKJIHGFEDCBA
               ABCDEFGHIJKLMNOPQRQPONMLKJIHGFEDCBA
              ABCDEFGHIJKLMNOPQRSRQPONMLKJIHGFEDCBA
             ABCDEFGHIJKLMNOPQRSTSRQPONMLKJIHGFEDCBA
            ABCDEFGHIJKLMNOPQRSTUTSRQPONMLKJIHGFEDCBA
           ABCDEFGHIJKLMNOPQRSTUVUTSRQPONMLKJIHGFEDCBA
          ABCDEFGHIJKLMNOPQRSTUVWVUTSRQPONMLKJIHGFEDCBA
         ABCDEFGHIJKLMNOPQRSTUVWXWVUTSRQPONMLKJIHGFEDCBA
        ABCDEFGHIJKLMNOPQRSTUVWXYXWVUTSRQPONMLKJIHGFEDCBA
       ABCDEFGHIJKLMNOPQRSTUVWXYZYXWVUTSRQPONMLKJIHGFEDCBA
      ABCDEFGHIJKLMNOPQRSTUVWXYZ[ZYXWVUTSRQPONMLKJIHGFEDCBA
     ABCDEFGHIJKLMNOPQRSTUVWXYZ[\[ZYXWVUTSRQPONMLKJIHGFEDCBA
    ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]\[ZYXWVUTSRQPONMLKJIHGFEDCBA
   ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA
  ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA
 ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA
ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`a`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA
Press any key to continue . . .*/