/*
 * Arg.hpp
 *
 *  Created on: 6 mai 2014
 *      Author: paul
 */

#ifndef ARG_HPP_
#define ARG_HPP_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include <stdlib.h>
#include "Group.hpp"
#include "Person.hpp"
#include "Donor.hpp"
#include "Csv.hpp"

#define COMMA ","

enum STATE {ERROR = 1, WRITE, READ};
class Arg
{

public:
    Arg();
    virtual ~Arg();

    void readArg(int nbrArg, char **myArg, int *state, string *newdata);

};

#endif /* ARG_HPP_ */
