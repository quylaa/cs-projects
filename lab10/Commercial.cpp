// Written by Aleks Christensen
#include "Commercial.h"

using namespace std;

Commercial::Commercial(int propId, bool rented, double estValue, string addressIn,
 bool discounted, double taxRate) : Property(propId, rented, estValue, addressIn)
{
  discount = discounted;
  rate = taxRate;
}
Commercial::~Commercial(){};

string Commercial::toString() const
{
  stringstream info(Property::toString());
  discount ? (info << "Discounted\tDiscount: " << (rate * 100)) : (info << "Not Discounted");
  return info.str();
}
