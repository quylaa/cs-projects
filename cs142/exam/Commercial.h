// Name: Aleks Christensen
// ID: 69-763-5482
// CS 142 Fall 2014 Final Exam
#pragma once

#include "Property.h"

class Commercial : public Property
{
  protected:
    bool discount;
    double rate;

  public:
    // Constructor
    Commercial(int propId, bool rented, double estValue, int payed, string addressIn,
      bool discounted, double taxRate);
    virtual ~Commercial();
    // ----------------------------------------------------
    // toString() - returns string of attributes
    string toString() const;
    // getTax() - returns the taxed amount due on the property
    double getTax();
    // getDays() - returns number of days until the taxes on the property are due
    int getDays();
};
