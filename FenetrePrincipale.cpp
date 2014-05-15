#include "FenetrePrincipale.hpp"

using namespace std;

FenetrePrincipale::FenetrePrincipale() : QWidget()
{
    //Edit des propriétés de la fenetre
    //setFixedSize(300, 400);
    //setGeometry(450, 300, 300, 400);
    setWindowIcon(QIcon("depense.png"));
    setWindowTitle("Friend Expenses V1.0");
    setGeometry(100, 100, 600, 700);

    // Construction des widgets
    m_boutonOuvrir = new QPushButton("Ouvrir le fichier CSV", this);
    m_boutonQuit = new QPushButton("Quitter", this);
    mlabel= new QLabel("Pas de fichier chargé", this);
    test = new QTextEdit();
    test->setReadOnly(1);

    // Personnalisation des widgets
    m_boutonOuvrir->setCursor(Qt::PointingHandCursor);
    m_boutonOuvrir->setIcon(QIcon("dossier.jpg"));
    mlabel->setGeometry(QRect(10, 70, 300, 20));
    mlabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    //m_boutonOuvrir->move(60, 20);
    //m_boutonQuit->move(110, 160);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(m_boutonOuvrir);
    layoutPrincipal->addWidget(mlabel);
    layoutPrincipal->addWidget(test);
    layoutPrincipal->addWidget(m_boutonQuit);
    setLayout(layoutPrincipal);

    // Connexion du clic du bouton à la fermeture de l'application
    QObject::connect(m_boutonQuit, SIGNAL(clicked()), this, SLOT(ouvrirDialogueQuit()));
    QObject::connect(m_boutonOuvrir, SIGNAL(clicked()), this, SLOT(ouvrirDialogueCSV()));
}

void FenetrePrincipale::ouvrirDialogueQuit()
{
    int reponse = QMessageBox::question(this, "Quitter?", "Etes-vous sur de vouloir quitter ?", QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        QCoreApplication::quit();
    }
    else if (reponse == QMessageBox::No)
    {
    }
}

void FenetrePrincipale::ouvrirDialogueCSV()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "CSV (*.csv)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
    mlabel->setText("<html><u><b>fichier</u></b> : </html>" + fichier);
    mlabel->setWordWrap(true);
    mlabel->setGeometry(QRect(10, 60, 280, 100));
    mlabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    QFile lesDonnees(fichier);
    if(lesDonnees.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&lesDonnees);
        while(!flux.atEnd())
        {
            QVector<QString> person;
            QString line = flux.readLine();
            listeDeMots = line.split(",");
            person.push_back(line);

            Person *aPerson = new Person;
            if (listeDeMots.at(4) == "Person")
            {
                aPerson = new Person;
                aPerson->setName(listeDeMots.at(0));
                aPerson->setPhoneNumber(listeDeMots.at(1));
                aPerson->setExpenses(listeDeMots.at(2).toDouble());
                aPerson->setGroupName(listeDeMots.at(3));
                aPerson->setType();
            }
            if (listeDeMots.at(4) == "Donor")
            {
                aPerson = new Donor;
                aPerson->setName(listeDeMots.at(0));
                aPerson->setPhoneNumber(listeDeMots.at(1));
                aPerson->setExpenses(listeDeMots.at(2).toDouble());
                aPerson->setGroupName(listeDeMots.at(3));
                aPerson->setType();
            }
            bool group_status;

            if (_list_group.size() == 0)
                _list_group.push_back(listeDeMots.at(3));
            for (int i = 0; i < _list_group.size(); i++)
            {
                if (_list_group[i] == listeDeMots.at(3)) //group existe deja
                {
                    group_status = true;
                    break;
                }
                else
                    group_status = false;
            }
                if (!group_status)
                {
                    _list_group.push_back(listeDeMots.at(3)); // contient le nom des groupes
                }
            _vPerson.push_back(aPerson); // contient toutes les personnes
        }
        lesDonnees.close();

        QVector<Group> Groups;
        createGroup(Groups);
        Afficher(Groups);
    }
}

void FenetrePrincipale::createGroup(QVector<Group>& Groups)
{
int nbDonor = 0, _nbPersPerGroup;

    //trier les donnees lues dans le csv
    for (int i = 0; i < _list_group.size(); i++)
    {
        Group aGroup;
        aGroup.setGroupName(_list_group[i]);

        for (int j = 0; j < _vPerson.size(); j++) {
            if (_list_group[i] == _vPerson[j]->getGroupName()) {
                //personne par groupe
                _nbPersPerGroup++;
                aGroup.push_back(_vPerson[j]);
                if (_vPerson[j]->getType() == "Donor") {
                    nbDonor++;
                }
            }
        }
        //remplir vecteur de group
        aGroup.setNbPersGroup(_nbPersPerGroup - nbDonor);
        _nbPersPerGroup = 0;
        nbDonor = 0;
        Groups.push_back(aGroup);
    }
}

void FenetrePrincipale::Afficher(QVector<Group>& Groups)
{
    float aExpensesPerPerson = 0;
    int color_indexer = 0;
    QString colors[NB_MAX_COLOR] = {"white", "red", "green", "blue", "magenta", "black"};

    for(int i=1; i<Groups.size(); i++)
    {
        test->append("Total expenses for group <FONT color=blue>" + Groups[i].getGroupName() + " </FONT>: <FONT color=red>" + QString::number((double)Groups[i].totalExpenses()) + "</FONT>");

        aExpensesPerPerson = Groups[i].expensesPerPerson();

        test->append("Average expenses per person : <FONT color=yellow>" + QString::number((double)aExpensesPerPerson) + "</FONT>");
        test->append("");
    }

        test->append("Name\tPhone\tExpenses\tPayback\tGroup\tType");
        test->append("-----------------------------------------------------------------------------------------------------");


    for(QVector<Group>::iterator it = Groups.begin(); it != Groups.end(); ++it)
    {
        int exp = it->expensesPerPerson();
        for (size_t i=0; i < it->size(); ++i)
        {
            // operate the payback first
            (*it)[i]->operatePayback(exp);
            // display the values
            test->append(
                        "<pre><FONT size =2 color=" + colors[color_indexer] + ">"
                        + (*it)[i]->getName()+ "</FONT>" + "\t"
                        "<FONT size =2 color=" + colors[color_indexer] + ">"
                        + (*it)[i]->getPhoneNumber()+ "</FONT>" + "\t"
                        "<FONT size =2 color=" + colors[color_indexer] + ">"
                        + QString::number((double)(*it)[i]->getExpenses())+ "</FONT>" + "\t"
                        "<FONT size =2 color=" + colors[color_indexer] + ">"
                        + QString::number((double)(*it)[i]->getPayback()) + "</FONT>" + "\t"
                        "<FONT size =2 color=" + colors[color_indexer] + ">"
                        + it->getGroupName()+ "</FONT>" + "\t"
                        "<FONT size =2 color=" + colors[color_indexer] + ">"
                        + (*it)[i]->getType()
                        + "</FONT></pre>");

        }
        test->append("");
        if(color_indexer==NB_MAX_COLOR-1)
            color_indexer=0;
        else
            color_indexer++;
    }
}
