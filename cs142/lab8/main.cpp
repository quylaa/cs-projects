// Written by Aleks Christensen

// Test Cases
//
// Case 1
// Input: 1
// Output: ~~ You have no cars in your inventory ~~
//
// Case 2
// Input: 3, Ford, 8525.99, Green
// Output: ~~ Car Bought ~~
//
// Case 3
// Input: 6, cars1.txt
// Output: ~~ File successfully loaded ~~


#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <memory>
#include "Car.h"

using namespace std;

const int NAME_LOC = 0;
const int COLOR_LOC = 1;
const int PRICE_LOC = 2;
const int FILE_BAL = 0;
const int FILE_NAME = 0;
const int FILE_COLOR = 1;
const int FILE_PRICE = 2;

int getInt(const int defaultValue = -1)
{
  string input;
  cin >> input;
  stringstream stream(input);
  int result = defaultValue;
  if (stream >> result) return result;
  else return result;
}

int showInv(vector<Car*>& cars)
{
  size_t numCars = cars.size();
  if (numCars == 0) {
    cout << endl << "~~ You have no cars in your inventory ~~" << endl;
    return 0;
  } else {
    cout << endl << "-------------------------------" << endl;
    for (size_t curCar = 0; curCar < cars.size(); ++curCar) {
      Car car = (*cars.at(curCar));
      cout << car.toString();
      cout << "-------------------------------" << endl;
    }
    return 0;
  }
}

int buyCar(double& balance, vector<Car*>& cars)
{

  string carName;
  string color;
  double price;

  cout << endl << "Please enter the name of the car to buy: ";
  cin >> carName;
  vector<Car*>::iterator carList;
  for(carList = cars.begin(); carList != cars.end(); ++carList) {
    if (carName == (*carList)->getName()) {
      cout << endl << "!! Car already in inventory !!" << endl;
      return -1;
    }
  }

  cout << "Now enter the price of the car you want to buy: $";
  cin >> price;
  if (price > balance) {
    cout << endl << "!! You do not have enough money to buy this car !!" << endl;
    return -1;
  }

  cout << "And now the color of the car: ";
  cin >> color;

  balance -= price;
  Car* newCar = new Car(carName, color, price);
  cars.push_back(newCar);
  cout << endl << "~~ Car bought ~~" << endl;
  return 0;
}

int sellCar(double& balance, vector<Car*>& cars)
{
  string carName;

  cout << endl << "Please enter the name of the car you wish to sell: ";
  cin >> carName;
  vector<Car*>::iterator carList;
  for (carList = cars.begin(); carList != cars.end(); ++carList) {
    if ((*carList)->getName() == carName) {
      balance += (*carList)->getPrice();
      delete * carList;
      carList = cars.erase(carList);
      cout << endl << "~~ Car sold ~~" << endl;
      return 0;
    }
  }
  cout << endl << "!! Car not in inventory !!" << endl;
  return -1;
}

int paintCar(vector<Car*>& cars)
{
  string newColor;
  string carName;
  cout << endl << "Please enter the name of the car you wish to paint: ";
  cin >> carName;
  vector<Car*>::iterator carList;
  for(carList = cars.begin(); carList != cars.end(); ++carList) {
    if ((*carList)->getName() == carName) {
      cout << "Now enter the color you wish to paint the car: ";
      cin >> newColor;
      (*carList)->paint(newColor);
      cout << endl << "~~ Painted " << carName << " " << newColor << " ~~" << endl;
      return 0;
    }
  }
  cout << endl << "!! Car not in inventory !!" << endl;
  return -1;
}

int loadFile(double& balance, vector<Car*>& cars)
{
  cin.ignore();
  string filename;
  vector<string> lines;
  cout << endl << "Please enter the full filename of the file you wish to load [example.txt]: ";
  getline(cin, filename);
  ifstream file(filename);
  if (file) {
    for (string line; getline(file, line);) {
      lines.push_back(line);
    }
    balance += stod(lines.at(FILE_BAL));
    for (size_t carLines = 1; carLines < lines.size(); ++carLines) {
      istringstream iss(lines.at(carLines));
      vector<string> aspects{ istream_iterator < string > {iss}, istream_iterator < string > {} };
      Car* newCar = new Car(aspects.at(FILE_NAME), aspects.at(FILE_COLOR), stod(aspects.at(FILE_PRICE)));
      cars.push_back(newCar);
    }
    cout << endl << "~~ File successfully loaded ~~" << endl;
    file.close();
    return 0;
  } else {
    cout << endl << "!! Could not open file. Try entering the full file path. !!" << endl;
    return -1;
  }
}

int saveFile(double balance, vector<Car*> cars)
{
  cin.ignore();
  string filename;
  cout << endl << "Please enter the name of the file you wish to save as [example.txt]: ";
  getline(cin, filename);
  ofstream file(filename);
  if(file) {
    file << balance << endl;
    vector<Car*>::iterator carList;
    for (carList = cars.begin(); carList != cars.end(); ++carList) {
      stringstream aspects;
      aspects << (*carList)->getName() << " " << (*carList)->getColor() << " " << (*carList)->getPrice();
      file << aspects.str() << endl;
    }
    file.close();
    cout << endl << "~~ File successfully saved ~~" << endl;
    return 0;
  } else {
    cout << endl << "!! File cannot be saved !!" << endl;
    return -1;
  }
}

int menu(int opt, double& balance, vector<Car*>& cars)
{
  switch (opt) {
    case 1: // Show inventory
      showInv(cars);
      break;
    case 2: // Show balance
      cout << endl << "~~ Current balance is $" << setprecision(10) << balance << " ~~" << endl;
      break;
    case 3: // Buy car
      buyCar(balance, cars);
      break;
    case 4: // Sell car
      sellCar(balance, cars);
      break;
    case 5: // Paint car
      paintCar(cars);
      break;
    case 6: // Load file
      loadFile(balance, cars);
      break;
    case 7: // Save file
      saveFile(balance, cars);
      break;
    case 8: // Quit
      break;
    default:
      cout << endl << "!! Invalid menu option !!" << endl;
      break;
  }
  return opt;
}

int main()
{
  int opt;
  double balance = 10000.00;
  vector<Car*> cars;

  cout << endl << "~~ Car Inventory ~~" << endl;
  while (true) {
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~ Show current inventory [1] ~~" << endl;
    cout << "~~ Show current balance [2]   ~~" << endl;
    cout << "~~ Buy a car [3]              ~~" << endl;
    cout << "~~ Sell a car [4]             ~~" << endl;
    cout << "~~ Paint a car [5]            ~~" << endl;
    cout << "~~ Load file [6]              ~~" << endl;
    cout << "~~ Save file [7]              ~~" << endl;
    cout << "~~ Quit program [8]           ~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Choose an action: ";
    opt = getInt();
    opt = menu(opt, balance, cars);
    if (opt == 8) {
      break;
    }
  }
  return 0;
}
