//============================================================================
// Name        : main.cpp
// Author      : YH
// Version     :
// Copyright   : latest
// Description : Application to manage friends expenses
//============================================================================

#include "Person.hpp"
#include "Group.hpp"
#include "Donor.hpp"
#include "Csv.hpp"
#include "Arg.hpp"
#include "FenetrePrincipale.hpp"
#include "FenetreSecondaire.hpp"
#include "FenetreResultat.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <gtest/gtest.h>
#include <QApplication>
#include <QPushButton>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QFont>
#include <QIcon>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>

#define DEBUG
#undef DEBUG

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetre;//Fenetre principal
    FenetreSecondaire fenetre2;//Fenetre secondaire
    FenetreResultat fenetre3;//Fenetre resultat

    // Affichage de la fenêtre
    fenetre.show();
    fenetre2.show();

    return app.exec();
}
