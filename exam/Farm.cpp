// Name: Aleks Christensen
// ID: 69-763-5482
// CS 142 Fall 2014 Final Exam
#include "Farm.h"

Farm::Farm(int propId, bool rented, double estValue, int payed, string addressIn) : Property(propId, rented, estValue, payed, addressIn)
{
  discount = true;
  rate = 0.40;
}
Farm::~Farm(){};

string Farm::toString() const
{
  string info = Property::toString();
  stringstream out;
  out << info;
  discount ? (out << "Discounted\tDiscount: " << (rate * 100)) << "%" : (out << "Not Discounted");
  out << "\tNOTE: Farm property";
  return out.str();
}

double Farm::getTax()
{
  double tax, disRate;
  rental ? tax = 0.012 : tax = 0.01;
  discount ? disRate = rate : disRate = 0.0;
  return (value * tax) - ((value * tax) * disRate);
}

int Farm::getDays()
{
  return 100;
}
