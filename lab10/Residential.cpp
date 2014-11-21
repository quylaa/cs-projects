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
  stringstream info(Property::toString());
  vacant ? (info << "Vacant") : (info << "Occupied");
  return info.str();
}
