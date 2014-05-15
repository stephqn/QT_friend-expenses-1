/*
 * Csv.cpp
 *
 *  Created on: 24 avr. 2014
 *      Author: masse
 */

#include "Csv.hpp"

using namespace std;

Csv::Csv() : _nbPersPerGroup (0)
{
}

Csv::~Csv()
{
    _myFile.close();
}

bool Csv::checkFile(string myFileName)
{
    _myFile.open(myFileName.c_str(), ios::in);
    if(_myFile)
    {
        _myFile.close();
        return true;
    }
    else
        return false;
}

void Csv::openCSV(string myFileName)
{
    qDebug() << "\nInput data file : ";
    if (checkFile(myFileName))
    {
        _myFile.open(myFileName.c_str(), ios::in | ios::out | ios::app);
    }
    else
    {
        qDebug() << "Exception caught while opening your file" << endl;
        qDebug() << "Please check file name or syntax." << endl;
        qDebug() << "Use \"./friend-expenses --help\" for help" << endl;
        //exit(1);
    }
}
void Csv::closeCsv()
{
    _myFile.close();
}
void Csv::writeCSV(string person)
{
    _myFile << person;
    _myFile.seekp(0); // reposition ourselves at the beginning
}
/*
void Csv::readCSV()
{
    bool group_status;
    int lineCounter(0);
    string currentLine;
    string item;

    while (1)
    {
        vector<string> person;

        getline(_myFile, currentLine);

        if (lineCounter != 0)
        {
            if (_myFile.eof())
                break;
            stringstream ss(currentLine.c_str());

            while (std::getline(ss, item, ',')) {
                person.push_back(item);

            }
            Person *aPerson = new Person;
            if (person[4] == "Person") {
                aPerson = new Person;
                aPerson->setName(person[0]);
                aPerson->setPhoneNumber(person[1]);
                aPerson->setExpenses(atof(person[2].c_str()));
                aPerson->setGroupName(person[3]);
                aPerson->setType();
            }
            if (person[4] == "Donor")
            {
                aPerson = new Donor;
                aPerson->setName(person[0]);
                aPerson->setPhoneNumber(person[1]);
                aPerson->setExpenses(atof(person[2].c_str()));
                aPerson->setGroupName(person[3]);
                aPerson->setType();
            }
            if (_list_group.size() == 0)
                _list_group.push_back(person[3]);
            for (unsigned int i = 0; i < _list_group.size(); i++)
            {
                if (_list_group[i] == person[3]) //group existe deja
                {
                    group_status = true;
                    break;
                } else
                    group_status = false;
            }
            if (!group_status)
            {
                _list_group.push_back(person[3]); // contient le nom des groupes
            }
            _vPerson.push_back(aPerson); // contient toutes les personnes
        }
        lineCounter++;
    }
}


void Csv::createGroup(vector<Group>& Groups)
{
    int nbDonor = 0;

    //trier les donnees lues dans le csv
    for (unsigned int i = 0; i < _list_group.size(); i++)
    {
        Group aGroup;
        aGroup.setGroupName(_list_group[i]);

        for (unsigned int j = 0; j < _vPerson.size(); j++) {
            if (_list_group[i] == _vPerson[j]->getGroupName()) {
                //personne par groupe
                _nbPersPerGroup++;
                aGroup.push_back(_vPerson[j]);
                if (_vPerson[j]->getType() == "Donor") {
                    nbDonor++;
                }
            }
        }
        //remplir vecteur de group
        aGroup.setNbPersGroup(_nbPersPerGroup - nbDonor);
        _nbPersPerGroup = 0;
        nbDonor = 0;
        Groups.push_back(aGroup);
    }

}

void Csv::setName(const string& iNameFile)
{
    _nameFile = iNameFile;
}
*/
