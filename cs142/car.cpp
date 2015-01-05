// Test cases
//
// Normal car costing $12,000 with 21 mpg vs. Hybrid car costing $25,000 with 38 mpg at $2.85/gal
// Normal car costing $18,000 with 26 mpg vs. Hybrid car costing $23,000 with 41 mpg at $3.20/gal
// Normal car costing $15,000 with 24 mpg vs. Hybrid car costing $31,000 with 47 mpg at $3.80/gal

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

string q[9] = {"Miles per year? ","Price of a gallon of gas? ","Cost of a hybrid car? ","MPG of a hybrid car? ","Resale value of a hybrid car in 5 years? ","Cost of a non-hybrid car? ","MPG of a non-hybrid car? ","Resale value of a non-hybrid car in 5 years? ","Buying criteria? [Gas, Total] "};
double a[8];
string criteria;
const string NEG = "You cannot enter a negative number.\n";
const string INVAL = "Invalid input.\n";
const int YEARS = 5;

int main()
{
  for ( int n=0; n<8; ++n) {
    cout << q[n];
    cin >> a[n];
    if ( signbit(a[n]) ) {
      cout << NEG;
      cout << q[n];
      cin >> a[n];
    }
  }
  cout << q[8];
  cin >> criteria;
  transform(criteria.begin(),criteria.end(),criteria.begin(),::tolower);
  if ( criteria != "total" && criteria != "gas" ) {
    cout << INVAL;
    cout << q[8];
    cin >> criteria;
    transform(criteria.begin(),criteria.end(),criteria.begin(),::tolower);
  }
  int miles = a[0] * YEARS;
  double gas_used_hybrid = miles / a[3];
  double gas_cost_hybrid = gas_used_hybrid * a[1];
  double gas_used_non = miles / a[6];
  double gas_cost_non = gas_used_non * a[1];
  int hybrid_dep = a[2] - a[4];
  int non_dep = a[5] - a[7];
  double hybrid_total_cost = hybrid_dep + gas_cost_hybrid;
  double non_total_cost = non_dep + gas_cost_non;
  cout << fixed << setprecision(2);
  if ( criteria == "total" ) {
    if ( hybrid_total_cost < non_total_cost ) {
      cout << "Car\t\t" << "Gallons used\t" << "Total cost of car" << endl;
      cout << "-------------------------------------------------" << endl;
      cout << "Hybrid car\t" << gas_used_hybrid << " gals\t$" << hybrid_total_cost << endl;
      cout << "Non-Hybrid car\t" << gas_used_non << " gals\t$" << non_total_cost << endl;
    } else {
      cout << "Car\t\t" << "Gallons used\t" << "Total cost of car" << endl;
      cout << "-------------------------------------------------" << endl;
      cout << "Non-Hybrid car\t" << gas_used_non << " gals\t$" << non_total_cost << endl;
      cout << "Hybrid car\t" << gas_used_hybrid << " gals\t$" << hybrid_total_cost << endl;
    }
  } else {
    if ( gas_used_hybrid < gas_used_non ) {
      cout << "Car\t\t" << "Gallons used\t" << "Total cost of car" << endl;
      cout << "-------------------------------------------------" << endl;
      cout << "Hybrid car\t" << gas_used_hybrid << " gals\t$" << hybrid_total_cost << endl;
      cout << "Non-Hybrid car\t" << gas_used_non << " gals\t$" << non_total_cost << endl;
    } else {
      cout << "Car\t\t" << "Gallons used\t" << "Total cost of car" << endl;
      cout << "-------------------------------------------------" << endl;
      cout << "Non-Hybrid car\t" << gas_used_non << " gals\t$" << non_total_cost << endl;
      cout << "Hybrid car\t" << gas_used_hybrid << " gals\t$" << hybrid_total_cost << endl;
    }
  }
  return 0;
}

// Extra credit point
//
// The hybrid car would have to have an mpg of 167 to be cheaper
// than the non-hybrid car in terms of total cost
