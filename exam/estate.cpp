// Name: Aleks Christensen
// ID: 69-763-5482
// CS 142 Fall 2014 Final Exam

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Property.h"
#include "Residential.h"
#include "Commercial.h"

// namespace std is declared in Property.h, which then becomes inherited by everything else

// declaring location of string difference between property types
const int RES = 4;
const int COM = 5;
// declaring constant locations of data in token vectors
const int TYPE_LOC = 0;
const int RENTED_LOC = 1;
const int VALUE_LOC = 2;
const int VACANT_LOC = 3;
const int DISCOUNT_LOC = 3;
const int RATE_LOC = 4;
// declaring error codes
const int FINE = 0;
const int INV_FILE = -1;
const int EMPTY = -2;

void errorCheck(int err) // checks return value of function and displays error message
{
  switch (err) {
    case 0:
      break;
    case -1:
      cout << endl << "Could not open file!" << endl;
      break;
    case -2:
      cout << endl << "You have nothing!" << endl;
      break;
    default:
      cout << endl << "Generic error code!" << endl;
      break;
  }
}

void ignore(vector<string> tokens) // prints the bad property line
{
  cout << "Ignoring bad `" << tokens.at(TYPE_LOC) << "` in input file: ";
  for (size_t t = 0; t < tokens.size(); ++t) {
    cout << tokens.at(t) << " ";
  }
  cout << endl;
}

int print(vector<Property*> properties) // prints current inventory of properties along with their attributes
{
  size_t numProps = properties.size();
  if (numProps == 0) {
    return EMPTY; // Error code -4 will be empty vector
  }
  else {
    cout << endl;
    for (size_t curProp = 0; curProp < properties.size(); ++curProp) {
      cout << properties.at(curProp)->toString() << endl;
    }
    return FINE;
  }
}

int loadFile(vector<Property*>& properties) // loads file into vector
{
  string fileName;
  int start; // var to store where the address starts
  int id = 0; // property id, increments each time a new property is stored
  cout << "Please enter the location of a file with property data\n>";
  getline(cin, fileName);
  ifstream file(fileName); // open file
  if (file) { // if the file doesn't exist, none of this will happen
    for (string line; getline(file, line);) { // get one line at a time
      istringstream iss(line); // make a string stream out of the line
      vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}}; // break up the stringstream into words by spaces and put them into a vector
      if (tokens.at(TYPE_LOC) == "Residential") start = RES; // Address starts at location 4 for Residential locations
      else if (tokens.at(TYPE_LOC) == "Commercial") start = COM; // Start at 5 for Commercial locations
      else { ignore(tokens); continue; } // if the property type is unknown, ignore it and move on
      if (tokens.at(RENTED_LOC) != "1" && tokens.at(RENTED_LOC) != "0") { ignore(tokens); continue; } // if invalid data is at a location,
      if (tokens.at(VACANT_LOC) != "1" && tokens.at(VACANT_LOC) != "0") { ignore(tokens); continue; } // ignore the line and move on
      ostringstream address; // stores the property's address
      for (size_t i = start; i < tokens.size(); ++i) { // iterate through whatever's after the property data in the token vector
        if (i == tokens.size() - 1) { // and store it to the address stringstream
          address << tokens.at(i); // we don't want a trailing space
        }
        else {
          address << tokens.at(i) << " ";
        }
      }
      if (start == RES) { // if the property is residential
        try{
          Residential* place = new Residential(id, stoi(tokens.at(RENTED_LOC)), // make a new residential object pointer
            stoi(tokens.at(VALUE_LOC)), address.str(), stoi(tokens.at(VACANT_LOC)));
          properties.push_back(place); // and store it to the properties vector
        }
        catch (const invalid_argument& e) { ignore(tokens); continue; } // If anything is invalid, the whole thing will fail and be ignored
      }
      else { // if it's not residential, it'll be commercial
        try{
          Commercial* place = new Commercial(id, stoi(tokens.at(RENTED_LOC)), stoi(tokens.at(VALUE_LOC)), // make the object pointer
            address.str(), stoi(tokens.at(DISCOUNT_LOC)), stod(tokens.at(RATE_LOC)));
          properties.push_back(place); // and store it
        }
        catch (const invalid_argument& e) { ignore(tokens); continue; } // If anything is invalid, the whole thing will fail and be ignored
      }
      id++; // increment the property id
    }
    return FINE;
  }
  else { return INV_FILE; } // Error code -2 will be invalid file
}

void printReport(vector<Property*> properties)
{
  cout << endl << "NOW PRINTING TAX REPORT" << endl;
  for (size_t prop = 0; prop < properties.size(); ++prop) {
    cout << "** Taxes due for property at: " << properties.at(prop)->getAttr("addr") << endl;
    cout << "\tProperty ID:\t\t\t" << properties.at(prop)->getAttr("id") << endl;
    cout << "\tEstimated Value:\t\t$" << properties.at(prop)->getAttr("value") << endl;
    cout << "\tTaxes due:\t\t\t$" << properties.at(prop)->getTax() << endl;
  }
}

int main()
{
  vector<Property*> properties;

  // errorCheck(loadFile(properties));
  if (loadFile(properties) != FINE) {errorCheck(INV_FILE); system("pause"); return 0;}
  if (print(properties) != FINE) {errorCheck(EMPTY); system("pause"); return 0;}
  printReport(properties);
  system("pause");
  return 0;
}
