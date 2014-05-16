#include "FenetreSecondaire.hpp"
#include "FenetrePrincipale.hpp"

FenetreSecondaire::FenetreSecondaire() : QWidget()
{
    setGeometry(400, 400, 300, 200);
    setWindowTitle("Ajouter un utilisateur");

    //QlineEdit & QPushButton
    QLineEdit *nom = new QLineEdit;
    QLineEdit *phone = new QLineEdit;
    QLineEdit *depense = new QLineEdit;
    QLineEdit *nomdugroupe = new QLineEdit;
    QPushButton *boutonAjouter = new QPushButton("Ajouter");

    //ComboBox
    QComboBox *liste = new QComboBox(this);
    liste->addItem("Donor");
    liste->addItem("Person");

    //Layout formulaire
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Votre nom", nom);
    formLayout->addRow("Votre telephone", phone);
    formLayout->addRow("Votre dépense", depense);
    formLayout->addRow("Votre nom de groupe", nomdugroupe);
    formLayout->addRow("Votre type", liste);

    // Création du layout principal de la fenêtre (vertical)
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;

    // Ajout des layouts
    layoutPrincipal->addLayout(formLayout);
    layoutPrincipal->addWidget(boutonAjouter);
    layoutPrincipal->addWidget(liste);
    setLayout(layoutPrincipal);

    //Action
    //QString *fichier;
    QWidget::connect(boutonAjouter, SIGNAL(clicked()), this, SLOT(ajouterCSV()));

}

void FenetreSecondaire::ajouterCSV()
{
  //QString *fichier;
  //QFile lesDonnees(*fichier);
  //if(lesDonnees.open(QIODevice::ReadOnly | QIODevice::Text))
  //{
  //}

}
