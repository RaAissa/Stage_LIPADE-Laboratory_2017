#include <QtWidgets/QApplication>
//#include "qmlapplicationviewer/qmlapplicationviewer.h"
#include <QApplication>
#include "mafenetre.h"
#include"Clustering.h"
#include"kmean.h"
/*
 * Auteur : Marah Poos
 * Date de création: 01/01/2016
 * Modifiée par: Van Cuong KIEU
 * Date de modification: 30/09/2016
 */
int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    MaFenetre fenetre;
    fenetre.show();
    return app.exec();

//kmean *v = new kmean();
//    v->run_kmean();



}
