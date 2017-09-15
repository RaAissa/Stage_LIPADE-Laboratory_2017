#ifndef MAFENETRE_H
#define MAFENETRE_H

/*
 * Auteur : Marah Poos
 * Date de création: 01/01/2016
 * Modifiée par: Van Cuong KIEU
 * Date de modification: 30/09/2016
 * Modifié par: Raouf AISSA
 * Date de modification: 01/03/2017
 */
#include <QCheckBox>
#include <QTextEdit>
#include <QApplication>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QMessageBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QImage>
#include <QCheckBox>
#include <QPixmap>
#include <QComboBox>
#include <tool.h>
#include <vector>
#include <QMouseEvent>
#include <QPoint>
#include "traitement.h"
#include <iostream>
#include <string>
#include <QFileInfo>
#include <sys/stat.h>
#include <cstdlib>



class MaFenetre : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

private:
    //modifié
     QCheckBox *checkbox;
    QTabWidget  *onglets;
    QPoint point;
    QGridLayout *layout;
     QGridLayout *layout1;
    QPushButton *bouton_ouvrir;
    QPushButton *bouton_lancer;
    QPushButton *bouton_enregistrer;
    QPushButton *bouton_play;


    //modifié
    QPushButton *bouton_tiff;
    QPushButton *bouton_ouvrirImage;



    QPushButton *bouton_ouvrirVideo;
    QImage image_initiale;
    QImage image_traitee;
    QImage image_evaluation;
    QLabel *label_image_evaluation;

    QLabel *label_videoInitiale;
    QLabel *label_videoTraitee;
    QImage image_inpainting;
    QLabel *label_image_inpainting;
    QImage video_inpainting;
    QLabel *label_videoInpainting;
    QLabel *label_positionPremierPoint;
    QLabel *label_positionSecondPoint;
    QLabel *label_positionPremierPointImage;
    QLabel *label_positionSecondPointImage;
    QLabel *label_positionPremierPointVideo;
    QLabel *label_positionSecondPointVideo;
    QImage image_K_means_nD_t;
    QLabel *label_K_means_nD_t;

    QImage image_flot_optique;
    QLabel *label_flot_optique;




    QSlider *slider;
    QLCDNumber *lcd;

    QComboBox *liste;
    //modifié
    QComboBox *liste1;
    QComboBox *liste2;
    QComboBox *liste3;
    QComboBox *liste4;
    QComboBox *liste5;

    //
    int taillevideo;
    int taillevideo2;
    QDir dir; // Dossier du fichier
    QString dirPath; // Path vers le fichier
    QString fileName; // Nom du fichier (sans le path)
    string nouveauDossier;
    string nomChemin;
    string nomCheminVideo;
    string traitement;
    string nomFichier;
    int positionSlider;
    int positionSwitch=0;
    int positionSwitch1=0;
    int positionSwitch2=0;
    int positionSwitch3=0;
    int positionSwitch4=0;
    int positionSwitch5=0;

    //modifie dés
    int w=0 , h=0 ;
    vector <QPoint> points;
    vector <QPoint> points_image;
    vector <QPoint> points_video2;
    double dWidth;
    double dHeight;
    double height_video1;
    double height_video2;
    double height_image;
    //modifié
    bool premiere_fois;
   //
    QString dirPathImage;
    QString fileNameImage;
    string nomCheminImage;
    string nomFichierImage;
    string nomFichierVideo;
    string nouveauDossierVideo;
    vector<Mat> allImages;
    std::vector<std::string> imaFolder;
public:
    MaFenetre();
    void mousePressEvent(QMouseEvent *event);

public slots:
    void ouvrirDialogue();
    void sliderMovedslot(int position);
    void enregistrer();
    void lancer();
    void afficher(int);
    //modifie
    void afficher1(int);
    void afficher2(int);
    void afficher3(int);
     void afficher4(int);
    void afficher5(int);
     //
    void play();
    void wait(float seconds);
    void ouvrirImage();
    void ouvrirVideoInpainting();




    //Modifié
    void verif();
    void ouvrirtiff();


};
#endif // MAFENETRE_H
