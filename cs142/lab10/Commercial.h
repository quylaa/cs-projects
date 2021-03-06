// Written by Aleks Christensen
#pragma once

#include "Property.h"

class Commercial : public Property
{
  protected:
    bool discount;
    double rate;

  public:
    // Constructor
    Commercial(int propId, bool rented, double estValue, string addressIn,
      bool discounted, double taxRate);
    virtual ~Commercial();
    // ----------------------------------------------------
    // toString() - returns string of attributes
    string toString() const;
    // getTax() - returns the taxed amount due on the property
    double getTax();
};
