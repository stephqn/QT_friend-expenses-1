#ifndef DEF_FENETREPRINCIPALE
#define DEF_FENETREPRINCIPALE

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
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QDesktopServices>
#include <QVector>
#include "Group.hpp"
#include "Person.hpp"
#include "Donor.hpp"
#include <string>
#include <iomanip>
#include <cstdlib>

#define NB_MAX_COLOR 7

class FenetrePrincipale : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    FenetrePrincipale();
    QString fichier;
    QComboBox *liste;
    QLineEdit *nom;
    QDialog *d = new QDialog();
    int flag = 0;

    public slots:
    void ouvrirDialogueQuit();
    void ouvrirDialogueCSV();
    void createGroup(QVector<Group>& Groups);
    void Afficher(QVector<Group>& Groups);
    void FenetreAjouterCSV();
    void AjouterCSV();

    private:
    QPushButton *m_boutonOuvrir;
    QPushButton *m_boutonQuit;
    QPushButton *m_boutonAjouter;
    QLabel *mlabel;
    QTextEdit *test;
    QString line;
    QStringList listeDeMots;
    QFormLayout *Layout;
    QVBoxLayout *layoutPrincipal;
    QVector<Person*> _vPerson;
    QVector<QString> _list_group;

    //Ajouter ligne
    QLineEdit *phone;
    QLineEdit *depense;
    QLineEdit *nomdugroupe;
    QPushButton *boutonAjouter;
    QPushButton * boutonfermer;
};

#endif
