#ifndef FENETRERESULTAT_HPP
#define FENETRERESULTAT_HPP

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
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <QDesktopServices>
#include <QVector>
#include "Group.hpp"
#include "Person.hpp"
#include "Donor.hpp"

class FenetreResultat : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    FenetreResultat();

    public slots:
    void AfficherD(QVector<Group>& Groups);

    private:
    QPushButton *m_boutonLoad;
    QVBoxLayout *layoutPrincipal;
    QLabel *nom;
    QLabel *test;
    QLabel *Expenses;
    QLabel *Payback;
    QLabel *Grous;
    QLabel *Type;
    QVector<Person*> _vPerson;
    QVector<QString> _list_group;

};

#endif // FENETRERESULTAT_HPP
