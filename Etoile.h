#ifndef ETOILE_H
#define ETOILE_H


#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include "dossier.h"

using namespace std;
using namespace cv;

class Etoile
{
public:
    Etoile();
    void runEtoile(int&positionswitch,bool &premiere_fois,vector<Mat> allImages,int &position,int taillevideo, string nouveauDossier, string traitement);
    void runEtoile_compo(int&positionswitch,bool &premiere_fois,vector<Mat>allImages,int &position,int taillevideo, string nouveauDossier, string traitement);
    cv::Point barycentre(Mat img);
    void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
    Mat Kmeans_blobs(/*vector < std::vector<cv::Point2i > > &blobs,*/cv::Mat &img1,cv::Mat&confusion,int position,string nouveauDossier, string traitement,int pixels);
    double NormalDistribution(double mu,double sigma);
    Point barycentrecompo(vector<cv::Point2i >b);
   Mat Dilation(Mat h);
private:
    vector<Mat> all_Images;
     int t;

  static Etoile Instance;
};

#endif // ETOILE_H
