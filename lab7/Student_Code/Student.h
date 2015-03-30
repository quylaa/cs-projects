// Written by Aleks Christensen

#ifndef STUDENT_H_
#define STUDENT_H_

#include "StudentInterface.h"
#include <sstream>

class Student : public StudentInterface
{
	private:
		// Student ID
		unsigned long long int ID;
		// student name
		string name;
		// student address
		string address;
		// studen phone number
		string phone;
		// current GPA
		string GPA;
		
	public:
		Student(unsigned long long int IDin, string nameIn, string addressIn, string phoneIn);
		~Student();

		/*
		 * Returns student ID
		 */
		unsigned long long int getID();

		/*
		 * Returns student name
		 */
		string getName();

		/*
		 * Returns student's GPA
		 */
		string getGPA();

		/*
		 * Add's given course grade to current GPA
		 */
		void addGPA(double classGrade);

		/* The student object will be put into string representation. Student info will be
		 * ordered ID, name, address, phone number, and GPA. Each piece of information will
		 * be on its own line. GPA will not have a newline following it and the precision 
		 * of the GPA will be rounded to two decimal places. For example,
		 * 
		 * 123456789
		 * Ben Thompson
		 * 17 Russell St, Provo, UT 84606
		 * 555-555-5555
		 * 3.12
		 * 
		 * Returns this as string with no trailing line
		 */
		string toString();
};

struct Compare
{
	bool operator()(Student* student1, Student* student2)
	{
		return student1->getName() < student2->getName();
	}
};


#endif