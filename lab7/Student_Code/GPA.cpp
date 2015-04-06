// Written by Aleks Christensen

#include "GPA.h"

StudentInterface* GPA::findSet(unsigned long long int id)
{
    // set<StudentInterface*, Comparator>::iterator sit;
    for (StudentInterface* sit : sset) {
        if (sit->getID() == id) return sit;
    }
    return *sset.end();
}

GPA::GPA()
{
	init();
}

GPA::~GPA(){ clear(); }

void GPA::init()
{
	scale.insert(pair<string, double>("A", 4.00));
	scale.insert(pair<string, double>("A-", 3.70));
	scale.insert(pair<string, double>("B+", 3.40));
	scale.insert(pair<string, double>("B", 3.00));
	scale.insert(pair<string, double>("B-", 2.70));
	scale.insert(pair<string, double>("C+", 2.40));
	scale.insert(pair<string, double>("C", 2.00));
	scale.insert(pair<string, double>("C-", 1.70));
	scale.insert(pair<string, double>("D+", 1.40));
	scale.insert(pair<string, double>("D", 1.00));
	scale.insert(pair<string, double>("D-", 0.70));
	scale.insert(pair<string, double>("E", 0.00));
}

bool GPA::isnum(string num)
{
    return !num.empty() && find_if(num.begin(), num.end(),
            [](char c) { return !isdigit(c); }) == num.end();
}

vector<string> GPA::import(string fileName)
{
	vector<string> info;
	fstream file(fileName);
	if(file) {
		for (string line; getline(file, line);) {
			info.push_back(line);
		}
	}
	return info;
}

map<unsigned long long int, StudentInterface*> GPA::getMap()
{
	return smap;
}

set<StudentInterface*, Comparator> GPA::getSet()
{
	return sset;
}

bool GPA::importStudents(string mapFileName, string setFileName)
{
	vector<string> mapInfo = import(mapFileName);
	vector<string> setInfo = import(setFileName);

	if (mapInfo.empty() || setInfo.empty()) return false;
	if ((mapInfo.size() % 4 != 0) || (setInfo.size() % 4 != 0)) return false;

	for (size_t i = 0; i < mapInfo.size(); i += 4) {
		if (!isnum(mapInfo.at(i))) return false;

		unsigned long long int newID = stoi(mapInfo.at(i));
		string newName = mapInfo.at(i+1);
		string newAddress = mapInfo.at(i+2);
		string newPhone = mapInfo.at(i+3);

		Student* newKid = new Student(newID, newName, newAddress, newPhone);
		smap.insert(pair<unsigned long long int, Student*>(newID, newKid));
	}

	for (size_t j = 0; j < setInfo.size(); j += 4) {
		if (!isnum(setInfo.at(j))) return false;

		unsigned long long int newID = stoi(setInfo.at(j));
		string newName = setInfo.at(j+1);
		string newAddress = setInfo.at(j+2);
		string newPhone = setInfo.at(j+3);

		Student* newKid = new Student(newID, newName, newAddress, newPhone);
		sset.insert(newKid);
	}
	return true;
}

bool GPA::importGrades(string fileName)
{
	vector<string> info = import(fileName);

	if (info.empty()) return false;

	for (size_t i = 0; i < info.size(); i += 3) {
		if (!isnum(info.at(i))) return false;

		unsigned long long int id = stoi(info.at(i));
		double grade = scale.at(info.at(i+2));

        StudentInterface* kid;
        if (smap.find(id) != smap.end()) kid = smap.find(id)->second;
        else if (findSet(id) != *sset.end()) kid = findSet(id);
        else return false;

		kid->addGPA(grade);
	}
	return true;
}

string GPA::querySet(string fileName)
{
	vector<string> info = import(fileName);
	if (info.empty()) return "";

	ostringstream out;

	for (size_t i = 0; i < info.size(); i++) {
		unsigned long long int id = stoi(info.at(i));
		
		StudentInterface* kid = findSet(id);

		if (kid != *sset.end()) {
      out << kid->getID() << " " << kid->getGPA() << " " << kid->getName() << endl;
		} 
	}

	return out.str();
}

string GPA::queryMap(string fileName)
{
	vector<string> info = import(fileName);
	if (info.empty()) return "";

	ostringstream out;
	out.precision(2);

	for (size_t i = 0; i < info.size(); i++) {
		unsigned long long int id = stoi(info.at(i));

		StudentInterface* kid = smap[id];

		if (kid) {
			out << kid->getID() << " " << kid->getGPA() << " " << kid->getName() << endl;
		}
	}
	return out.str();
}

void GPA::clear()
{
	for (pair<unsigned long long int, StudentInterface*> mit : smap) {
		delete mit.second;
	}
    smap.clear();

	for (StudentInterface* sit : sset) {
        delete sit;
	}
    sset.clear();
}
