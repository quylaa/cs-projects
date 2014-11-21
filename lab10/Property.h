// Written by Aleks Christensen
#pragma once

#include <string>
#include <sstream>
#include <iostream>


using namespace std;

class Property
{
  private:
    int id;
    string address;
    bool rental;
    double value;

  public:
    /* Constructor of Property class
     * addressIn will be stored to address
     */
    Property(int propId, bool rented, double estValue, string addressIn);
    virtual ~Property();
    // ----------------------------------------------------
    // toString() - returns a string of the attributes
    virtual string toString() const;
};
