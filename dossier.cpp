#include "dossier.h"


void Dossier::creerDossier(string dossier){
    const int dir_err = system(("mkdir -p " + dossier).c_str());
    if (-1 == dir_err)
        {
        cout << "Erreur : Impossible de creer le dossier: " << dossier << endl;
        exit(1);
        }
    cout << "Efini"<<endl;
}
