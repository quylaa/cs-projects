// Written by Aleks Christensen
#include "Residential.h"

Residential::Residential(int propId, bool rented, double estValue, string addressIn,
 bool occupied) : Property(propId, rented, estValue, addressIn)
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
