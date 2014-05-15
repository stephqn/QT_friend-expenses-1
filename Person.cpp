/*
 * Person.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: YH
 */

#include "Person.hpp"
#include "Group.hpp"

using namespace std;

Person::Person() :
    _expenses(0),
    _payback(0) {
    _pGroup = new Group;
}

Person::Person(const QString name, const QString phone, const float expenses, const QString gName)
{
    _name = name;
    _phoneNumber = phone;
    _expenses = expenses;
    _payback = 0;
    _pGroup = new Group;
    this->setGroupName(gName);
    this->setType();
}

Person::~Person()
{
    delete _pGroup;
}


const QString& Person::getName() const
{
    return _name;
}

const QString& Person::getPhoneNumber() const
{
    return _phoneNumber;
}

float Person::getExpenses() const
{
    return _expenses;
}

float Person::getPayback() const
{
    return _payback;
}

void Person::setName(const QString& name)
{
    _name = name;
}

void Person::setPhoneNumber(const QString& phoneNumber)
{
    _phoneNumber = phoneNumber;
}

void Person::setExpenses(const float expenses)
{
    _expenses = expenses;
}

void Person::setPayback(const float expenses)
{
    _payback = expenses;
}

void Person::operatePayback(const float iExpensesPerPerson) {
    _payback = _expenses - iExpensesPerPerson;
}

void Person::setType()
{
    _type = "Person";
}

const QString& Person::getType() const
{
    return _type;
}

void Person::setGroupName(const QString& name)
{
    _pGroup->setGroupName(name);
}

const QString& Person::getGroupName() const
{
    return _pGroup->getGroupName();
}
