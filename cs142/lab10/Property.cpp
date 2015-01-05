// Written by Aleks Christensen
#include "Property.h"

Property::Property(int propId, bool rented, double estValue, string addressIn)
{
  id = propId;
  rental = rented;
  value = estValue;
  address = addressIn;
}
Property::~Property(){};

string Property::getAttr(string opt)
{
  stringstream attr;
  if (opt == "addr") attr << address;
  if (opt == "rental") { if (rental) { attr << "true"; } else { attr << "false"; } }
  if (opt == "value") attr << value;
  if (opt == "id") attr << id;
  return attr.str();
}

string Property::toString() const
{
  ostringstream info;
  info << "Property ID: " << id << "\tAddress: " << address << "\t\t";
  rental ? (info << "Rental\t\t") : (info << "Not Rental\t\t");
  info << "Estimated Value: " << value << "\t\t";
  return info.str();
}
