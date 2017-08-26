#ifndef GRAPHCUT_H
#define GRAPHCUT_H

#include <opencv2/opencv.hpp>
#include <QPoint>
#include <QLabel>
#include <QWidget>
#include "dossier.h"

using namespace std;
using namespace cv;

class GraphCut
{
protected:
    Mat img;

public:
    GraphCut(const QWidget* maFenetre, QLabel* lblImage);
    GraphCut(Mat img):img(img){}
    Mat calculerGraphCut(Mat img, vector <QPoint> points, String chemin, int i, string nouveauDossier);
    Mat calculerFond(Mat result, Mat img);
    Mat calculerBoiteEnglobante(vector<vector<Point> > contours_poly, vector<Rect> boundRect);

private:
    Point2i getPointInImage(QPoint p);
    QLabel* _lblImage;
    const QWidget* _maFenetre;
    int w, h;
//    int calculerHeight(int, int);
//    int calculerWidth(int, int);
};

#endif // GRAPHCUT_H
