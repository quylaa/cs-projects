// Written by Aleks Christensen

#include "Student.h"

Student::Student(unsigned long long int IDin, string nameIn, string addressIn, string phoneIn)
 : ID(IDin), name(nameIn), address(addressIn), phone(phoneIn), GPA(0.00) {}

Student::~Student(){}

void Student::recalc()
{
  double avg = 0.0;
  for (double grade : classes) {
    avg += grade;
  }
  avg = avg / classes.size();
  GPA = avg;
}

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
  /*if (GPA == 4.0) return "A";
  else if (GPA < 4.0 && GPA >= 3.7) return "A-";
  else if (GPA < 3.7 && GPA >= 3.4) return "B+";
  else if (GPA < 3.4 && GPA >= 3.0) return "B";
  else if (GPA < 3.0 && GPA >= 2.7) return "B-";
  else if (GPA < 2.7 && GPA >= 2.4) return "C+";
  else if (GPA < 2.4 && GPA >= 2.0) return "C";
  else if (GPA < 2.0 && GPA >= 1.7) return "C-";
  else if (GPA < 1.7 && GPA >= 1.4) return "D+";
  else if (GPA < 1.4 && GPA >= 1.0) return "D";
  else if (GPA < 1.0 && GPA >= 0.7) return "D-";
  else if (GPA < 0.7 && GPA >= 0.0) return "E";*/
  stringstream g;
  g << fixed << setprecision(2) << GPA;
  return g.str();
}

void Student::addGPA(double classGrade)
{
  classes.push_back(classGrade);
  recalc();
}

string Student::toString()
{
  ostringstream info;
  //info.precision(3);
  info << ID << endl << name << endl << address << endl << phone << endl;
  if (GPA == 0) info << "0.00";
  else info << fixed << setprecision(2) << GPA;
  return info.str();
}
