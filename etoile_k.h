#ifndef ETOILE_k_H
#define ETOILE_k_H


#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include "dossier.h"

using namespace std;
using namespace cv;

class etoile_k
{
public:
    etoile_k();
    void runEtoile(int&positionswitch,bool &premiere_fois,vector<Mat> allImages,int &position,int taillevideo, string nouveauDossier, string traitement);
    void runEtoile_compo(int&positionswitch,bool &premiere_fois,vector<Mat>allImages,int &position,int taillevideo, string nouveauDossier, string traitement);
    cv::Point barycentre(Mat img);
    void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
    void Kmeans_blobs(vector<Mat>allImages,cv::Mat &img1,cv::Mat&confusion,int position,string nouveauDossier, string traitement,int pixels,cv::Mat&centers1);
    double NormalDistribution(double mu,double sigma);
    Point barycentrecompo(vector<cv::Point2i >b);
    int distance(int x, int y,int m, Mat centers1);
    double NormalDistribution(double mu,double sigma, int x);
    int taille(vector<Mat>allImages);
    void creer_images(string nouveauDossier, string traitement);
    vector<int> Kmeans_blobs1(vector<Mat>allImages,std::vector<int>&Labels,cv::Mat &img1,cv::Mat&confusion,string nouveauDossier, string traitement,int pixels);
private:
    vector<Mat> all_Images;
    int t;
    static etoile_k Instance;
};

#endif // ETOILE_H
