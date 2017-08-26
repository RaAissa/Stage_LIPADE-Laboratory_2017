#include "lucaskanade.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
LucasKanade::LucasKanade()
{
}
void LucasKanade::runLukasKanade(int&positionw,int&positionswitch,bool &premiere_fois,vector<Mat> allImages,int &position,int taillevideo, string nouveauDossier, string traitement){
    Mat dst;
    int pixels=positionswitch;

    Mat imgref=imread("/home/aissa/Bureau/out5/frame1.tif",CV_LOAD_IMAGE_COLOR);
    if (premiere_fois==true){
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/FlotOptique");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/FlotOptique/PNG");
        premiere_fois=false;
    }
    Mat imgA, imgB, imgC, img,img1,img2,dist,dist1,dist2,dist3,dist4,dist5;
    int nombre_dist = 0;
    map<int,int> histogramme;
    vector<vector<cv::Vec4i> > allDistances;
    int compt=0;
    for(int m = 1 ; m < allImages.size() ; m++){
        imgA = allImages[m-1];
        imgB = allImages[m];
        dist1 = Mat::zeros(imgA.size(), imgA.type());
        dist2 = Mat::zeros(imgB.size(), imgB.type());
        cvtColor(imgA, dist1, CV_RGB2GRAY);
        cvtColor(imgB, dist2, CV_RGB2GRAY);
        if(cv::countNonZero(dist1) !=0 && cv::countNonZero(dist2)!=0){
            vector<cv::Vec4i> distanceImage;
            int win_size= positionw;
            //nombre maximal de corners
            //int maxCorners = 2000;
            //int maxCorners = INT_MAX;
            std::vector<cv::Point2f> cornersA;
            // cornersA.reserve(maxCorners);
            std::vector<cv::Point2f> cornersB;
            cornersA.clear();
            cornersB.clear();
            // cornersB.reserve(maxCorners);
            for(int y = 0 ; y < imgA.rows ; y = y + pixels){
                for(int x = 0 ; x < imgA.cols ; x = x +pixels){
                  //modification apportée a lucas et kanadé
                    Vec3b intensite = imgA.at<Vec3b>(y,x);
                 // if (intensite.val[0]!=0 && intensite.val[1]!=0 && intensite.val[2]!=0){
                        cornersA.push_back(Point(x,y));
                  //}
                }
            }
            for(int y = 0 ; y < imgB.rows ;  y = y +pixels){
                for(int x = 0 ; x < imgB.cols ;  x = x +pixels){
                   Vec3b intensite1= imgB.at<Vec3b>(y,x);
              //if (intensite1.val[0]!=0 && intensite1.val[1]!=0 && intensite1.val[2]!=0){

                  cornersB.push_back(Point(x,y));
                 // }
                }
            }
            // Call Lucas Kanade algorithm
            std::vector<uchar> features_found;
            // features_found.reserve(maxCorners);
            std::vector<float> feature_errors;
            //feature_errors.reserve(maxCorners);
            calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size),5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 30, 0.01),0);


            for( int i=0; i < features_found.size(); i++ ){
               // if((int)features_found[i]==0){
                Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
                Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
                Vec4i p01(p0.x, p0.y, p1.x, p1.y);
                //double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
                //if(dist_euclidienne>=0){
                int dist_euclidienne_int = (int) sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
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
               // }
            }
            allDistances.push_back(distanceImage);
        }else{
        compt++;
        }
    }
    //modifié *0.95
    int nombre_dist_reduit = nombre_dist;
    cout << "nombre de dist : " << nombre_dist <<endl;
    cout << "95% du nombre de dist : " << nombre_dist_reduit <<endl;
    int somme = 0;
    int derniere_valeur = 0;
    for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it){
        somme = somme + it->second;
        if(somme >= nombre_dist_reduit){
            derniere_valeur = it->first;
            break;
        }
    }
    cout<<"taille:"<<endl;
    cout<< allDistances.size()<<endl;
    int t=0;

    for(int m =0 ; m < allImages.size() ; m++){
        img = allImages[m];
        if(m==allImages.size()-1){
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m).c_str(), img);
            break;
        }
        img1 = allImages[m+1];
        dist4 = Mat::zeros(img.size(), img.type());
        dist3 = Mat::zeros(img.size(), img.type());
        cvtColor(img, dist3, CV_RGB2GRAY);
        cvtColor(img1, dist4, CV_RGB2GRAY);
        if(cv::countNonZero(dist3)==0){
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m).c_str(), img);
            t++;
        }else{
            if(cv::countNonZero(dist3)!=0&&cv::countNonZero(dist4)!=0){
                 int compteur=0;
                 imgC = Mat::zeros(imgA.size(), CV_8UC3);
                 //à modifier
                 imgC=cv::Scalar(0,0,0);
                 int k=m-t;
                 vector<Vec4i> distanceImage = allDistances[k];
                 for( int i=0; i < distanceImage.size(); i++ ){
                     Vec4i p01 = distanceImage[i];
                     Point p0(p01[0], p01[1]);
                     Point p1(p01[2], p01[3]);
                     int dist_euclidienne = (int) sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y));
                     if(dist_euclidienne<= derniere_valeur){
//
                        line( imgC, p0, p1, Scalar(255,255,255)  ,1, CV_AA,0);
                        compteur++;
                     }
                 }
                 imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m).c_str(), imgC);

                if(countNonZero(dist4)==0){
                t=0;
                }

             distanceImage.clear();
             }else{
                 imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m).c_str(), img1);

                 t++;
             }
         }
    }


//    t=0;
//    for(int m =0; m < allImages.size(); m++){

//        //additionner grabcut au resultat du flot optique
//        img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), position+m+t).c_str(), CV_LOAD_IMAGE_UNCHANGED);
//        dist3 = Mat::zeros(img.size(), img.type());
//        cvtColor(img, dist3, CV_RGB2GRAY);
//        if(cv::countNonZero(dist3)==0){
//            int t1=0;
//            while(true){
//                if(m+t+t1==allDistances.size()){
//                    t+=t1;
//                    t1=0;
//                    break;
//                }
//                img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), position+m+t+t1).c_str(), CV_LOAD_IMAGE_UNCHANGED);
//                dist3 = Mat::zeros(img.size(), img.type());
//                cvtColor(img, dist3, CV_RGB2GRAY);
//                if(cv::countNonZero(dist3)!= 0){
//                    imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t+t1).c_str(), img);
//                    dist = Mat::zeros(imgC.size(), CV_8UC3);
//                    addWeighted(img, 0.5, imgC, 0.5, 0.0, dist);
//                    if(dist.cols>768 && dist.rows>576){
//                        cv::resize(dist, dst,imgref.size());
//                        imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m+t+t1+1).c_str(), dst);
//                    }
//                    imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t+t1+1).c_str(), dist);
//                    t1++;
//                    t+=t1;
//                    t1=0;
//                    break;
//                }
//                addWeighted(img, 0.5, imgC, 0.5, 0.0, dist);
//                if(img.cols>768 && img.rows>576){
//                    cv::resize(img, dst,imgref.size());
//                    imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m+t+t1+1).c_str(), dst);
//                }
//                imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t+t1).c_str(), img);
//                t1++;
//            }
//        }else{


//            dist = Mat::zeros(imgC.size(), CV_8UC3);
//            addWeighted(img, 0.5, imgC, 0.5, 0.0, dist);
//            if(dist.cols>768 && dist.rows>576){
//                cv::resize(dist, dst,imgref.size());
//                imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m+t).c_str(), dst);
//            }
//            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m+t).c_str(), dist);
//        }
//        cout<<m<<endl;
//    }

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
