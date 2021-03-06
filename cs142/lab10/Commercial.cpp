// Written by Aleks Christensen
#include "Commercial.h"

Commercial::Commercial(int propId, bool rented, double estValue, string addressIn,
 bool discounted, double taxRate) : Property(propId, rented, estValue, addressIn)
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
