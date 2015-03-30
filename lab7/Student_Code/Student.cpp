// Written by Aleks Christensen

#include "Student.h"

Student::Student(unsigned long long int IDin, string nameIn, string addressIn, string phoneIn)
 : ID(IDin), name(nameIn), address(addressIn), phone(phoneIn), GPA("E") {}

Student::~Student(){}

unsigned long long int Student::getID()
{
	return ID;
}

string Student::getName()
{
	return name;
}

string Student::getGPA()
{
	return GPA;
}

void Student::addGPA(double classGrade)
{
	double cur = stod(GPA);
	cur += classGrade;
	GPA = to_string(cur);
}

string Student::toString()
{
	ostringstream info;
	info << ID << endl << name << endl << address << endl << phone << endl << GPA;
	return info.str();
}