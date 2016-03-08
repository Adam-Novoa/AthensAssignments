/*
Adam Novoa
CS 372
Throttle Class Overload
9/8/2014
*/

#include<iostream>

using namespace std;

class throttle
{
private:
	int position;
	int Top_Position;

public:
	throttle(int top = 6, int pos = 0)
	{
		if (pos >= 0)
		{
			position = pos;
		}
		else
		{
			position = 0;
		}
		if (top > 0)
		{
			Top_Position = top;
		}
		else
		{
			Top_Position = 0;
		}

	}
	throttle(throttle& temp)
	{
		position = temp.getPos();
		Top_Position = temp.getTop();
	}

	void shut_off()
	{
		position = 0;
	}
	void shift(int amount)
	{
		if (getPos() + amount >= 0 && getPos() + amount <= getTop())
		{
			position += amount;
		}
		else if (getPos() + amount < 0)
		{
			position = 0;
		}
		else if (getPos() + amount > getTop())
		{
			position = getTop();
		}
	}
	double flow()
	{
		return (double)getPos() / getTop();
	}
	bool is_on()
	{
		return getPos();
	}



	int getPos()
	{
		return position;
	}
	int getTop()
	{
		return Top_Position;
	}

	bool operator==(throttle& temp)
	{
		return
			(position == temp.getPos())
			&&
			(Top_Position == temp.getTop());		
	}

	friend bool operator!=(throttle& temp1, throttle& temp2);
	friend ostream& operator<<(ostream& out, throttle& temp);
};

int main()
{
	throttle car;
	throttle truck(30);
	throttle shuttle(20, 6);
	throttle mythrottle = truck;

	if (car.operator==(truck))
	{
		cout << "Car = Truck" << endl;
	}
	
	if (truck == mythrottle)
	{
		cout << "Truck = mythrottle" << endl;
	}

	if (operator!=(car,truck))
	{
		cout << "Car != Truck" << endl;
	}

	if (truck != mythrottle)
	{
		cout << "Truck != mythrottle" << endl;
	}

	cout << "\nShuttle " << endl << shuttle;

	system("pause");
	return 0;
}

bool operator!=(throttle& temp1, throttle& temp2)
{
	return !(temp1 == temp2);
}

ostream& operator<<(ostream& out, throttle& temp)
{
	out << "Top Position = " << temp.getTop() << endl;
	out << "Current Position = " << temp.getPos() << endl;
	return out;
}
/*
Output

Truck = mythrottle
Car != Truck

Shuttle
Top Position = 20
Current Position = 6
Press any key to continue . . .
*/