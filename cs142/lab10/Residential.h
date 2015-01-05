// Written by Aleks Christensen
#pragma once

#include "Property.h"

class Residential : public Property
{
  protected:
    bool vacancy;

  public:
    // Constructor
    Residential(int propId, bool rented, double estValue, string addressIn, bool occupied);
    virtual ~Residential();
    // ----------------------------------------------------
    // toString() - returns string of attributes
    virtual string toString() const;
    // getTax() - returns the taxed amount due on the property
    virtual double getTax();
};
