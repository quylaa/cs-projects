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
  string info = Property::toString();
  stringstream out;
  out << info;
  discount ? (out << "Discounted\tDiscount: " << (rate * 100)) << "%" : (out << "Not Discounted");
  return out.str();
}
