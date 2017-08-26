#include "analyseletk.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Clustering.h"

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
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/FlotOptique");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/FlotOptique/PNG");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans2d");
           Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans2d/resize");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/blured");
    }

    int size1=0;
       Mat imgA1 = allImages[(int)(taillevideo/2)];
    for(int y = 0 ; y < imgA1.rows ; y = y + pixels){
        for(int x = 0 ; x < imgA1.cols ; x = x +pixels){
           size1++;
        }
    }
    cout<<size1<<endl;
    Mat MATRICE(size1, 1, CV_32F);
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
    moyenne_de_fenetre(B_image,1 /*1=>kernel5*5, 2==kernel3*3*/ );
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
        cv::split(img_hsv, hsv_channels);
        cv::Mat h_image = hsv_channels[0];
        cv::Mat s_image = hsv_channels[1];
        cv::Mat v_image = hsv_channels[2];
        int indice=0;
        cornersA.clear();
        cornersB.clear();
//        if (premiere_fois==true){
            for(int y = 0 ; y < imgA.rows ; y = y + pixels){
                for(int x = 0 ; x < imgA.cols ; x = x +pixels){
                    Vec3b intensite = imgA.at<Vec3b>(y,x);
                   //if (intensite.val[0]!=0 && intensite.val[1]!=0 && intensite.val[2]!=0){
                    cornersA.push_back(Point(x,y));
//                     MATRICE.at<float>(indice,1)=(float)(h_image.at<uchar>(y,x)*2);
//                     MATRICE.at<float>(indice,1)=(float)s_image.at<uchar>(y,x);
//                     MATRICE.at<float>(indice,1)=(float)v_image.at<uchar>(y,x);

                       //couleur moyenne pour un
//                       MATRICE.at<float>(indice,1)=(float)B_image.at<uchar>(y,x);
//                       MATRICE.at<float>(indice,1)=(float)G_image.at<uchar>(y,x);
//                       MATRICE.at<float>(indice,1)=(float)R_image.at<uchar>(y,x);
//                       MATRICE.at<float>(indice,3)=(float)imgA.at<Vec3b>(y,x).val[0];
//                       MATRICE.at<float>(indice,3)=(float)imgA.at<Vec3b>(y,x).val[1];
//                       MATRICE.at<float>(indice,3)=(float)imgA.at<Vec3b>(y,x).val[2];
//                       cout<<(int)imgA.at<Vec3b>(y,x).val[1]<<endl;
//                       cout<<"hue"<<endl;
//                       cout<<(float)h_image.at<uchar>(y,x)<<endl;
//                       cout<<(float)s_image.at<uchar>(y,x)<<endl;
//                       cout<<(float)v_image.at<uchar>(y,x)<<endl;
                    //}
                indice ++;
                }
            }
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
        std::vector<float> feature_errors;
        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size),1, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 30, 0.01),0);
//        for(int i=0;i<cornersB.size();i++){
//            cornersC.push_back(cornersB[i]);
//        }
        int compteur_colonnes=0;
        double max=0, max_x=0,max_y=0;
        float A,A1,B,C;
        int y=0;
        int k=0;
        int u=0;

cout<<features_found.size();



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
            cout<<"A"<<endl;
            cout<<A<<endl;
            MATRICE.at<float>(i,0)=A;
            u=k;
            int k=u+pixels;
            if(compteur_colonnes==(int)imgA.cols/pixels){
                compteur_colonnes=0;
            }else{
                compteur_colonnes++;
            }
        }

        cout<<"entrée"<<endl;


        //normalisation min max
        normalize(MATRICE,MATRICE_2,0.0,1.0,NORM_MINMAX);
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
MATRICE_1=Mat::zeros(size2, 2, CV_32F);
cout<<MATRICE_1.cols<<endl;
cout<<MATRICE_1.rows<<endl;

std::vector<cv::Point2f> cornersA;
//cornersA.reserve(maxCorners);
std::vector<cv::Point2f> cornersB;
for(int m = 1;m <allImages.size();m++){
    ofstream fichier ("/home/aissa/Bureau/Deplacement.txt", ios::out | ios::app);
    ofstream fichier1("/home/aissa/Bureau/Delacement_axe_X.txt", ios::out | ios::app);
    ofstream fichier2("/home/aissa/Bureau/Delacement_axe_Y.txt", ios::out | ios::app);
    Mat binary;
    std::vector < std::vector<cv::Point2i > > blobs;
    imgA = allImages[m-1];
    cout<< imgA.size()<<endl;
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


//         if (premiere_fois==true){
             for(int y = 0 ; y < imgA.rows ; y = y + pixels){
                 for(int x = 0 ; x < imgA.cols ; x = x +pixels){
                     Vec3b intensite = imgA.at<Vec3b>(y,x);
                     //if (intensite.val[0]!=0 && intensite.val[1]!=0 && intensite.val[2]!=0){
                         cornersA.push_back(Point(x,y));
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
         for(int y = 0 ; y < imgB.rows ;  y = y +pixels){
             for(int x = 0 ; x < imgB.cols ;  x = x +pixels){
                 Vec3b intensite1= imgB.at<Vec3b>(y,x);

                     cornersB.push_back(Point(x,y));

             }
         }

         std::vector<float> feature_errors;
         cout<<"optical flow"<<endl;
         calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size),1, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 30, 0.01),0);

         cout<<features_found.size()<<endl;
//         for(int i=0;i<cornersB.size();i++){
//             cornersC.push_back(cornersB[i]);
//         }

  double max=0, max_x=0,max_y=0;


         int compteur_colonnes=0;

         float A,A1,B,C;
         int y=0;
         int k;
         int u=0;

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


             label=distance((int)deplacement, m, centers1,(int)((taillevideo/2)-1));

             if(premiere_trame==true){
                 Labels.push_back(label);
                 MATRICE_1.at<float>(i,0)=A;
                 MATRICE_1.at<float>(i,1)=(float)(m+1)*10;
             }else{
                 Labels.push_back(label);
                 MATRICE_1.at<float>(i+size,0)=A;
                 MATRICE_1.at<float>(size+i,1)=(float)(m+1)*10;

             }
             u=k;

             int k=u+pixels;
             fichier<<A1<<" ";
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
         size=size+features_found.size();
         cout<<"deplacement6"<<endl;
         premiere_trame=false;
         cout<<"deplacement7"<<endl;
         cout<<"sorti"<<endl;
         allDistances.push_back(distanceImage);
     }else{
         compt++;
     }

     fichier.close();
     fichier1.close();
     fichier2.close();
 }

//
cout<<"labels size"<<endl;
cout<<(int)(Labels.size()/9)<<endl;
Mat MATRICE_0;

//normalisation min max
normalize(MATRICE_1,MATRICE_0,0.0,1.0,NORM_MINMAX);
 Kmeans_ND(allImages,Labels,features_found.size(),imgA,MATRICE_0,nouveauDossier,traitement,pixels, centers1,ind_k);
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
        cout << "somme : " << somme << endl;
        if(somme >= nombre_dist_reduit){
            derniere_valeur = it->first;
            cout <<"derniere valeur: " << derniere_valeur << endl;
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
        cout<<"oui"<<endl;
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
                    imwrite(cv::format((nouveauDossier + "/" + traitement + "/FlotOptique/PNG/frame%d.png").c_str(), position+m).c_str(), imgC);
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
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/FlotOptique/PNG/frame%d.png").c_str(), position+m).c_str(), imgC);
            dist = Mat::zeros(imgC.size(), CV_8UC3);
            addWeighted(img, 0.5, imgC, 0.5, 0.0, dist);
            if(dist.cols>768 && dist.rows>576){
                cv::resize(dist, dst,imgref.size());
                imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m+t).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t).c_str(), dist);
        }
    }
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
    t=0;
}





























// code Kmeans_1D

void Analyseletk::Kmeans_1D(cv::Mat &img1,cv::Mat&confusion,string nouveauDossier,string traitement,int pixels,cv::Mat& centers,int &ind_k){
    cout<<"kmeans_1D"<<endl;
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

    Mat img((int)img1.rows/pixels,(int)img1.cols/pixels, CV_8UC3);

    Mat dist(img1.rows,img1.cols,CV_8UC3);

    Mat labels;



    kmeans(confusion,MAX_CLUSTERS, labels,TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),1, KMEANS_PP_CENTERS, centers);

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
       rectangle(dist, Rect(centre.x, centre.y,10,10),colorTab[clusterIdx],-1 );
       compteur_alpha++;
       k++;
   }
   imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans/frame%d.tif").c_str(), 1).c_str(), dist);
   cout<<"centers"<<endl;
   cout<<centers<<endl;
   img.release();
   dist.release();
   //centers.release();
// centers1.release();
}




//code Kmeans_ND
void Analyseletk::Kmeans_ND(vector<Mat>allImages,std::vector<int>&labels,int size_of_features,cv::Mat &img1,cv::Mat&confusion,string nouveauDossier, string traitement,int pixels,cv::Mat&centers1,int &ind_k){
    cout<<"kmeans_ND"<<endl;
    const int MAX_CLUSTERS =ind_k;
    Scalar colorTab[] ={
        Scalar(0, 0, 255),
        Scalar(0,255,0),
        Scalar(255,100,100),
        Scalar(255,0,255),
        Scalar(0,255,255),
        Scalar(255,255,0),
        //Scalar(0,0,0),
        //Scalar(255,255,255),
        //Scalar(100,100,100),
        //Scalar(0,50,50),
        //Scalar(150,0,150),
        //Scalar(50,0,50),
    };

    int size_1=0;
    Mat img((int)img1.rows/pixels,(int)img1.cols/pixels, CV_8UC3);
    Mat dist(img1.rows,img1.cols,CV_8UC3);

    Mat centers;
    kmeans(confusion,MAX_CLUSTERS, labels,TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),3, KMEANS_USE_INITIAL_LABELS, centers);
    cout<<"###########labels############"<<endl;
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
        rectangle(dist, Rect(centre.x, centre.y,10,10),colorTab[clusterIdx],-1 );
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
        distance=(double) sqrt((((x-centers1.at<int>(i,0))*(x-centers1.at<int>(i,0))))+((((int)midle_size*100)-(10*(frame)))*(((int)midle_size*100)-(10*(frame)))));
        if (distance < distance_av){
            label=i;
            distance_av=distance;
        }
    }
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
