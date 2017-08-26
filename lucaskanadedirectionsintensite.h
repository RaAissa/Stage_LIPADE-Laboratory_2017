#ifndef LUCASKANADEDIRECTIONSINTENSITE_H
#define LUCASKANADEDIRECTIONSINTENSITE_H

#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include "dossier.h"
#include <iostream>

class LucasKanadeDirectionsIntensite
{
public:
    LucasKanadeDirectionsIntensite(vector<Mat> allImages);
    void runDirectionsDeplacementIntensite(int taillevideo, string nouveauDossier, string traitement);

private:
    vector<Mat> all_Images;
};

#endif // LUCASKANADEDIRECTIONSINTENSITE_H
