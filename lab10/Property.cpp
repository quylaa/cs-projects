// Written by Aleks Christensen
#include "Property.h"

using namespace std;

Property::Property(int propId, bool rented, double estValue, string addressIn)
{
  id = propId;
  rental = rented;
  value = estValue;
  address = addressIn;
}
Property::~Property(){};

string Property::toString() const
{
  ostringstream info;
  info << "Property ID: " << id << "\tAddress: " << address << "\t\t";
  rental ? (info << "Rental\t\t") : (info << "Not Rental\t\t");
  info << "Estimated Value: " << value << "\t\t";
  return info.str();
}
