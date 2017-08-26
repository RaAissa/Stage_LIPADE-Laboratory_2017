#ifndef LUCASKANADE_H
#define LUCASKANADE_H

#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include "dossier.h"

using namespace std;
using namespace cv;

class LucasKanade
{
public:
    LucasKanade();
    void runLukasKanade(int&posiotionw,int&positionswitch,bool &premiere_fois,vector<Mat> allImages,int &position,int taillevideo, string nouveauDossier, string traitement);
    void HSVtoRGB(float *r, float *g, float *b, float h, float s=1, float v=1);

private:
    vector<Mat> all_Images;
    int t;
};

#endif // LUCASKANADE_H
