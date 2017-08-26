#ifndef LUCASKANADECARTEDECHALEUR_H
#define LUCASKANADECARTEDECHALEUR_H

#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include "dossier.h"

class LucasKanadeCarteDeChaleur
{
public:
    LucasKanadeCarteDeChaleur();
    void runCarteDeChaleur(int taillevideo, string nouveauDossier, string traitement);
    void HSVtoRGB(float *r, float *g, float *b, float h, float s=1, float v=1);
};

#endif // LUCASKANADECARTEDECHALEUR_H
