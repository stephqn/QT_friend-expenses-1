/*
 * Donor.hpp
 *
 *  Created on: 3 avr. 2014
 *      Author: YH
 */

#ifndef DONOR_HPP_
#define DONOR_HPP_

#include "Person.hpp"
#include "Group.hpp"
#include <QString>

class Donor : public Person
{
public:
    Donor();
    Donor(const QString name, const QString phone, const float donation, const QString gName);
    float getExpenses() const;
    void setExpenses(const float expenses);

    void setType();

    void operatePayback(const float iExpensesPerPerson);
    virtual ~Donor();

private:
    float _donation;
};

#endif /* DONOR_HPP_ */
