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

int getInt(const int defaultValue = -1)
{
  string input;
  cin >> input;
  stringstream stream(input);
  int result = defaultValue;
  if (stream >> result) return result;
  else return result;
}

void doNothing()
{
  cout << endl << "!! This function is not yet implemented !!" << endl;
}

int showInv(vector<shared_ptr<Car>>& cars)
{
  cout << endl << "-------------------------------" << endl;
  for (size_t cur_car = 0; cur_car < cars.size(); ++cur_car) {
    //string name = (*cars)->at(cur_car).at(NAME_LOC);
    //string color = cars.at(cur_car).at(COLOR_LOC);
    //double price = stod(cars.at(cur_car).at(PRICE_LOC));
    //Car car(name, color, price);
    Car car = (*cars.at(cur_car));
    cout << car.toString();
    cout << "-------------------------------" << endl;
  }
  return 0;
}

int menu(int opt, double& balance, vector<shared_ptr<Car>>& cars)
{
  switch (opt) {
    case 1: // Show inventory
      // doNothing();
      showInv(cars);
      break;
    case 2: // Show balance
      // doNothing();
      cout << endl << "~~ Current balance is $" << setprecision(10) << balance << " ~~" << endl;
      break;
    case 3: // Buy car
      doNothing();
      break;
    case 4: // Sell car
      doNothing();
      break;
    case 5: // Paint car
      doNothing();
      break;
    case 6: // Load file
      doNothing();
      break;
    case 7: // Save file
      doNothing();
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
  double balance = 1000000.0;
  //vector<vector<string>> inventory;
  vector<shared_ptr<Car>> cars;

  //Car* ford = new Car("Ford","Red",12849.13);
  auto ford = make_shared<Car>("Ford", "Red", 4226.99);
  auto tesla = make_shared<Car>("Tesla", "White", 12368.99);
  cars.push_back(ford);
  cars.push_back(tesla);
  // vector<string> car1;
  // car1.push_back("Ford");
  // car1.push_back("Red");
  // car1.push_back("12853.84");
  // inventory.push_back(car1);
  // double p = stod(car1.at(2));
  // cout << p << " / ";
  // cout << setprecision(2) << fixed << p << endl;

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
