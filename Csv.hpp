/*
 * Csv.hpp
 *
 *  Created on: 24 avr. 2014
 *      Author: masse
 */

#ifndef CSV_HPP_
#define CSV_HPP_

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <limits>
#include <vector>
#include <stdlib.h>
#include "Group.hpp"
#include "Person.hpp"
#include "Donor.hpp"
#include <QDebug>

using namespace std;

class Csv
{
public:
    Csv();
    virtual ~Csv();

    void setName(const string& iNameFile);
    void openCSV(string myFileName);
    void readCSV();
    void writeCSV(string person);
    void createGroup (vector <Group>& groups);
    inline bool checkFile(string myFileName);
    void closeCsv();

private :
    string _nameFile;
    fstream _myFile;
    vector<Person*> _vPerson;
    vector<string>  _list_group;
    int _nbPersPerGroup;
};

#endif /* CSV_HPP_ */
