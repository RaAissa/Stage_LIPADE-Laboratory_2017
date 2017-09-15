/*
 * Auteur: Raouf AISSA
 * Date de creation: 01/03/2017
 */
 
#include "analyseletk.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Clustering.h"
#include "Bibliotheque.h"
#include "lucaskanadecartedechaleur.h"
Analyseletk::Analyseletk()
{
}

//Analyseletk::evaluation_inertie_intra(){
//    double distances;
//    for(int i=0; i<1000; i++){
//        distance=+sqrt(((poinx-poinx_cluster)*(poinx-poinx_cluster))+((poiny-poiny_cluster)*(poiny-poiny_cluster))+((point-point_cluster)*(point-poinx_cluster));
//    }
//   double inertie==distance/nombre de points;
//}


void Analyseletk::moyenne_de_fenetre(Mat & mat,int kernel_choice){
    Mat kern = (Mat_<char>(5, 5) << 1, 1, 1, 1, 1,
                                    1, 1, 1, 1, 1,
                                    1, 1, 1, 1, 1,
                                    1, 1, 1, 1, 1,
                                    1, 1, 1, 1, 1);
    Mat kern3 = (Mat_<char>(3, 3) << 1, 1, 1,
                                     1, 1, 1,
                                     1, 1, 1);
    if(kernel_choice==1){
        filter2D(mat,mat,-1,kern,Point(-1,-1),0,BORDER_DEFAULT);
    }
    if(kernel_choice=2){
        filter2D(mat,mat,-1,kern3,Point(-1,-1),0,BORDER_DEFAULT);
    }
}

void Analyseletk::runAnalyseletk( vector <QPoint> points,int&positionw,int&positionswitch,bool &premiere_fois,vector<Mat> allImages,int &position,int taillevideo, string nouveauDossier, string traitement,int &ind_k){
    //int lis[]={27,85,96,88,56,94,97,100,78,92,97,99,79,84,96,100,92,93,96,100};
    float temps;
    clock_t t1, t2;
    t1 = clock();
    Mat dst,img_hsv;
    Mat imgA, imgB, imgC, img, dist,dist1,dist2,dist3,dist4,centers1;
    int nombre_dist = 0;
    map<int,int> histogramme;
    vector<vector<cv::Vec4i> > allDistances;
    int compt=0;
    std::vector<cv::Point2f> cornersC;
    std::vector <int> Labels;
    int label;
    int pixels=positionswitch;
    QPoint secondPoint = points.back();
    points.pop_back();
    QPoint firstPoint = points.back();
    Mat imgref=imread("/home/aissa/Bureau/out5/frame1.tif",CV_LOAD_IMAGE_COLOR);
    if (premiere_fois==true){
        Dossier::creerDossier(nouveauDossier + "/" + traitement +"/FlotOptique");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/FlotOptique/resize");
        Dossier::creerDossier(nouveauDossier + "/" + traitement+ "/Kmeans");
        Dossier::creerDossier(nouveauDossier + "/" + traitement +"/Kmeans2d");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans2d/resize");
        Dossier::creerDossier(nouveauDossier + "/" + traitement +"/blured");
    }
    ofstream fichier66 ( "/home/aissa/Bureau/temps_de_calcul.txt", ios::out | ios::app);
    ofstream fichier61 ( "/home/aissa/Bureau/x.txt", ios::out | ios::trunc);
    ofstream fichier62 ( "/home/aissa/Bureau/y.txt", ios::out | ios::trunc);
    fichier66<<"image " <<" "<<traitement<<endl;
    int size1=0;
    Mat imgA1 = allImages[(int)(taillevideo/2)];
    for(int y = 0 ; y < imgA1.rows ; y = y + pixels){
        for(int x = 0 ; x < imgA1.cols ; x = x +pixels){
            size1++;
        }
    }
    cout<<size1<<endl;
    Mat MATRICE(size1, 4, CV_32F);
    Mat MATRICE_2;
    //std::vector<cv::Mat> Vec_de_mat;
    ////////////////////////debut
    Mat binary;
    std::vector < std::vector<cv::Point2i > > blobs;
    cout<<taillevideo;
    imgA = allImages[(int)(taillevideo/2)];
    imgB = allImages[(int)((taillevideo/2)+1)];
    dist1 = Mat::zeros(imgA.size(), imgA.type());
    dist2 = Mat::zeros(imgB.size(), imgB.type());
    cvtColor(imgA, dist1, CV_RGB2GRAY);
    cvtColor(imgB, dist2, CV_RGB2GRAY);
    std::vector<cv::Mat> BGR_channels;
    cv::split(imgA, BGR_channels);
    cv::Mat B_image = BGR_channels[0];
    cv::Mat G_image = BGR_channels[1];
    cv::Mat R_image = BGR_channels[2];
    //imwrite(cv::format((nouveauDossier + "/" + traitement + "/blured/frame%d.tif").c_str(),2).c_str(),imgA);
    //moyenne_de_fenetre(B_image);
    //imwrite(cv::format((nouveauDossier + "/" + traitement + "/blured/frame%d.tif").c_str(),1).c_str(),B_image);
    //calcul du RGB dans un voisinage 3*3 ou 5*5
    //moyenne_de_fenetre(B_image,1 /*1=>kernel5*5, 2==kernel3*3*/ );
    imwrite(cv::format((nouveauDossier + "/" + traitement + "/blured/frame%d.tif").c_str(),2).c_str(),imgA);
    //imwrite(cv::format((nouveauDossier + "/" + traitement + "/blured/frame%d.tif").c_str(),2).c_str(),R_image);
    //moyenne_de_fenetre(R_image);
    //imwrite(cv::format((nouveauDossier + "/" + traitement + "/blured/frame%d.tif").c_str(),1).c_str(),R_image);
    if(cv::countNonZero(dist1) !=0 && cv::countNonZero(dist2)!=0){
        int win_size= positionw;
        std::vector<cv::Point2f> cornersA;
        std::vector<cv::Point2f> cornersB;
        cvtColor(imgA,img_hsv,CV_BGR2HSV);
        std::vector<cv::Mat> hsv_channels;
        cv::split(imgA, hsv_channels);
        cv::Mat h_image = hsv_channels[0];
        cv::Mat s_image = hsv_channels[1];
        cv::Mat v_image = hsv_channels[2];
        int indice=0;
        cornersA.clear();
        cornersB.clear();
        //if (premiere_fois==true){
        //Mat diff = Mat::zeros(imgA.size(), imgA.type());
        //ne pas enlever partie blured
        //for(int y = 0 ; y < imgA.rows ; y = y +1){
        //for(int x = 0 ; x < imgA.cols ; x = x +1){
        //Vec3b intensite1= imgA.at<Vec3b>(y,x);
        //Vec3b intensite2= imgB.at<Vec3b>(y,x);
        //Vec3b intensite3= diff.at<Vec3b>(y,x);
        //intensite3.val[0]=abs(intensite2.val[0]-intensite1.val[0]);
        //intensite3.val[1]=abs(intensite2.val[1]-intensite1.val[1]);
        //intensite3.val[2]=abs(intensite2.val[2]-intensite1.val[2]);
        //diff.at<Vec3b>(y,x)[0]= intensite3.val[0];
        //diff.at<Vec3b>(y,x)[1]= intensite3.val[1];
        //diff.at<Vec3b>(y,x)[2]= intensite3.val[2];
        //diff.at<uchar>(y,x)=abs(dist2.at<uchar>(y,x)-dist1.at<uchar>(y,x));
        //}
        //}
        //imwrite(cv::format("/home/aissa/Bureau/diff%d.tif", 1).c_str(), diff);
        for(int y = 0 ; y < imgA.rows ; y = y + pixels){
            for(int x = 0 ; x < imgA.cols ; x = x +pixels){
                Vec3b intensite = imgA.at<Vec3b>(y,x);
                //if (intensite.val[0]!=0 && intensite.val[1]!=0 && intensite.val[2]!=0){
                cornersA.push_back(Point(x,y));
// MATRICE.at<float>(indice,1)=(float)(h_image.at<uchar>(y,x)*2);
//                     MATRICE.at<float>(indice,1)=(float)s_image.at<uchar>(y,x);
                     MATRICE.at<float>(indice,3)=(float)s_image.at<uchar>(y,x);

                       //couleur moyenne pour un
//                       MATRICE.at<float>(indice,3)=(float)B_image.at<uchar>(y,x)/255;
//                       MATRICE.at<float>(indice,4)=(float)G_image.at<uchar>(y,x)/255;
//                       MATRICE.at<float>(indice,5)=(float)R_image.at<uchar>(y,x)/255;
//                       MATRICE.at<float>(indice,3)=(float)imgA.at<Vec3b>(y,x).val[0];
//                       MATRICE.at<float>(indice,3)=(float)imgA.at<Vec3b>(y,x).val[1];
//                       MATRICE.at<float>(indice,3)=(float)imgA.at<Vec3b>(y,x).val[2];
//                       cout<<(int)imgA.at<Vec3b>(y,x).val[1]<<endl;
//                       cout<<"hue"<<endl;
//                       cout<<(float)h_image.at<uchar>(y,x)<<endl;
//                       cout<<(float)s_image.at<uchar>(y,x)<<endl;
//                       cout<<(float)v_image.at<uchar>(y,x)<<endl;
                     MATRICE.at<float>(indice,1)=x/imgA.cols;
                      MATRICE.at<float>(indice,2)=y/imgA.rows;

                    //}
                indice ++;
                }
            }
//            std::vector<cv::Mat> MATRICE_chanel;
//            cv::split(MATRICE, MATRICE_chanel);
//               normalize(MATRICE_chanel[1],MATRICE_chanel[1],0.0,1.0,NORM_MINMAX);
//               normalize(MATRICE_chanel[2],MATRICE_chanel[2],0.0,1.0,NORM_MINMAX);
//               merge(MATRICE_chanel,MATRICE);

//        }else{
//            for(int i=0;i<cornersC.size();i++){
//                cornersA.push_back(cornersC[i]);
//            }
//            cornersC.clear();
//        }
        for(int y = 0 ; y < imgB.rows ;  y = y +pixels){
            for(int x = 0 ; x < imgB.cols ;  x = x +pixels){
                Vec3b intensite1= imgB.at<Vec3b>(y,x);
                //if (intensite1.val[0]!=0 && intensite1.val[1]!=0 && intensite1.val[2]!=0){
                    cornersB.push_back(Point(x,y));
                //}
            }
        }
float somme=0;
        std::vector<float> feature_errors;
        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size),1, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 30, 0.01),0);

        //        for(int i=0;i<cornersB.size();i++){
        //            cornersC.push_back(cornersB[i]);
        //        }

        int compteur_colonnes=0;
        float max=0,min=1000000, max_x=0,max_y=0;

        float A,A1,B,C;
        int y=0;
        int k=0;
        int u=0;
        vector<float>distances;
        for( int i=0; i < features_found.size(); i++ ){
            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
            double deplacement = (double)sqrt((p0.x-p1.x)*(p0.x-p1.x)+(p0.y-p1.y)*(p0.y-p1.y));
            double deplacementX=(double)sqrt((p0.x-p1.x)*(p0.x-p1.x) );
            double deplacementY=(double)sqrt((p0.y-p1.y)*(p0.y-p1.y) );

            A=deplacement;

            A1=(float)deplacement;
            B=(float)deplacementX;
            C=(float)deplacementY;
//

            somme=somme+A;
            distances.push_back(A);
            if(A>max){
                max=A;
            }
            if(A<min){
                min=A;
            }


            MATRICE.at<float>(i,0)=A;
            u=k;
            int k=u+pixels;
            if(compteur_colonnes==(int)imgA.cols/pixels){
                compteur_colonnes=0;
            }else{
                compteur_colonnes++;
            }
        }
int moy=(int)(somme/features_found.size());
      int indice554=0;
      cout<< moy<<endl;
       cout<< "moy"<<endl;
      Mat MATRICE555((int)(imgA.rows/pixels),(int)(imgA.cols/pixels),CV_32F);
      Mat MATRICE444((int)(imgA.rows/pixels),(int)(imgA.cols/pixels),CV_8UC1);
        for(int y = 0 ; y < MATRICE555.rows ; y++){
            for(int x = 0 ; x < MATRICE555.cols ; x++){
              MATRICE555.at<float>(y,x)=(float)MATRICE.at<float>(indice554,0);
              indice554++;

            }
        }
       cout<<"MATRICE444"<<endl;
        MATRICE555.convertTo(MATRICE444, CV_8UC1);
       cout<<"MATRICE4441"<<endl;
        threshold(MATRICE444,MATRICE444,0,moy,THRESH_BINARY|THRESH_OTSU);
            cout<<"MATRICE4442"<<endl;
   MATRICE444.convertTo(MATRICE555, CV_32F);
   float moy1=(float)(somme/features_found.size());
   cout<<"MATRICE4444"<<endl;
   cout<<"size de features"<<endl;
   cout<< features_found.size()<<endl;
          cout<< moy1<<endl;
          vector<float> disto;
          cout<<"1"<<endl;
          float somvar=0;
          for(int i=0; i<distances.size();i++){
            somvar=somvar+sqrt( (distances[i]-moy1)*(distances[i]-moy1));
            disto.push_back(sqrt((distances[i]-moy1)*(distances[i]-moy1)));
          }
          cout<<"t2"<<endl;
          float var=0;
          var=(float)(somvar/distances.size());
          float somoy=0;
          int compteur_d_outlayer=0;
          for(int i=0; i<distances.size();i++){
              if(disto[i]>var){
                  disto[i]= moy1;
                  compteur_d_outlayer++;
              }else{
                  disto[i]=distances[i];
              }
              somoy=somoy+disto[i];
          }
          disto.clear();
          cout<<"nombred_outlayers"<<endl;
          float pourcentage_outlayers=(float)((float)compteur_d_outlayer/(float)features_found.size());
          cout<<pourcentage_outlayers<<endl;
          cout<<"t10"<<endl;
          dt=(float)(((float)(somoy/distances.size()))/allImages.size());
          cout<<"11"<<endl;
          distances.clear();
          cout<<"dt"<<endl;
          cout<<dt<<endl;
          cout<<"t11"<<endl;
          cout <<"deplacement"<<endl;
          cout<<min<<endl;
          cout<<max<<endl;
          int indice_57=0;
          for(int y = 0 ; y < MATRICE444.rows ;  y ++){
            for(int x = 0 ; x < MATRICE444.cols ;  x ++){
                if(MATRICE555.at<float>(y,x)==0.0){
                  MATRICE.at<float>(indice_57,0)=0;

              }
                    //cout<<MATRICE.at<float>(indice_57,0)<<" ";
              indice_57++;
            }
//            cout<<" "<<endl;
        }

MATRICE555.release();
MATRICE444.release();

        cout<<"t12"<<endl;
        Mat img55  (imgA.rows, imgA.cols, CV_32F);

        int indice1=0;
        for(int y = 0 ; y < imgB.rows ;  y = y +pixels){
            for(int x = 0 ; x < imgB.cols ;  x = x +pixels){
                img55.at<float>(y,x)=MATRICE.at<float>(indice1,0);
                indice1++;
                        //}
            }
        }


        cout<<"entrée"<<endl;








        Rect const roi_initial_location((int)imgA.cols/2,(int)imgA.rows/2,(int) imgA.cols/2, (int)imgA.rows/2);
         cv::Mat roi =  img55(roi_initial_location).clone();
         //mean shift
         cv::TermCriteria criteria(cv::TermCriteria::COUNT +
                                     cv::TermCriteria::EPS,
                                     10, 0.01);




         cv::Rect mean_shift_window = roi_initial_location;
                cv::meanShift( img55, mean_shift_window, criteria);
                float r=0, g =0, b=0;
                float H = 0;

                Mat Distms(img55.rows, img55.cols, CV_8UC3);
                normalize(img55,img55,0,360,NORM_MINMAX);
                for(int y = 0 ; y < img55.rows ;  y = y +pixels){
                    for(int x= 0 ; x < img55.cols ;  x = x +pixels){
                if(img55.at<float>(y,x)!=0){
                H =(float) img55.at<float>(y,x);
                LucasKanadeCarteDeChaleur *carte = new LucasKanadeCarteDeChaleur();

                carte->HSVtoRGB(&r, &g, &b, H);
                 rectangle(Distms, Rect(x, y,pixels,pixels),Scalar(b *255,g *255,r *255),-1 );
                }else{

                    rectangle(Distms, Rect(x, y,pixels,pixels),Scalar(0,0,0),-1 );
                }
                }

                    }
                //merge(hsv_channels,img55);

        //        //normalisation min max
        //        normalize(MATRICE.col(1),MATRICE.col(1),min,max,NORM_MINMAX);
        //         normalize(MATRICE.col(2),MATRICE.col(2),min,max,NORM_MINMAX);
                imwrite(cv::format("/home/aissa/Bureau/Meanshift%d.tif", 1).c_str(), Distms);
                roi.release();
                img55.release();

//Mat img55;
////cvtColor(img55,img55, CV_BGR2HSV);

//        Mat Matrice1;
//Rect const roi_initial_location(640, 360, 640, 360);
// cv::Mat roi =  img(roi_initial_location).clone();

// cv::TermCriteria criteria(cv::TermCriteria::COUNT +
//                             cv::TermCriteria::EPS,
//                             10, 0.01);
// cv::Rect mean_shift_window = roi_initial_location;
//        cv::meanShift( img, mean_shift_window, criteria);
//        //merge(hsv_channels,img55);

//        //normalisation min max
         normalize(MATRICE.col(1),MATRICE.col(1),min,max,NORM_MINMAX);
         normalize(MATRICE.col(2),MATRICE.col(2),min,max,NORM_MINMAX);
         normalize(MATRICE.col(3),MATRICE.col(3),min,max,NORM_MINMAX);



          //normalize(MATRICE,MATRICE,0.0,1.0,NORM_MINMAX);

//         imwrite(cv::format("/home/aissa/Bureau/Meanshift%d.tif", 1).c_str(), img);
//
        Kmeans_1D(imgA,MATRICE,nouveauDossier,traitement,pixels,centers1,ind_k);
//

        cout<<"sorti"<<endl;

    }else{
        compt++;
    }

MATRICE.release();
MATRICE_2.release();



///////////////////////////

    //The End of part 1

//////////////////////////



int size = 0; bool premiere_trame=true;
int size2=(int)(features_found.size() * (allImages.size()-1));
Mat MATRICE_1;
MATRICE_1=Mat::zeros(size2, 5, CV_32F);
cout<<"ici"<<endl;
std::vector<cv::Point2f> cornersA;
//cornersA.reserve(maxCorners);
std::vector<cv::Point2f> cornersB;
int indice_3=0;
cout<<"ici14"<<endl;
double max=0,min=180000;
for(int m = 1;m <allImages.size();m++){

    cout<<"ici"<<m<<endl;
    bool seuil=true;
    ofstream fichier ("/home/aissa/Bureau/Deplacement.txt", ios::out | ios::app);
    ofstream fichier1("/home/aissa/Bureau/Delacement_axe_X.txt", ios::out | ios::app);
    ofstream fichier2("/home/aissa/Bureau/Delacement_axe_Y.txt", ios::out | ios::app);
    Mat binary;
    std::vector < std::vector<cv::Point2i > > blobs;
    imgA = allImages[m-1];

    //imgC = Mat::zeros(imgA.size(), CV_8UC3);
    //imgC = cv::Scalar(0,0,0);
    //dist1 = Mat::zeros(imgA.size(), imgA.type());
    //cvtColor(imgA, dist1, CV_RGB2GRAY);
    imgB = allImages[m];
    dist1 = Mat::zeros(imgA.size(), imgA.type());
    dist2 = Mat::zeros(imgB.size(), imgB.type());
    dist4 = Mat::zeros(imgA.size(),imgB.type());
    cvtColor(imgA, dist1, CV_RGB2GRAY);
    cvtColor(imgB, dist2, CV_RGB2GRAY);
     //imwrite(cv::format((nouveauDossier+"/"+traitement +"/blured/frame%d.tif").c_str(), m).c_str(), dist4);
    if(cv::countNonZero(dist1) !=0 && cv::countNonZero(dist2)!=0){
         vector<cv::Vec4i> distanceImage;
         int win_size= positionw;
         //nombre maximal de corners
         //int maxCorners = 2000;
         //int maxCorners = INT_MAX;
         cornersA.clear();
         cornersB.clear();
         std::vector<cv::Mat> BGR_channels;
         cv::split(imgA, BGR_channels);
         cv::Mat B_image = BGR_channels[0];
         cv::Mat G_image = BGR_channels[1];
         cv::Mat R_image = BGR_channels[2];
         std::vector<cv::Mat> hsv_channels;
         cv::split(imgA, hsv_channels);
         cv::Mat h_image = hsv_channels[0];
         cv::Mat s_image = hsv_channels[1];
         cv::Mat v_image = hsv_channels[2];

//         if (premiere_fois==true){
             for(int y = 0 ; y < imgA.rows ; y = y + pixels){
                 for(int x = 0 ; x < imgA.cols ; x = x +pixels){
                     Vec3b intensite = imgA.at<Vec3b>(y,x);
                     //if (intensite.val[0]!=0 && intensite.val[1]!=0 && intensite.val[2]!=0){

                         cornersA.push_back(Point(x,y));
                         MATRICE_1.at<float>(indice_3,2)=x/imgA.cols;
                         MATRICE_1.at<float>(indice_3,3)=y/imgA.rows;

                         // MATRICE.at<float>(indice,1)=(float)(h_image.at<uchar>(y,x)*2);
                         //                     MATRICE.at<float>(indice,1)=(float)s_image.at<uchar>(y,x);
                                              MATRICE_1.at<float>(indice_3,4)=(float)s_image.at<uchar>(y,x)/255;



                        // MATRICE_1.at<float>(indice_3,4)=(float)B_image.at<uchar>(y,x)/255;
//                         MATRICE_1.at<float>(indice_3,5)=(float)G_image.at<uchar>(y,x)/255;
//                         MATRICE_1.at<float>(indice_3,6)=(float)R_image.at<uchar>(y,x)/255;
                            indice_3++;
                         //}
                 }
             }
      //   premiere_fois=false;


////    }else{
//             for(int i=0;i<cornersC.size();i++){
//                 cornersA.push_back(cornersC[i]);
//             }
//             cornersC.clear();
//         }
               cout<<"ici1"<<endl;
         for(int y = 0 ; y < imgB.rows ;  y = y +pixels){
             for(int x = 0 ; x < imgB.cols ;  x = x +pixels){
                 Vec3b intensite1= imgB.at<Vec3b>(y,x);

                     cornersB.push_back(Point(x,y));

             }
         }

         std::vector<float> feature_errors;

         calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size),1, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 30, 0.01),0);


//         for(int i=0;i<cornersB.size();i++){
//             cornersC.push_back(cornersB[i]);
//         }

  double  max_x=0,max_y=0;


         int compteur_colonnes=0;

         float A,A1,B,C;
         int y=0;
         int k;
         int u=0;
int moy2=0;
float somme2=0;
         for( int i=0; i < features_found.size(); i++ ){
             if(i==0){
                 fichier<<""<<endl;
                 fichier<<"image " <<m<<" "<<endl;
                 fichier1<<""<<endl;
                 fichier1<<"image " <<m<<" "<<endl;
                 fichier2<<""<<endl;
                 fichier2<<"image " <<m<<" "<<endl;
             }

             Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
             Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
             Vec4i p01(p0.x, p0.y, p1.x, p1.y);

             //double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
             //if(dist_euclidienne>=0){
             int dist_euclidienne_int = (int)sqrt((p0.x-p1.x)*(p0.x-p1.x)+(p0.y-p1.y)*(p0.y-p1.y));
             double deplacement = (double)sqrt((p0.x-p1.x)*(p0.x-p1.x)+(p0.y-p1.y)*(p0.y-p1.y));

             double deplacementX=(double)sqrt((p0.x-p1.x)*(p0.x-p1.x) );
             double deplacementY=(double)sqrt((p0.y-p1.y)*(p0.y-p1.y) );




             //A=(float)deplacement/max;
             A=(float)deplacement;
//             A1=(float)deplacement/max;
             //B=(float)deplacementX/max_x;
             //C=(float)deplacementY/max_y;
             B=(float)deplacementX;
             C=(float)deplacementY;

                somme2=somme2+A;
             label=distance((int)deplacement, m, centers1,(int)((taillevideo/2)-1));

             if(premiere_trame==true){
                 if(A>max){
                     max=A;
                 }
                 if(A<min){
                     min=A;
                 }
                 Labels.push_back(label);
                 MATRICE_1.at<float>(i,0)=A;
                 MATRICE_1.at<float>(i,1)=(float)(m+1)*dt;
             }else{
                 if(A>max){
                     max=A;
                 }
                 if(A<min){
                     min=A;
                 }
                 Labels.push_back(label);
                 MATRICE_1.at<float>(i+size,0)=A;
                 MATRICE_1.at<float>(size+i,1)=(float)(m+1)*dt;

             }
             u=k;

             int k=u+pixels;

             if(A>80&&A<250&&seuil==true){
             seuil=false;
                 fichier61<<m+1<<endl;
                 fichier62<<A<<endl;


             }























             fichier<<A<<" ";
             fichier1<<B<<" ";
             fichier2<<C<<" ";
             nombre_dist++;
             map<int,int>::iterator search = histogramme.find(dist_euclidienne_int);
             distanceImage.push_back(p01);
             if(search != histogramme.end()) {
             //std::cout << "Found avant" << search->first << " " << search->second << '\n';
             search->second++;
             //std::cout << "Found apres" << search->first << " " << search->second << '\n';
             }else{
             //std::cout << "Not found\n";
             histogramme.insert(pair<int,int>(dist_euclidienne_int, 1));
             }

             if(compteur_colonnes==(int)imgA.cols/pixels){
                 fichier<<""<<endl;
                 fichier1<<""<<endl;
                 fichier2<<""<<endl;
                 compteur_colonnes=0;
             }else{
                 compteur_colonnes++;
             }
         }










         moy2=(int)(somme2/features_found.size());
               int indice5541=0;
               cout<< moy2<<endl;
                cout<< "moy"<<endl;
               Mat MATRICE5551((int)(imgA.rows/pixels),(int)(imgA.cols/pixels),CV_32F);
               Mat MATRICE4441((int)(imgA.rows/pixels),(int)(imgA.cols/pixels),CV_8UC1);
                 for(int y = 0 ; y < MATRICE5551.rows ; y++){
                     for(int x = 0 ; x < MATRICE5551.cols ; x++){
                       MATRICE5551.at<float>(y,x)=(float)MATRICE_1.at<float>(indice5541+size,0);
                       indice5541++;

                     }
                 }
                cout<<"MATRICE444"<<endl;
                 MATRICE5551.convertTo(MATRICE4441, CV_8UC1);
                cout<<"MATRICE4441"<<endl;
                 threshold(MATRICE4441,MATRICE4441,0,moy2,THRESH_BINARY|THRESH_OTSU);
                     cout<<"MATRICE4442"<<endl;
            MATRICE4441.convertTo(MATRICE5551, CV_32F);

            int indice_571=0;
                    for(int y = 0 ; y < MATRICE4441.rows ;  y ++){
                        for(int x = 0 ; x < MATRICE4441.cols ;  x ++){



                            if(MATRICE5551.at<float>(y,x)==0.0){
                              MATRICE_1.at<float>(indice_571+size,0)=0;

                          }
                                //cout<<MATRICE.at<float>(indice_57,0)<<" ";
                          indice_571++;
                        }
            //            cout<<" "<<endl;
                    }




         size=size+features_found.size();

         premiere_trame=false;

         cout<<"sorti"<<endl;
         allDistances.push_back(distanceImage);
     }else{
         compt++;
     }

     fichier.close();
     fichier1.close();
     fichier2.close();
 }
//string commande = "python /home/aissa/Bureau/from_armand/courbe.py";
// system(commande.c_str());
//
cout<<"labels size"<<endl;
cout<<(int)(Labels.size()/9)<<endl;
Mat MATRICE_0;
//std::vector<cv::Mat> MATRICE1_chanel;
//cv::split(MATRICE_1, MATRICE1_chanel);
//   normalize(MATRICE1_chanel[2],MATRICE1_chanel[2],0.0,1.0,NORM_MINMAX);
//   normalize(MATRICE1_chanel[3],MATRICE1_chanel[3],0.0,1.0,NORM_MINMAX);
//   merge(MATRICE1_chanel,MATRICE_1);
//normalisation min max

normalize(MATRICE_1.col(3),MATRICE_1.col(3),min,max,NORM_MINMAX);
 normalize(MATRICE_1.col(2),MATRICE_1.col(2),min,max,NORM_MINMAX);
  normalize(MATRICE_1.col(4),MATRICE_1.col(4),min,max,NORM_MINMAX);
//   normalize(MATRICE_1.col(5),MATRICE_1.col(5),min,max,NORM_MINMAX);
//    normalize(MATRICE_1.col(6),MATRICE_1.col(6),min,max,NORM_MINMAX);
 //normalize(MATRICE_1.col(1),MATRICE_1.col(1),min,max,NORM_MINMAX);
//normalize(MATRICE_1,MATRICE_0,0.0,1.0,NORM_MINMAX);
 Kmeans_ND(allImages,Labels,features_found.size(),imgA,MATRICE_1,nouveauDossier,traitement,pixels, centers1,ind_k);
//

MATRICE_0.release();
MATRICE_1.release();
//modifié *0.95
//int nombre_dist_reduit = nombre_dist*0.95;
int nombre_dist_reduit = nombre_dist;
//cout << "nombre de dist : " << nombre_dist <<endl;
//cout << "95% du nombre de dist : " << nombre_dist_reduit <<endl;
int somme = 0;
int derniere_valeur = 0;
for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it){
    somme = somme + it->second;
    if(somme >= nombre_dist_reduit){
        derniere_valeur = it->first;
        break;
        }
}
t=0;
cout<<"oui"<<endl;
for(int m =0 ; m < allDistances.size() ; m++){
    int compteur=0;
    imgC = Mat::zeros(imgA.size(), CV_8UC3);
        //à modifier
        imgC=cv::Scalar(255,255,255);
        vector<Vec4i> distanceImage = allDistances[m];
        for(int i=0; i < distanceImage.size(); i++){
            Vec4i p01 = distanceImage[i];
            Point p0(p01[0], p01[1]);
            Point p1(p01[2], p01[3]);
            int dist_euclidienne = (int)sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            if(dist_euclidienne<= derniere_valeur){
                line( imgC, p0, p1, cv::Scalar(0,255,0),1, CV_AA,0);
                // }
                Scalar bleu = Scalar(255,0,0);
                Scalar red = Scalar(0,0,255);
                Scalar jaune = Scalar(0,255,255);
                cv::circle(imgC, Point(p0.x,p0.y),1, red, 1);
                cv::circle(imgC, Point(p1.x,p1.y), 1, bleu, 1);
                if(p0.x==p1.x&&p0.y==p1.y){
                    cv::circle(imgC,Point(p0.x,p0.y),1,jaune,1);
                }
                compteur++;
            }
        }

        distanceImage.clear();

        img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), position+m+t).c_str(), CV_LOAD_IMAGE_UNCHANGED);
        dist3 = Mat::zeros(img.size(), img.type());

        cvtColor(img, dist3, CV_RGB2GRAY);
        if(cv::countNonZero(dist3)==0){
            int t1=0;
            while(true){
                if(m+t+t1==allDistances.size()){
                    t+=t1;
                    t1=0;
                    break;
                }
                img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), position+m+t+t1).c_str(), CV_LOAD_IMAGE_UNCHANGED);
                dist3 = Mat::zeros(img.size(), img.type());
                cvtColor(img, dist3, CV_RGB2GRAY);
                if(cv::countNonZero(dist3)!= 0){
                    imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t+t1).c_str(), img);
                    imwrite(cv::format((nouveauDossier + "/" + traitement + "/FlotOptique/frame%d.tif").c_str(), position+m).c_str(), imgC);
                    imwrite(cv::format((nouveauDossier + "/" + traitement + "/FlotOptique/resize/frame%d.png").c_str(), position+m).c_str(), imgC);
                    dist = Mat::zeros(imgC.size(), CV_8UC3);
                    addWeighted(img, 0.5, imgC, 0.5, 0.0, dist);

                    if(dist.cols>768 && dist.rows>576){
                        cv::resize(dist, dst,imgref.size());
                        imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m+t+t1+1).c_str(), dst);
                    }
                    imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t+t1+1).c_str(), dist);
                    t1++;
                    t1=0;
                    break;
                }

                if(img.cols>768 && img.rows>576){
                    cv::resize(img, dst,imgref.size());
                    imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m+t+t1+1).c_str(), dst);
                }
                imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t+t1).c_str(), img);
                t1++;
            }
        }else{
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/FlotOptique/frame%d.tif").c_str(), position+m).c_str(), imgC);
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/FlotOptique/resize/frame%d.png").c_str(), position+m).c_str(), imgC);
            dist = Mat::zeros(imgC.size(), CV_8UC3);
            addWeighted(img, 0.5, imgC, 0.5, 0.0, dist);
            if(dist.cols>768 && dist.rows>576){
                cv::resize(dist, dst,imgref.size());
                imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m+t).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t).c_str(), dist);
        }
    }
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    fichier66<<"temps de calcul: " <<temps<<" "<<endl;
    fichier66.close();
    allDistances.clear();
    allImages.clear();
    imgA.release();
    imgB.release();
    imgC.release();
    img.release();
    dist.release();
    dist1.release();
    dist2.release();
    dist3.release();
}


// code Kmeans_1D

void Analyseletk::Kmeans_1D(cv::Mat &img1,cv::Mat&confusion,string nouveauDossier,string traitement,int pixels,cv::Mat& centers,int &ind_k){
    cout<<"kmeans_1D"<<endl;
    const int MAX_CLUSTERS =ind_k;
    cout<<ind_k<<endl;
    Scalar colorTab[] ={
        Scalar(0, 0, 255),
        Scalar(0,255,0),
        Scalar(255,100,100),
        Scalar(255,0,255),
        Scalar(0,255,255),
        Scalar(255,255,0),
        Scalar(0,0,0),
        Scalar(255,255,255),
        Scalar(100,100,100),
        Scalar(0,50,50),
        Scalar(150,0,150),
        Scalar(50,0,50),
    };
    Mat img((int)img1.rows/pixels,(int)img1.cols/pixels, CV_8UC3);
    Mat dist(img1.rows,img1.cols,CV_8UC3);
    Mat labels;
    cout <<"ici"<<endl;
    kmeans(confusion,MAX_CLUSTERS, labels,TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),1, KMEANS_PP_CENTERS, centers);
    cout <<"ici2"<<endl;
    dist = Scalar::all(255);
    int size3= confusion.rows;
    int j=0;
    int k=0;
    int compteur_alpha=0;
    for(int i = 0; i <size3; i++ ){
       Point centre(0,0);
       if(compteur_alpha%img.cols==0){
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
       rectangle(dist, Rect(centre.x, centre.y,pixels,pixels),colorTab[clusterIdx],-1 );
       compteur_alpha++;
       k++;
    }
    imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans/frame%d.tif").c_str(), 1).c_str(), dist);
    cout<<"centers"<<endl;
    cout<<centers<<endl;
    img.release();
    dist.release();
    all_Images.clear();
    confusion.release();
    //centers.release();
    //centers1.release();
}




//code Kmeans_ND
void Analyseletk::Kmeans_ND(vector<Mat>allImages,std::vector<int>&labels,int size_of_features,cv::Mat &img1,cv::Mat&confusion,string nouveauDossier, string traitement,int pixels,cv::Mat&centers1,int &ind_k){
    const int MAX_CLUSTERS =ind_k;
    Scalar colorTab[] ={
        Scalar(0, 0, 255),
        Scalar(0,255,0),
        Scalar(255,100,100),
        Scalar(255,0,255),
        Scalar(0,255,255),
        Scalar(255,255,0),
        Scalar(0,0,0),
        Scalar(255,255,255),
        Scalar(100,100,100),
        Scalar(0,50,50),
        Scalar(150,0,150),
        Scalar(50,0,50),
    };
    int size_1=0;
    Mat img((int)img1.rows/pixels,(int)img1.cols/pixels, CV_8UC3);
    Mat dist(img1.rows,img1.cols,CV_8UC3);
    Mat centers;
    kmeans(confusion,MAX_CLUSTERS, labels,TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),3, KMEANS_USE_INITIAL_LABELS, centers);
    dist = Scalar::all(255);
    for(int m = 0; m <allImages.size()-1; m++){
        int j=0;
        int k=0;
        int compteur_alpha=0;
        for(int i = 0; i <size_of_features; i++ ){
            Point centre(0,0);
            if (compteur_alpha%img.cols==0){
                j++;
                k=0;
                compteur_alpha=0;
            }
            int clusterIdx = labels[size_1];
            if(k==0&&j!=0){centre.x=k;centre.y=(j*pixels);}
            if(k!=0&&j==0){centre.x=k*pixels;centre.y=j;}
            if(k==0&&j==0){centre.x=k;centre.y=j;}
            if(k!=0&&j!=0){centre.x=k*pixels;centre.y=j*pixels;}
            //circle( dist, centre, 4, colorTab[clusterIdx], 5, CV_AA);
            rectangle(dist, Rect(centre.x, centre.y,pixels,pixels),colorTab[clusterIdx],-1 );
            compteur_alpha++;
            k++;
            size_1++;
        }
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans2d/frame%d.tif").c_str(), m).c_str(), dist);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans2d/resize/frame%d.tif").c_str(), m).c_str(), dist);
    }
    img.release();
    dist.release();
    centers.release();
    confusion.release();
    labels.clear();
}


// Code Trouver des blobs

//void Analyseletk::FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs){
//    blobs.clear();
//    cv::Mat label_image;
//    binary.convertTo(label_image, CV_32SC1);
//    int label_count = 2;
//    for(int y=0; y < label_image.rows; y++) {
//        int *row = (int*)label_image.ptr(y);
//        for(int x=0; x < label_image.cols; x++) {
//            if(row[x] != 1) {
//                continue;
//            }
//            cv::Rect rect;
//            cv::floodFill(label_image, cv::Point(x,y), label_count, &rect, 0, 0, 4);
//            std::vector <cv::Point2i> blob;
//            for(int i=rect.y; i < (rect.y+rect.height); i++) {
//                int *row2 = (int*)label_image.ptr(i);
//                for(int j=rect.x; j < (rect.x+rect.width); j++) {
//                    if(row2[j] != label_count) {
//                        continue;
//                    }
//                    blob.push_back(cv::Point2i(j,i));
//                }
//            }
//            blobs.push_back(blob);
//            label_count++;
//        }
//    }
//}

// code calcul de la distance
int Analyseletk::distance(int x,int frame, Mat centers1,int midle_size){
    double distance_av=1920000000.0;
    int label=0;
    double distance=0;
    for(int i=0;i<centers1.rows;i++){
        distance=(double) sqrt((((x-centers1.at<int>(i,0))*(x-centers1.at<int>(i,0))))+((((int)midle_size*dt)-(dt*(frame)))*(((int)midle_size*dt)-(dt*(frame)))));
        if (distance < distance_av){
            label=i;
            distance_av=distance;
        }
    }
    centers1.release();
    return label;
}

//code centre de gravité du Nuage pour évaluation

Point3d Analyseletk::barycentre_nuage(vector<cv::Point2i>b,int m){
    int somme_x=0,somme_y=0,N=0,somme_t=0;
    for(int y=0;y<m;y++){
        for(int i=0;i<b.size();i++){
            somme_x+=(int)b[i].x;
            somme_y+=(int)b[i].y;
            somme_t+=(int)m*10;
            N++;
        }
    }
    cv::Point3d ctr_gravite((int)(somme_x/N),(int)(somme_y/N),(int)(somme_t/N));
    return ctr_gravite;
}
