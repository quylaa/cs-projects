// Written by Aleks Christensen

#include <string>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include "Arena.h"
#include "Robot.h"
#include "Archer.h"
#include "Cleric.h"

bool doThing(char opt, Arena* stadium)
{
    if (tolower(opt) == 'a') {
        cin.ignore();
        cout << endl << "Enter fighter info in form of <name> <class char> <maxHP> <str> <spd> <mgc>" << endl;
        cout << "Valid classes are: (C)leric, (R)obot, (A)rcher" << endl << endl;
		cout << "> ";
        string info;
        getline(cin, info);
		
		if (info.empty()) {
			cout << "!! Incorrect syntax; Fighter not added !!" << endl << endl;
			return false;
		}

        if (stadium->addFighter(info)) {
            cout << "!! Fighter added successfully !!" << endl << endl;
        } else {
            cout << "!! Incorrect syntax; Fighter not added !!" << endl << endl;
        }

    } else if (tolower(opt) == 'r') {
        cout << "> Enter name of fighter to remove: ";
        string name;
        cin >> name;
        if (stadium->removeFighter(name)) {
            cout << "!! Fighter successfully removed !!" << endl << endl;
            return true;
        } else {
            cout << "!! Fighter does not exist !!" << endl << endl;
            return false;
        }
    } else if (tolower(opt) == 'm') {
        cout << endl << "!! Fighter Menu !!" << endl << endl;
        cout << "> Select a fighter by name: ";
        string name;
        cin >> name;
        FighterInterface* ftr = stadium->getFighter(name);
        if (ftr->getName() != "NULL") {
          while (true) {
                cout << endl << "Get (n)ame" << endl;
                cout << "Get ma(x) HP" << endl;
                cout << "Get (c)urrent HP" << endl;
                cout << "Get (s)trength value" << endl;
                cout << "Get s(p)eed value" << endl;
                cout << "Get (m)agic value" << endl;
                cout << "Get (d)amage dealt" << endl;
                cout << "Deal d(a)mage" << endl;
                cout << "(R)eset fighter" << endl;
                cout << "R(e)generate fighter" << endl;
                cout << "(U)se fighter's ability" << endl;
                cout << "(Q)uit" << endl << endl;
    
                cout << "> Select an option: ";
                char in;
                cin >> in;
                if (tolower(in) == 'n') cout << ftr->getName() << endl;
                else if (tolower(in) == 'x') cout << endl << "!! " << ftr->getMaximumHP() << " !!" << endl;
				else if (tolower(in) == 'c') cout << endl << "!! " << ftr->getCurrentHP() << " !!" << endl;
				else if (tolower(in) == 's') cout << endl << "!! " << ftr->getStrength() << " !!" << endl;
				else if (tolower(in) == 'p') cout << endl << "!! " << ftr->getSpeed() << " !!" << endl;
				else if (tolower(in) == 'm') cout << endl << "!! " << ftr->getMagic() << " !!" << endl;
				else if (tolower(in) == 'd') cout << endl << "!! " << ftr->getDamage() << " !!" << endl;
                else if (tolower(in) == 'a') {
                    int dmg;
                    cout << endl << endl << "> Enter amount of damage to deal: ";
                    cin >> dmg;
                    ftr->takeDamage(dmg);
					cout << endl << endl << "!! Current HP: " << ftr->getCurrentHP() << " !!" << endl << endl;
                }
                else if (tolower(in) == 'r') {
                    ftr->reset();
					cout << endl << endl << "!! Fighter reset !!" << endl << endl;
                }
                else if (tolower(in) == 'e') {
                    ftr->regenerate();
					cout << endl << endl << "!! Fighter regenerated !!" << endl << endl;
                }
                else if (tolower(in) == 'u') {
                    if (ftr->useAbility()) {
						cout << endl << endl << "!! Ability used !!" << endl << endl;
                    } else {
						cout << endl << endl << "!! Could not use ability !!" << endl << endl;
                    }
                }
                else if (tolower(in) == 'q') break;
            }
        } else {
			cout << endl << "!! Fighter does not exist !!" << endl << endl;
            return false;
        }
    }
}

int main()
{
    Arena* stadium = new Arena();

    while (true) {
        cout << "<< Arena >>" << endl << endl;
        cout << "(A)dd fighter" << endl;
        cout << "(R)emove fighter" << endl;
        cout << "Fighter (M)enu" << endl;
        cout << "(Q)uit" << endl << endl;
		cout << "> ";
        char in;
        cin >> in;
        if (tolower(in) == 'q') break;
        else {doThing(in, stadium);}
    }


    // stadium->addFighter("John C 100 3 6 20");
    // stadium->addFighter("Bob R 150 20 8 12");
    // FighterInterface* first = stadium->getFighter("John");
    // FighterInterface* second = stadium->getFighter("Bob");
    // cout << first->getName() << endl;
    // cout << second->getName() << endl;
    // stadium->removeFighter("John");
    // stadium->removeFighter("Bob");

    delete stadium;
    return 0;
}
