/*
 * Person.hpp
 *
 *  Created on: Feb 18, 2014
 *      Author: YH
 */

#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <string>
#include <QString>
#include <iostream>

class Group;
using namespace std;

class Person
{
public:
    Person();
    Person(const QString name, const QString phone, const float expenses, const QString gName);
    virtual ~Person();

    const QString& getName() const;
    void setName(const QString& name);

    const QString& getPhoneNumber() const;
    void setPhoneNumber(const QString& phoneNumber);

    virtual float getExpenses() const;
    virtual void setExpenses(const float expenses);

    float getPayback() const;
    void setPayback(const float payBack);

    virtual void operatePayback(const float iExpensesPerPerson);

    const QString& getType() const;
    virtual void setType();

    /*
     * Getter & Setter to Group::_groupName
     * attribute is set through *_pGroup pointer
     */
    void setGroupName(const QString& name);
    const QString& getGroupName() const;

protected:
    QString _name;
    QString _phoneNumber;
    float _expenses;
    float _payback;
    QString _type;
private:
    Group *_pGroup;

};

#endif /* PERSON_HPP_ */
