// Written by Aleks Christensen
//
// Test Cases
// 
// Input: Choice 1, slot 2
// Output: [2 1.5 1 1.5 2 2.5 3 2.5 3 2.5 3 3.5 4]
//         ~~ You won $10000! ~~
//
// Input: Choice 1, slot 7
// Output: [7 7.5 7 6.5 6 5.5 5 4.5 4 4.5 5 5.5 6]
//         ~~ You won $1000! ~~
//
// Input: Choice 2, 3 chips, slot 6
// Output: ~~ You won $2500! ~~ 


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int SLOT_VALUES[9] = {100,500,1000,0,10000,0,1000,500,100};
double path[13];
int final_step = 12;
int money;
int end;
int avg;

int lr()
{
  double r = rand() * 1.0 / RAND_MAX;
  int s = r + 0.5;
  return s;
}

void step(int slot, double path[])
{
  double pos = slot;
  for ( int n=0; n<13; n++ ) {
    int dir = lr();
    if ( pos == 0.0 ) {
      path[n] = 0.0;
      pos += 0.5;
    }
    if ( pos == 8.0 ) {
      path[n] = 8.0;
      pos -= 0.5;
    }
    if ( dir == 0 ) {
      path[n] = pos;
      pos -= 0.5;
    }
    if ( dir == 1 ) {
      path[n] = pos;
      pos += 0.5;
    }
  }
}

void sum_money(double path[])
{
  end = path[final_step];
  money += SLOT_VALUES[end];
}

void print(double path[], int money)
{
  cout << "[";
  for ( int m=0; m<13; m++ ) {
    cout << path[m] << " ";
  }
  cout << "\b]" << endl;
  cout << "~~ You won $" << money << "!~~" << endl;
}

int main()
{
  srand(time(0));
  while (true) {
    cout << endl << "What would you like to do?" << endl;
    cout << "//-------------------------------------//" << endl;
    cout << "// Drop one chip into a slot? [1]      //" << endl;
    cout << "// Drop multiple chips into a slot [2] //" << endl;
    cout << "// Exit [3]                            //" << endl;
    cout << "//-------------------------------------//" << endl;
    cout << "Make a choice: ";
    int sel;
    cin >> sel;
    switch ( sel ) {
      case 1:
        int slot;
        cout << "Which slot do you want to drop it in? ";
        cin >> slot;
        if ( slot < 0 || slot > 8 ) {
          cout << endl << "~~ Invalid slot ~~" << endl;
          break;
        }
        cout << endl;
        cout << "~~ Dropping a chip into slot " << slot << " ~~"<< endl;
        cout << endl << "~~ Path ~~" << endl;
        step(slot, path);
        money = 0;
        sum_money(path);
        print(path, money);
        break;
      case 2:
        int chips;
        cout << "How many chips do you want to drop? ";
        cin >> chips;
        if ( chips < 1 ) {
          cout << endl << "~~ Invalid number of chips ~~" << endl;
          break;
        }
        cout << "Which slot do you want to drop them in? ";
        cin >> slot;
        if ( slot < 0 || slot > 8 ) {
          cout << endl << "~~ Invalid slot ~~" << endl;
          break;
        }
        cout << endl;
        cout << "~~ Dropping " << chips << " chips into slot " << slot << " ~~" << endl;
        money = 0;
        for ( int a=1;a<=chips;a++ ) {
          step(slot, path);
          sum_money(path);
        }
        avg = money / chips;
        cout << endl << "~~ You won $" << money << "! ~~" << endl;
        cout << endl << "~~ Amount earned per chip (average): $" << avg << " ~~" << endl;
        break;
      case 3:
        cout << endl << "~~ Exiting game... ~~" << endl;
        return 0;
        break;
      default:
        cout << endl << "~~ That is not a valid choice. Please choose again. ~~" << endl;
        break;
    }
  }
  return 0;
}
