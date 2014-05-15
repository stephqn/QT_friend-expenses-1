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
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QDesktopServices>
#include <QVector>
#include "Group.hpp"
#include "Person.hpp"
#include "Donor.hpp"
#include <string>
#include "FenetreResultat.hpp"
#include <iomanip>
#include <cstdlib>

#define NB_MAX_COLOR 7

class FenetrePrincipale : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    FenetrePrincipale();

    public slots:
    void ouvrirDialogueQuit();
    void ouvrirDialogueCSV();
    void createGroup(QVector<Group>& Groups);
    void Afficher(QVector<Group>& Groups);

    private:
    QPushButton *m_boutonOuvrir;
    QPushButton *m_boutonQuit;
    QLabel *mlabel;
    QTextEdit *test;
    QString line;
    QStringList listeDeMots;
    QFormLayout *Layout;
    QVBoxLayout *layoutPrincipal;
    QVector<Person*> _vPerson;
    QVector<QString> _list_group;
};

#endif
