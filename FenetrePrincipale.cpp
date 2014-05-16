#include "FenetrePrincipale.hpp"

using namespace std;

FenetrePrincipale::FenetrePrincipale() : QWidget()
{
    //Edit des propriétés de la fenetre
    setFixedSize(600, 700);
    //setGeometry(450, 300, 300, 400);
    setWindowIcon(QIcon("depense.png"));
    setWindowTitle("Friend Expenses V1.0");
    //setGeometry(100, 100, 600, 700);

    // Construction des widgets
    m_boutonOuvrir = new QPushButton("&Ouvrir le fichier CSV", this);
    m_boutonQuit = new QPushButton("&Quitter", this);
    m_boutonAjouter = new QPushButton("A&jouter", this);
    mlabel= new QLabel("Pas de fichier chargé", this);
    debug = new QTextEdit();

    // Personnalisation des widgets
    m_boutonOuvrir->setCursor(Qt::PointingHandCursor);
    m_boutonOuvrir->setIcon(QIcon("dossier.jpg"));
    mlabel->setGeometry(QRect(10, 70, 300, 20));
    mlabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    debug->setReadOnly(1);
    m_boutonAjouter->setEnabled(0);
    //m_boutonOuvrir->move(60, 20);
    //m_boutonQuit->move(110, 160);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(m_boutonOuvrir);
    layoutPrincipal->addWidget(mlabel);
    layoutPrincipal->addWidget(debug);
    layoutPrincipal->addWidget(m_boutonAjouter);
    layoutPrincipal->addWidget(m_boutonQuit);
    setLayout(layoutPrincipal);

    // Connexion du clic du bouton à la fermeture de l'application
    QObject::connect(m_boutonQuit, SIGNAL(clicked()), this, SLOT(ouvrirDialogueQuit()));
    QObject::connect(m_boutonOuvrir, SIGNAL(clicked()), this, SLOT(ouvrirDialogueCSV()));
    QObject::connect(m_boutonAjouter, SIGNAL(clicked()), this, SLOT(FenetreAjouterCSV()));
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
    QVector<Group> Groups;
    //Reset si réouverture
    for(QVector<Group>::iterator it = Groups.begin(); it != Groups.end(); ++it)
    {
        int exp = it->expensesPerPerson();
        for (size_t i=0; i < it->size(); ++i)
        {
            // operate the payback first
            (*it)[i]->operatePayback(exp);
            (*it)[i]->setName("");
            (*it)[i]->setPhoneNumber("");
            (*it)[i]->setExpenses(0);
            (*it)[i]->setPayback(0);
            it->setGroupName("");
            //(*it)[i]->setType("");
        }
    }

    debug->setText("");
    fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "CSV (*.csv)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
    mlabel->setText("<html><u><b>fichier</u></b> : </html>" + fichier);
    mlabel->setWordWrap(true);
    mlabel->setGeometry(QRect(10, 60, 280, 100));
    mlabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_boutonAjouter->setEnabled(1);    
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
    //iterate over persons to check for multiple expenses
    //two persons are considerated as the same when the name and the phone # is the same
    for(QVector<Group>::iterator it = Groups.begin(); it != Groups.end(); ++it)
    {
        for (size_t i=0; i < it->size(); ++i)
        {
            for(size_t j=0; j < it->size(); ++j)
            {
            if(i!=j && (*it)[i]->getName() == (*it)[j]->getName() && (*it)[i]->getPhoneNumber() == (*it)[j]->getPhoneNumber() && (*it)[i]->getGroupName() == (*it)[j]->getGroupName())
                {
                (*it)[i]->setExpenses((*it)[i]->getExpenses() + (*it)[j]->getExpenses());
                //we found two persons. Now remove the second one from the vector
                it->erase(it->begin()+j);
                }
            }
        }
    }
}

void FenetrePrincipale::Afficher(QVector<Group>& Groups)
{
    float aExpensesPerPerson = 0;
    int color_indexer = 0;
    QString colors[NB_MAX_COLOR] = {"white", "red", "green", "blue", "magenta", "black"};

    for(int i=1; i<Groups.size(); i++)
    {
        debug->append("Total expenses for group <FONT color=blue>" + Groups[i].getGroupName() + " </FONT>: <FONT color=red>" + QString::number((double)Groups[i].totalExpenses()) + "</FONT>");

        aExpensesPerPerson = Groups[i].expensesPerPerson();

        debug->append("Average expenses per person : <FONT color=yellow>" + QString::number((double)aExpensesPerPerson) + "</FONT>");
        debug->append("");
    }

        debug->append("Name\tPhone\tExpenses\tPayback\tGroup\tType");
        debug->append("-----------------------------------------------------------------------------------------------------");


    for(QVector<Group>::iterator it = Groups.begin(); it != Groups.end(); ++it)
    {
        int exp = it->expensesPerPerson();
        for (size_t i=0; i < it->size(); ++i)
        {
            // operate the payback first
            (*it)[i]->operatePayback(exp);
            // display the values
            debug->append(
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
        debug->append("");
        if(color_indexer==NB_MAX_COLOR-1)
            color_indexer=0;
        else
            color_indexer++;
    }
}

void FenetrePrincipale::FenetreAjouterCSV()
{
    d = new QDialog();
    d->setWindowTitle("Ajouter un utilisateur");

    //QlineEdit & QPushButton
    nom = new QLineEdit;
    phone = new QLineEdit;
    depense = new QLineEdit;
    nomdugroupe = new QLineEdit;
    QPushButton *boutonAjouter = new QPushButton("&Ajouter");
    QPushButton * boutonfermer = new QPushButton("&Fermer");

    //ComboBox
    liste = new QComboBox(d);
    liste->addItem("Donor");
    liste->addItem("Person");

    //Layout formulaire
    QFormLayout *formLayout2 = new QFormLayout(d);
    formLayout2->addRow("Votre nom", nom);
    formLayout2->addRow("Votre telephone", phone);
    formLayout2->addRow("Votre dépense", depense);
    formLayout2->addRow("Votre nom de groupe", nomdugroupe);
    formLayout2->addRow("Votre type", liste);
    formLayout2->addWidget(boutonAjouter);
    formLayout2->addWidget(boutonfermer);

    QObject::connect(boutonfermer, SIGNAL(clicked()), d, SLOT(close()));
    QObject::connect(boutonAjouter, SIGNAL(clicked()), this, SLOT(AjouterCSV()));

    d->show();
}

void FenetrePrincipale::AjouterCSV()
{
    QFile lesDonnees2(fichier);
    if(!lesDonnees2.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QTextStream flux(&lesDonnees2);
    flux.setCodec("UTF-8");
    if(nom->text()!="" && phone->text()!="" && depense->text()!="" && nomdugroupe->text()!="")
    {
        flux << nom->text() + "," +
                phone->text() + "," +
                depense->text() + "," +
                nomdugroupe->text() + "," +
                liste->currentText() + "\n" ;
        d->close();

        /*for(QVector<Group>::iterator it = Groups.begin(); it != Groups.end(); ++it)
        {
            int exp = it->expensesPerPerson();
            for (size_t i=0; i < it->size(); ++i)
            {
                // operate the payback first
                (*it)[i]->operatePayback(exp);
                (*it)[i]->setName("");
                (*it)[i]->setPhoneNumber("");
                (*it)[i]->setExpenses(0);
                (*it)[i]->setPayback(0);
                it->setGroupName("");
                //(*it)[i]->setType("");
            }
        }
        debug->setText("");
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
        }
            createGroup(Groups);
            Afficher(Groups);*/
    }
    else
        QMessageBox::critical(d, "Erreur", "Vous n'avez pas tout renseigné");

    lesDonnees2.close();
}


