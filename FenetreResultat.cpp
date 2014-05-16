#include "FenetreResultat.hpp"

FenetreResultat::FenetreResultat(): QWidget()
{
    setWindowTitle("Les dépenses");
    setGeometry(450, 100, 300, 546);

    m_boutonLoad = new QPushButton("Depense !", this);
    m_boutonLoad->move(60, 20);
   // QObject::connect(m_boutonLoad, SIGNAL(clicked()), this, SLOT(AfficherD(_list_group)));


/*
    nom = new QLabel("Pas de fichier chargé", this);
    nom->setGeometry(QRect(10, 10, 300, 20));
    nom->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    test = new QLabel("Pas de fichier chargé", this);
    test->setGeometry(QRect(10, 50, 500, 200));
    test->setAlignment(Qt::AlignHCenter | Qt::AlignTop);


    float aExpensesPerPerson = 0;

    for(unsigned int i=1; i<Groups.size(); i++)
    {
        qDebug() << "Total expenses for group " << Groups[i].getGroupName() << " : "  << Groups[i].totalExpenses() <<endl;
        aExpensesPerPerson = Groups[i].expensesPerPerson();
        qDebug() << "Average expenses per person : " << aExpensesPerPerson << endl;
        qDebug() << endl;
    }
    qDebug()  << left
                     <<  left
                     << "Name" << left
                     << "Phone Number"  << left
                     << "Expenses" << left
                     << "Payback"  << left
                     << "Group"  << left
                     << "Type"
                     << endl;
    qDebug() << "-------------------------------------------------------------------------"
        << endl;

    for(QVector<Group>::iterator it = Groups.begin(); it != Groups.end(); ++it)
    {
        int exp = it->expensesPerPerson();
        for (size_t i=0; i < it->size(); ++i)
        {
            // operate the payback first
            (*it)[i]->operatePayback(exp);
            // display the values
            qDebug() << left
                 << (*it)[i]->getName() << left
                 << (*it)[i]->getPhoneNumber() << left
                 << (*it)[i]->getExpenses() << left
                 << (*it)[i]->getPayback() << left
                 << it->getGroupName() << left
                 << (*it)[i]->getType();
        }
    qDebug() << endl;
    }

    /*QLabel *nom = new QLabel;
    QLabel *phone = new QLabel;
    QLabel *Expenses = new QLabel;
    QLabel *Payback = new QLabel;
    QLabel *Group = new QLabel;
    QLabel *Type = new QLabel;*/

    // Création du layout principal de la fenêtre (vertical)
    //QGridLayout *layoutPrincipal = new QGridLayout;
    //layoutPrincipal->addLayout(formLayout)
    /*layout->addWidget(nom, 0, 0);
    layout->addWidget(phone, 0, 1);
    layout->addWidget(Expenses, 0, 2);
    layout->addWidget(Payback, 0, 3);
    layout->addWidget(Group, 0, 4);
    layout->addWidget(Type, 0, 5);*/


    //setLayout(layoutPrincipal);*/
}
void FenetreResultat::AfficherD(QVector<Group>& Groups)
{
    qDebug() << "ok";
    test= new QLabel("test", this);
    test->setGeometry(QRect(10, 80, 280, 100));
    test->setText("<html><u><b>fichier</u></b> : </html>" + Groups[1].getGroupName());}
