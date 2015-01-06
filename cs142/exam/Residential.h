// Name: Aleks Christensen
// ID: 69-763-5482
// CS 142 Fall 2014 Final Exam
#pragma once

#include "Property.h"

class Residential : public Property
{
  protected:
    bool vacancy;

  public:
    // Constructor
    Residential(int propId, bool rented, double estValue, int payed, string addressIn, bool occupied);
    virtual ~Residential();
    // ----------------------------------------------------
    // toString() - returns string of attributes
    string toString() const;
    // getTax() - returns the taxed amount due on the property
    double getTax();
    // getDays() - returns number of days until the taxes on the property are due
    int getDays();
};
