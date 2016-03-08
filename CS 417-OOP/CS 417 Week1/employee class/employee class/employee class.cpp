/*
Adam Novoa
CS 472
1/22/2015
*/

#include<iostream>
#include<string>

using namespace std;

class employee
{
private:
	string name;
	int idNumber;
	string department;
	string position;
public:
	employee(string n, int id, string dep, string pos)
	{
		name = n;
		idNumber = id;
		department = dep;
		position = pos;
	}
	employee(string n, int id)
	{
		name = n;
		idNumber = id;
		department = "";
		position = "";
	}
	employee()
	{
		name = "";
		idNumber = 0;
		department = "";
		position = "";
	}
	void setName(string n)
	{
		name = n;
		return;
	}
	void setIdNumber(int id)
	{
		idNumber = id;
		return;
	}
	void setDepartment(string dep)
	{
		department = dep;
		return;
	}
	void setPosition(string pos)
	{
		position = pos;
		return;
	}

	string getName()
	{
		return name;
	}
	int getIdNumber()
	{
		return idNumber;
	}
	string getDepartment()
	{
		return department;
	}
	string getPosition()
	{
		return position;
	}
};


int main()
{
	employee temp("name1", 1, "dep", "pos");
	employee temp2("name2", 2);
	employee temp3;

	cout << "Employee name: " << temp.getName() << " Id#: " << temp.getIdNumber() 
		<< " Department: " << temp.getDepartment() << " Position: " << temp.getPosition() << endl;
	cout << "Employee name: " << temp2.getName() << " Id#: " << temp2.getIdNumber()
		<< " Department: " << temp2.getDepartment() << " Position: " << temp2.getPosition() << endl;
	cout << "Employee name: " << temp3.getName() << " Id#: " << temp3.getIdNumber()
		<< " Department: " << temp3.getDepartment() << " Position: " << temp3.getPosition() << endl;

	temp3.setName("New Name");
	temp3.setIdNumber(5);
	temp3.setDepartment("New Department");
	temp3.setPosition("New Position");

	cout << "Employee name: " << temp3.getName() << " Id#: " << temp3.getIdNumber()
		<< " Department: " << temp3.getDepartment() << " Position: " << temp3.getPosition() << endl;
	system("pause");
	return 0;
}
/*
Output
Employee name: name1 Id#: 1 Department: dep Position: pos
Employee name: name2 Id#: 2 Department:  Position:
Employee name:  Id#: 0 Department:  Position:
Employee name: New Name Id#: 5 Department: New Department Position: New Position

Press any key to continue . . .
*/