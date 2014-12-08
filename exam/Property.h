// Name: Aleks Christensen
// ID: 69-763-5482
// CS 142 Fall 2014 Final Exam
#pragma once

#include <string>
#include <sstream>
#include <iostream>


using namespace std;

class Property
{
  protected:
    int id;
    string address;
    bool rental;
    int since;
    double value;

  public:
    /* Constructor of Property class
     * addressIn will be stored to address
     */
    Property(int propId, bool rented, double estValue, int payed, string addressIn);
    virtual ~Property();
    // ----------------------------------------------------
    // getAttr() - get specific attribute
    string getAttr(string opt);
    // toString() - returns a string of the attributes
    virtual string toString() const;
    // getTax() - returns the taxed amount due on the property
    virtual double getTax() = 0;
    // getDays() - returns number of days until the taxes on the property are due
    virtual int getDays() = 0;
  };
