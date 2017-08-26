#ifndef INPAINTING_H
#define INPAINTING_H
#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QWidget>
#include "dossier.h"
using namespace std;
using namespace cv;

class Inpainting
{
public:
    Inpainting();
//    Inpainting(const QWidget* maFenetre, QLabel* lblImage);
    Mat calculerInpaintingTelea(Mat img, Mat masque);
    Mat calculerIntersection(Mat masque, Mat grabCut, Mat inpaintin);
    Mat calculerRectangleInscrit(Mat masque, int &hauteur, Rect &recPrecedent);
    void calculerPixels(Mat result);
    Mat calculerBoiteEnglobantee(vector<vector<Point> > contours_poly, vector<Rect> boundRect, Mat masque);
    Mat resizeImage(Mat rectangleInscrit, int hauteur);
    Mat calculerMasque(Mat masque, Mat rectangleInscrit);
    Mat copierImageDansTrame(Mat img, Mat rectangleInscrit, Mat image);
    Mat resizedImageTailleTramme(Mat rectangleInscrit, Mat resizedImage, int hauteur);
    Mat calculerInpaintingTeleaImage(Mat img, Mat masque);
    Mat copierInpaintingeDansTrame(Mat img, Mat inpainting_rectangleInscrit, Rect r);
  //  Mat copierInpaintingeDansTrame(Mat img, Mat inpainting_rectangleInscrit, Rect sr);
    void runInpaintingImage(int taillevideo, string nouveauDossier, string traitement, vector <QPoint> points_image, QString dirPathImage);
    void runInpainting(int taillevideo, string nouveauDossier, string traitement);

private:
    QLabel* _lblImage;
    const QWidget* _maFenetre;
    int w, h;
};

#endif // INPAINTING_H
