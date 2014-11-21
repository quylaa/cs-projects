// Written by Aleks Christensen
#include "Residential.h"

using namespace std;

Residential::Residential(int propId, bool rented, double estValue, string addressIn,
 bool vacancy) : Property(propId, rented, estValue, addressIn)
{
  vacant = vacancy;
}
Residential::~Residential(){};

string Residential::toString() const
{
  string info = Property::toString();
  stringstream out;
  out << info;
  vacant ? (out << "Vacant") : (out << "Occupied");
  return out.str();
}
