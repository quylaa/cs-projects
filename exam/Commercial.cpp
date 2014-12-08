// Name: Aleks Christensen
// ID: 69-763-5482
// CS 142 Fall 2014 Final Exam
#include "Commercial.h"

Commercial::Commercial(int propId, bool rented, double estValue, int payed, string addressIn,
 bool discounted, double taxRate) : Property(propId, rented, estValue, payed, addressIn)
{
  discount = discounted;
  rate = taxRate;
}
Commercial::~Commercial(){};

string Commercial::toString() const
{
  string info = Property::toString();
  stringstream out;
  out << info;
  discount ? (out << "Discounted\tDiscount: " << (rate * 100)) << "%" : (out << "Not Discounted");
  return out.str();
}

double Commercial::getTax()
{
  double tax, disRate;
  rental ? tax = 0.012 : tax = 0.01;
  discount ? disRate = rate : disRate = 0.0;
  return (value * tax) - ((value * tax) * disRate);
}

int Commercial::getDays()
{
  double taxDue = Commercial::getTax();
  int days;
  (taxDue > 1000000) ? days = 60 : days = 90;
  return days;
}
