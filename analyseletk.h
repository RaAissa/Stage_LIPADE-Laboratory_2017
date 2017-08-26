#ifndef ANALYSELETK_H
#define ANALYSELETK_H

#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include "dossier.h"
#include <QPoint>
#include <QLabel>
#include <QWidget>
using namespace std;
using namespace cv;

class Analyseletk
{
public:

    Analyseletk();
   int taille(vector<Mat>allImages);
    void evaluation_inertie_intra();
    void runAnalyseletk( vector <QPoint> points,int&posiotionw,int&positionswitch,bool &premiere_fois,vector<Mat> allImages,int &position,int taillevideo, string nouveauDossier, string traitement,int &ind_k);
    void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
    Point barycentrecompo(vector<cv::Point2i >b);
    Point3d barycentre_nuage(vector<cv::Point2i >b, int m);
    void Kmeans_1D(cv::Mat &img1,cv::Mat&confusion,string nouveauDossier,string traitement,int pixels,cv::Mat&centers,int &ind_k);
    void Kmeans_ND(vector<Mat>allImages,std::vector<int>&Labels,int size_of_features,cv::Mat &img1,cv::Mat&confusion,string nouveauDossier, string traitement,int pixels,cv::Mat&centers1,int &ind_k);
    int distance(int x,int frame, Mat centers1,int taille);
    void moyenne_de_fenetre(Mat & mat,int Kernel_choice );
private:
     std::vector<uchar> features_found;
    Point2i getPointInImage(QPoint p);
    QLabel* _lblImage;
    const QWidget* _maFenetre;
    vector<Mat> all_Images;
    int t;
    int m;
    QLabel *label_videoInitiale;
};

#endif // ANALYSELETK_H
