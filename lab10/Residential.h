// Written by Aleks Christensen
#pragma once

#include "Property.h"

class Residential : public Property
{
  protected:
    bool vacant;

  public:
    // Constructor
    Residential(int propId, bool rented, double estValue, string addressIn, bool vacancy);
    virtual ~Residential();
    // ----------------------------------------------------
    // toString() - returns string of attributes
    string toString() const;
};