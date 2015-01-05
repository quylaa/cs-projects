// Example cases
// 2 people with 15% tip = $17, 226.194 in^2 total, 113.097 in^2 each
// 14 people with 28% tip = $38, 628.318 in^2 total, 44.8799 in^2 each
// 68 people with 33% tip = $210, 3254.69 in^2,  47.863 in^2 each

#include <iostream>
#include <cmath>

using namespace std;

const double large_price = 14.68;
const double med_price = 11.48;
const double small_price = 7.28;
const int large_r = 10;
const int med_r = 8;
const int small_r = 6;
const double PI = 3.14159;
const int large_people = 7;
const int med_people = 3;
const int small_people = 1;

int pizzas[] = {0, 0, 0 };
double area = 0.0;

int square(int num)
{
  int result = num * num;
  return result;
}

void order(int people)
{

  while (people >= large_people) {
    pizzas[0] += 1;
    people -= large_people;
  }

  while (people >= med_people) {
    pizzas[1] += 1;
    people -= med_people;
  }

  while (people >= small_people) {
    pizzas[2] += 1;
    people -= small_people;
  }
}

void total_area()
{
  int n;
  int radii[] = { large_r, med_r, small_r };
  for ( n=0; n<3; ++n) {
    area += pizzas[n] * ( PI * ( square(radii[n])));
  }
}

double price_per(double pizza, int tip)
{
  double true_tip = tip / 100.0;
  double price = (pizza * true_tip) + pizza;
  return price;
}

int total_price(int tip)
{
  int total = 0;
  int m;
  int prices[] = { large_price, med_price, small_price };
  double large_total = pizzas[0] * (large_price + ((large_price * tip) / 100));
  double med_total = pizzas[1] * (med_price + ((med_price * tip) / 100));
  double small_total = pizzas[2] * (small_price + ((small_price * tip) / 100));
  int all_total = large_total + med_total + small_total + 0.5;
//  for ( m=0; m<3; ++m) {
//    double true_price = prices[m] + ((prices[m] * tip) / 100 ) + 0.5;
//    total += pizzas[m] * true_price;
//  }
  return all_total;
}

int main()
{
  int people;
  int tip;

  cout << "I am the Pizza Helper!\n";
  cout << "How many people will be attending your party? ";
  cin >> people;
  order(people);
  total_area();
  cout << pizzas[0] << " Large Pizza(s)" << endl;
  cout << pizzas[1] << " Medium Pizza(s)" << endl;
  cout << pizzas[2] << " Small Pizza(s)" << endl;
  cout << "The total pizzarea (haha) is " << area << " inches^2" << endl;
  cout << "Each person can have " << area/people << " inches^2" << endl;
  cout << "What percent will you tip? ";
  cin >> tip;
  int total = total_price(tip);
  cout << "The total cost will be $" << total << endl;

  return 0;
}
