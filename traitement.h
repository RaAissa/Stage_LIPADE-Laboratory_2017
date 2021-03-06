

/*
 * Auteur : Marah Poos
 * Date de création: 01/01/2016
 * Modifiée par: Van Cuong KIEU
 * Date de modification: 30/09/2016
 * Modifié par: Raouf AISSA
 * Date de modification: 01/03/2017
 */
#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "dossier.h"
#include "tool.h"
#include "graphcut.h"
#include "inpainting.h"
#include "video.h"
#include "inpainter.h"
#include "inpaintingimage.h"
#include "lucaskanade.h"
#include "lucaskanadedirection.h"
#include "lucaskanadecartedechaleur.h"
#include "lucaskanadedirectionsintensite.h"
#include "inpaintinginverser.h"
#include "analyseletk.h"
#include "Etoile.h"
#include "etoile_k.h"
#include "evaluation_class.h"
#include <map>
#include"Bibliotheque.h"

class Traitement
{
public:
    Traitement();
    void run(int&positionwinsize,int &positionSwitch1,int &position,vector<Mat> &allImages,bool &premiere_fois,int positionSwitch, int taillevideo, string nouveauDossier, int positionSlider, QLabel *label_videoInitiale, vector <QPoint> points, const QWidget* maFenetre,std::vector<std::string> imaFolder, vector <QPoint> points_image, QString dirPathImage, QLabel &label_image_inpainting, string nouveauDossierVideo, vector <QPoint> points_video2, QLabel *label_videoInpainting,int&indice_k);


private:
    void runGrabCut(int taillevideo, string nouveauDossier, int positionSlider, QLabel *label_videoInitiale, vector <QPoint> points, const QWidget* maFenetre,string traitement);
    void runGrabCutLucasKanade(int taillevideo, string nouveauDossier, int positionSlider, QLabel *label_videoInitiale, vector <QPoint> points, const QWidget* maFenetre,string traitement);
    void runInpainting(int taillevideo, string nouveauDossier, string traitement);
    //void HSVtoRGB(float *r, float *g, float *b, float h, float s=1, float v=1);
    //void RGBtoHSV(float *r, float *g, float *b, float h, float s, float v);
   // void runLukasKanade(int taillevideo, string nouveauDossier, string traitement);
    void runInpaintingImage(int taillevideo, string nouveauDossier, string traitement, vector <QPoint> points_image, QString dirPathImage);
    Point calculerPoint(double delta, Point p1, Point p0);
    //void runCarteDeChaleur(int taillevideo, string nouveauDossier, string traitement);
    //void runDirectionsDeplacement(int taillevideo, string nouveauDossier, string traitement);
    void runDirectionsDeplacementIntensite(int taillevideo, string nouveauDossier, string traitement);
    int maxTri(int x, int y, int z);
    int minTri(int x, int y, int z);
    vector<Mat> all_Images;
    QLabel *label_videoInitiale;
    QLabel *label_videoTraitee;
};

#endif // TRAITEMENT_H
