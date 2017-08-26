#ifndef INPAINTINGINVERSER_H
#define INPAINTINGINVERSER_H

#include <opencv2/opencv.hpp>
#include <QPoint>
//#include <QLabel>
//#include <QWidget>
#include "dossier.h"
#include "inpainting.h"

using namespace std;
using namespace cv;

class InpaintingInverser
{
public:
    static void runInpaintingInverser(int taillevideo, string nouveauDossier, string traitement, vector <QPoint> points_image, string nouveauDossierVideo);
    static Mat InpaintingInverserFinal(Mat video, Mat video2, Mat masque);
};

#endif // INPAINTINGINVERSER_H
