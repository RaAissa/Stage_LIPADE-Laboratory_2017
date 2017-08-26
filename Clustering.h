#include <opencv2/opencv.hpp>
#include "opencv/highgui.h"
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


class Clustering{

public:

Clustering(){

}
void run_main(cv::Mat &img1,cv::Mat&confusion,int position,string nouveauDossier, string traitement,int pixels)
{
    cout<<"kmeans"<<endl;
    const int MAX_CLUSTERS =2;
    Scalar colorTab[] ={
     Scalar(0, 0, 255),
     Scalar(0,255,0),
     Scalar(255,100,100),
     Scalar(255,0,255),
     //Scalar(0,255,255),
     //Scalar(255,255,0),
     //Scalar(0,0,0),
     //Scalar(255,255,255),
     //Scalar(100,100,100),
     //Scalar(0,50,50),
     //Scalar(150,0,150),
     //Scalar(50,0,50),
    };
cout<<"8"<<endl;
    Mat img((int)img1.rows/pixels,(int)img1.cols/pixels, CV_8UC3);
    cout<<"9"<<endl;
    Mat dist(img1.rows,img1.cols,CV_8UC3);
    cout<<"10"<<endl;
    Mat labels;
    Mat centers;
    cout<<"1"<<endl;
    kmeans(confusion,MAX_CLUSTERS, labels,
           TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
           3, KMEANS_PP_CENTERS, centers);
     cout<<"2"<<endl;
   cout<<"###########labels############"<<endl;
   dist = Scalar::all(255);
   int size3= confusion.rows;
   int j=0;
   int k=0;
   int compteur_alpha=0;

   for(int i = 0; i <size3; i++ ){
       Point centre(0,0);
       if (compteur_alpha%img.cols==0){
           j++;
           k=0;
           compteur_alpha=0;
       }
      int clusterIdx = labels.at<int>(i);
      if(k==0&&j!=0){ centre.x=k;centre.y=(j*pixels);}
      if(k!=0&&j==0){centre.x=k*pixels;centre.y=j;}
      if(k==0&&j==0){centre.x=k;centre.y=j;}
      if(k!=0&&j!=0){centre.x=k*pixels;centre.y=j*pixels;}

      //circle( dist, centre, 4, colorTab[clusterIdx], 5, CV_AA);
      rectangle(dist, Rect(centre.x, centre.y,pixels-1,pixels-1),colorTab[clusterIdx],-1 );
      compteur_alpha++;
      k++;
   }
   imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans/frame%d.tif").c_str(), position).c_str(), dist);
   img.release();
   dist.release();
   centers.release();
}
};
