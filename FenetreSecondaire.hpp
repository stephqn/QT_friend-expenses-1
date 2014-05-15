#ifndef FENETRESECONDAIRE_HPP
#define FENETRESECONDAIRE_HPP

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
#include <QComboBox>
#include <QLabel>

class FenetreSecondaire : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    FenetreSecondaire();

    public slots:
    void ajouterCSV();

private:
    QLineEdit *nom;
    QLineEdit *phone;
    QLineEdit *depense;
    QLineEdit *nomdugroupe;
    QLabel *mlabel;
    QFormLayout *formLayout;


};

#endif // FENETRESECONDAIRE_HPP
