/*
 * Group.hpp
 *
 *  Created on: Feb 18, 2014
 *      Author: YH
 */

#ifndef GROUP_HPP_
#define GROUP_HPP_

#include "Person.hpp"
#include <vector>
#include <string>

class Group : public vector<Person*> {
public:
    Group();
    Group(const QString groupName, int nbPers);
    virtual ~Group();

    const QString& getGroupName() const;
    void setGroupName(const QString& name);
    float totalExpenses() const;
    float expensesPerPerson() const;
    int getNbPersGroup() const;
    void setNbPersGroup(int nbPersGroup);
protected:
    QString _groupName;
    int _nbPersGroup;
};

#endif /* GROUP_HPP_ */
