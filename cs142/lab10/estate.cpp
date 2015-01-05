// Written by Aleks Christenen

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

using namespace std;

const int RES = 4;
const int COM = 5;
const int TYPE_LOC = 0;
const int RENTED_LOC = 1;
const int VALUE_LOC = 2;
const int VACANT_LOC = 3;
const int DISCOUNT_LOC = 3;
const int RATE_LOC = 4;

void errorCheck(int err)
{
  switch (err) {
    case 0:
      break;
    case -2:
      cout << endl << "Could not open file!" << endl;
      break;
    case -3:
      cout << "Invalid property attribute format!" << endl;
      break;
    case -4:
      cout << endl << "You have nothing!" << endl;
      break;
    default:
      cout << endl << "Generic error code!" << endl;
      break;
  }
}

void ignore(vector<string> tokens)
{
  cout << "Ignoring bad `" << tokens.at(TYPE_LOC) << "` in input file: ";
  for (size_t t = 0; t < tokens.size(); ++t) {
    cout << tokens.at(t) << " ";
  }
  cout << endl;
}

int print(vector<Property*> properties)
{
  size_t numProps = properties.size();
  if (numProps == 0) {
    return -4; // Error code -4 will be empty vector
  }
  else {
    cout << endl;
    for (size_t curProp = 0; curProp < properties.size(); ++curProp) {
      cout << properties.at(curProp)->toString() << endl;
    }
    return 0;
  }
}

int loadFile(vector<Property*>& properties)
{
  string fileName;
  int start;
  int id = 0;
  cout << "Please enter the location of a file with property data\n>";
  getline(cin, fileName);
  ifstream file(fileName);
  if (file) {
    for (string line; getline(file, line);) {
      istringstream iss(line);
      vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
      if (tokens.at(TYPE_LOC) == "Residential") start = RES; // Address starts at location 4 for Residential locations
      else if (tokens.at(TYPE_LOC) == "Commercial") start = COM; // Start at 5 for Commercial locations
      else { ignore(tokens); continue; }
      if (tokens.at(RENTED_LOC) != "1" && tokens.at(RENTED_LOC) != "0") { ignore(tokens); continue; }
      if (tokens.at(VACANT_LOC) != "1" && tokens.at(VACANT_LOC) != "0") { ignore(tokens); continue; }
      ostringstream address;
      for (size_t i = start; i < tokens.size(); ++i) {
        if (i == tokens.size() - 1) {
          address << tokens.at(i);
        }
        else {
          address << tokens.at(i) << " ";
        }
      }
      if (start == RES) {
        try{
          Residential* place = new Residential(id, stoi(tokens.at(RENTED_LOC)),
            stoi(tokens.at(VALUE_LOC)), address.str(), stoi(tokens.at(VACANT_LOC)));
          properties.push_back(place);
        }
        catch (const invalid_argument& e) { ignore(tokens); continue; } // If anything is invalid, the whole thing will fail and be ignored
      }
      else {
        try{
          Commercial* place = new Commercial(id, stoi(tokens.at(RENTED_LOC)), stoi(tokens.at(VALUE_LOC)),
            address.str(), stoi(tokens.at(DISCOUNT_LOC)), stod(tokens.at(RATE_LOC)));
          properties.push_back(place);
        }
        catch (const invalid_argument& e) { ignore(tokens); continue; }
      }
      id++;
    }
    return 0;
  }
  else { return -2; } // Error code -2 will be invalid file
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

  errorCheck(loadFile(properties));
  errorCheck(print(properties));
  printReport(properties);
  system("pause");
  return 0;
}
