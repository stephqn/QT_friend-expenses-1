/*
 * Arg.cpp
 *
 *  Created on: 6 mai 2014
 *      Author: paul
 */

#include "Arg.hpp"

Arg::Arg()
{
}

Arg::~Arg()
{
}

void help()//Gestion de l'ouverture et de l'affichage de l'aide
{
    char str;

    FILE * pFile;
    pFile = fopen ("../src/help.txt","r");
    if (pFile!=NULL)
    {
        while(fscanf(pFile, "%c", &str)!=EOF)
        {
            cout << str;
        }

      fclose (pFile);
    }
    else
        cout << "\n Failed to load Help, pls reinstall the software or contact the support at 0820 456 789" << endl;
}


void Arg::readArg(int nbrArg, char **myArg, int *state, string *newdata)//Gestion des arguments
{
    switch (nbrArg)
    {
      case 1://Si pas d'argument
          cout << "\nNo request specified.\nOpenning software Help...\n" << endl;
          help();//Ouverture de l'help
          *state = ERROR;
      break;

      case 2://Si Help ou File (sans nom de fichier)
          *state = ERROR;
          if(string(myArg[1])=="--help")
          {
              cout << "\nOpenning Software Help\n" << endl;
              help();//Ouverture de l'help
              break;
          }
          else
          {
              if(string(myArg[1])=="--file")
              {
                  cout << "\nError: no file mentioned." << endl;
              }
              else
              {
                  if((string(myArg[1])=="--name")||(string(myArg[1])=="--phone")||(string(myArg[1])=="--expense")||(string(myArg[1])=="--group")||(string(myArg[1])=="--type"))
                  {
                      cout << "\nError: options --name, --phone, --expense, --group and --type must be strictly used together." << endl;
                  }
                  else
                  {
                      cout << "\nError Arg. Type" << endl;
                      cout << "Use \"./friend-expenses --help\" for help" << endl;
                  }
              }
          }
      break;

      case 3://Si ouverture de fichier
              if(string(myArg[1])=="--file")
              {
                  cout << "Reading data file" << endl;
                  *state = READ;
              }
              else
              {
                  *state = ERROR;
                  if((string(myArg[1])=="--name")||(string(myArg[1])=="--phone")||(string(myArg[1])=="--expense")||(string(myArg[1])=="--group")||(string(myArg[1])=="--type"))
                  {
                      cout << "\nError: options --name, --phone, --expense, --group and --type must be strictly used together." << endl;
                  }
                  else
                  {
                      cout << "\nError Arg" << endl;
                      cout << "Use \"./friend-expenses --help\" for help" << endl;
                  }
              }
      break;

      case 13://Si ajout de ligne dans csv
          if((string(myArg[1])=="--name")&&(string(myArg[3])=="--phone")&&(string(myArg[5])=="--expense")&&(string(myArg[7])=="--group")&&(string(myArg[9])=="--type")&&(string(myArg[11])=="--file"))
          {
              cout << "\nAdding new line" << endl;
              *newdata=string(myArg[2])+ COMMA +string(myArg[4])+ COMMA +string(myArg[6])+ COMMA +string(myArg[8])+ COMMA + string(myArg[10]) + "\n";
              *state = WRITE;
          }
          else
          {
              cout << "\nError: options --name, --phone, --expense, --group and --type must be strictly used together." << endl;
              *state = ERROR;
          }
      break;

      default://Defaut
          *state = ERROR;
          if((string(myArg[1])=="--name")||(string(myArg[1])=="--phone")||(string(myArg[1])=="--expense")||(string(myArg[1])=="--group")||(string(myArg[1])=="--type"))
          {
              cout << "\nError: options --name, --phone, --expense, --group and --type must be strictly used together." << endl;
          }
          else
          {
              cout<<"\nError Arg"<< endl;
              cout << "Use \"./friend-expenses --help\" for help" << endl;
          }
        break;
      }
}

