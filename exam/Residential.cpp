// Name: Aleks Christensen
// ID: 69-763-5482
// CS 142 Fall 2014 Final Exam
#include "Residential.h"

Residential::Residential(int propId, bool rented, double estValue, int payed, string addressIn,
 bool occupied) : Property(propId, rented, estValue, payed, addressIn)
{
  vacancy = occupied;
}
Residential::~Residential(){};

string Residential::toString() const
{
  string info = Property::toString();
  stringstream out;
  out << info;
  vacancy ? (out << "Occupied") : (out << "Vacant");
  return out.str();
}

double Residential::getTax()
{
  double tax;
  vacancy ? tax = 0.006 : tax = 0.009;
  return (value * tax);
}

int Residential::getDays()
{
  double taxDue = Residential::getTax();
  int days;
  (taxDue > 1000000) ? days = 60 : days = 90;
  return days;
}
