
/*
 * Auteur: Raouf AISSA
 * Date de creation: 01/03/2017
 */


#include "etoile_k.h"
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include "lucaskanadecartedechaleur.h"
#define RAND ((double) rand())/((double) RAND_MAX)
#define TWOPI 2.0*3.141592653589793238462643383279502884197169399375
#define RANDN sqrt(-2.0*log(RAND))*cos(TWOPI*RAND)

etoile_k::etoile_k()
{
}

double etoile_k::NormalDistribution(double mu,double sigma,int x){
    if(sigma<=0.0){
       cout<<"Sigma est inferieur a 0"<<endl;
       exit(EXIT_FAILURE);
    }
    return (mu+sigma*RANDN);
}
void etoile_k::creer_images(string nouveauDossier, string traitement){

    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/evaluationset");
    int size=0;
    int size1=0;
    int size2=0;
    int l=rand()%100;
        int l1=rand()%100;
    for(int im=0;im<13;im++){
        if(im>0){
          if(im<=(int)13/2){
              size=size+100;
              size1=size+20;
          }else{
              size=size+100;
              size1=size1+20;
              size2=size2+100;
          }
        }

        Mat img= Mat::zeros(1080,1920, CV_8UC3);
        for(int y=0;y<img.rows;y++){
            for(int x=0; x<img.cols;x++){
                if(x==50+size&&y==50+size2){
                    rectangle(img,Rect(50+size,50+size2,2,2),Scalar(0,255,0),-1 );
                    int l=rand()%100;
                    for(int i=0;i<l; i++){
                       rectangle(img,Rect(size+50+(100-rand()%100),size2+50+(100-rand()%100),2,2),Scalar(0,255,0),-1 );
                    }
                }
                if(x==50+size1&&y==200+size2){
                    rectangle(img,Rect(50+size1,200+size2,2,2),Scalar(0,0,255),-1 );
                    for(int i=0;i<l; i++){
                       rectangle(img,Rect(size1+50+(100-rand()%100),200+(100-rand()%100)+size2,2,2),Scalar(0,0,255),-1 );
                    }
                }
            }
        }
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/evaluationset/frame%d.tif").c_str(), im+1).c_str(), img);
    }
}


// à modifier
Mat centers1, centers;

void etoile_k::runEtoile_compo(int&positionswitch,bool &premiere_fois,vector<Mat>allImages,int &position,int taillevideo, string nouveauDossier, string traitement){

creer_images(nouveauDossier,traitement);
    RNG rng;
    RNG rng2;
    RNG rng3;
    int size2=0;
    if (premiere_fois==true){
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Traits");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans2d");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans2d/resize");
        premiere_fois=false;
    }

    Mat imgref=imread("/home/aissa/Bureau/out5/frame1.tif",CV_LOAD_IMAGE_COLOR);
    cout<<"entré etoile"<<endl;
    Mat imgA,imgC,dist,dist1,binary,dst;
    int compt=0;
    srand(clock());
    //int l = rand()%10;
    std::vector < std::vector<cv::Point2i > > blobs;
    imgA = allImages[(int)allImages.size()/2];
    imgC = Mat::zeros(imgA.size(), CV_8UC3);
    imgC = cv::Scalar(0,0,0);
    cv::Mat output = cv::Mat::zeros(imgA.size(), CV_8UC3);
    dist1 = Mat::zeros(imgA.size(), imgA.type());
    cvtColor(imgA, dist1, CV_RGB2GRAY);
    //std::vector < std::vector<cv::Point2i > > blobs;
    cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
    FindBlobs(binary, blobs);

    Mat MATRICE(blobs.size(), 2, CV_32F);
    for(int i=0;i<blobs.size();i++){
        cv::Point centre_gravite=barycentrecompo(blobs[i]);
        MATRICE.at<float>(i,0)=centre_gravite.x;
        MATRICE.at<float>(i,1)=centre_gravite.y;

        //        if(centre_gravite.x<400){

        //            MATRICE.at<float>(i,0)=50;

        //        }else{

        //            MATRICE.at<float>(i,0)=30;

        //        }
    }

    Mat MATRICE_0;
    normalize(MATRICE,MATRICE_0,0.0,1.0,NORM_MINMAX);

    Kmeans_blobs(allImages,imgA,MATRICE_0,position,nouveauDossier,traitement,positionswitch, centers1);



    std::vector <int> Labels;
    Mat MATRICE_1;
    int size = 0; bool premiere1=true; int label;
    size2=taille(allImages);
    MATRICE_1=Mat::zeros(size2, 3, CV_32F);
    
    for(int m = 0; m <allImages.size(); m++){
        imgA = allImages[m];
        imgC = Mat::zeros(imgA.size(), CV_8UC3);
        imgC=cv::Scalar(0,0,0);
        dist1 = Mat::zeros(imgA.size(), imgA.type());
        cvtColor(imgA, dist1, CV_RGB2GRAY);
        if(cv::countNonZero(dist1) !=0){
           cvtColor(imgA, dist1, CV_RGB2GRAY);
           std::vector < std::vector<cv::Point2i > > blobs;
           cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
           FindBlobs(binary, blobs);
           for(int i=0;i<blobs.size();i++){
               cv::Point centre_gravite=barycentrecompo(blobs[i]);
             //calcule de la distance entre nos points et les labels de la frame 5
               label=distance((int)centre_gravite.x,(int)centre_gravite.y, m, centers1);
               cout<<label<<endl;
               if(premiere1==true){
                   Labels.push_back(label);
                   MATRICE_1.at<float>(i,0)=(float)centre_gravite.x;
                   cout<<(float)centre_gravite.x<<" ";
                   MATRICE_1.at<float>(i,1)=(float)centre_gravite.y;
                   cout<<(float)centre_gravite.y<<" ";
//                   if(centre_gravite.x<400){
//                       MATRICE_1.at<float>(i,0)=50;
//                   }else{
//                       MATRICE_1.at<float>(i,0)=30;
//                   }
                   MATRICE_1.at<float>(i,2)=(float)(m+1)*10;

               }else{
                   Labels.push_back(label);
                   MATRICE_1.at<float>(i+size,0)=(float)centre_gravite.x;
                   cout<<(float)centre_gravite.x<<" ";
                    MATRICE_1.at<float>(i+size,1)=(float)centre_gravite.y;
                    cout<<(float)centre_gravite.y<<" ";
//                   if(centre_gravite.x<400){
//                       MATRICE_1.at<float>(i+size,0)=50;
//                   }else{
//                       MATRICE_1.at<float>(i+size,0)=30;
//                   }
                   MATRICE_1.at<float>(size+i,2)=(float)(m+1)*10;
               }
           }

           size=size+blobs.size();
           premiere1=false;
        }else{
            compt++;
        }
    }
    cout<<"Matrice#########"<<endl;
    cout<<MATRICE_1.rows<<endl;
    cout<<MATRICE_1.cols<<endl;

    cout<<"normalize1"<<endl;
cout<<""<<endl;
    for(int x = 0 ; x < MATRICE_1.cols ; x = x +1){
         for(int y = 0 ; y < MATRICE_1.rows ; y = y + 1){
             cout<<MATRICE_1.at<float>(y,x)<<" ";
         }
         cout<<""<<endl;
    }
cout<<"########"<<endl;






    cout<<"normalize"<<endl;
    Mat MATRICE_2;

    //normalisation min max
    normalize(MATRICE_1,MATRICE_2,0.0,1.0,NORM_MINMAX);



    cout<<"normalize1"<<endl;
    cout<<""<<endl;
    for(int x = 0 ; x < MATRICE_1.cols ; x = x +1){
         for(int y = 0 ; y < MATRICE_1.rows ; y = y + 1){
             cout<<MATRICE_2.at<float>(y,x)<<" ";
         }
         cout<<""<<endl;
    }
    cout<<"########"<<endl;


    vector<int> labels1=Kmeans_blobs1(allImages,Labels,imgA,MATRICE_2,nouveauDossier,traitement,positionswitch);
    MATRICE_1.release();
    MATRICE_2.release();
    int size1=0;
    cout<<"decision"<<endl;

    int decision1=rand()%6;
    cout<<"decision1"<<endl;
    int decision2=3 ;
//      while (true){
//          for(int i = 0; i <listr1.size(); i++){
//          int decision1= rand()%2;
//            if(decision1==1){
//              listr1[i]=1;
//              compteur++;
//            }
//          }
//          if(compteur==decision0){
//              break;
//          }
//       }
    int compter=2;
    int size3=compter;

    for(int m = 0; m <allImages.size(); m++){
    cout<<"boucle"<<endl;
        if(compter==0){
            decision1= rand()%6;
            decision2= rand()%6;
            compter=2;
            size3=compter;
        }
        imgA = allImages[m];
        imgC = Mat::zeros(imgA.size(), CV_8UC3);
        imgC = cv::Scalar(0,0,0);
        cv::Mat output = cv::Mat::zeros(imgA.size(), CV_8UC3);
        dist1 = Mat::zeros(imgA.size(), imgA.type());
        cvtColor(imgA, dist1, CV_RGB2GRAY);
        if(cv::countNonZero(dist1) !=0){
            cvtColor(imgA, dist1, CV_RGB2GRAY);
            std::vector < std::vector<cv::Point2i > > blobs;
            cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
            FindBlobs(binary, blobs);
            for(int i=0;i<blobs.size();i++){
                int y=rand()%4;
                int y1=rand()%2;
                cv::Point centre_gravite=barycentrecompo(blobs[i]);
                // if(labels1[size1]==decision1){
                for (double angle =  360; angle>0 ; angle=angle-rng.uniform(5,25)){
                    vector<Point> p;
                    double k;
                    k=rng2.uniform(1,30);
                    float radian = angle*(0.0174533);
                    int x_ro = (int)centre_gravite.x + (k * cos(radian));
                    int y_ro = (int)centre_gravite.y+ (k * sin(radian));
                    int compt_pixels=0;
                    int x_ro1;
                    int y_ro1;
                    x_ro1 = (int)centre_gravite.x + ((k-compt_pixels-2) * cos(radian));
                    y_ro1 = (int)centre_gravite.y+ ((k-compt_pixels-2) * sin(radian));
                    float r=0, g =0, b=0;
                    float H = 0;
                    H =(float) angle;
                    LucasKanadeCarteDeChaleur *carte = new LucasKanadeCarteDeChaleur();
                    carte->HSVtoRGB(&r, &g, &b, H);
                    line(imgC, Point(centre_gravite.x , centre_gravite.y), Point(x_ro, y_ro), Scalar (255,255,255 /*b*255,g *255,r *255*/), 1.5, CV_AA);
                }
                //}
                size1++;
            }
        }else{
            compt++;
        }
        dist = Mat::zeros(imgC.size(), CV_8UC3);
        addWeighted(imgA, 0.5, imgC, 0.5, 0.0, dist);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Traits/frame%d.tif").c_str(), position+m).c_str(),imgC);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m).c_str(),dist);
        if(dist.cols>768 && dist.rows>576){
            cv::resize(dist, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m).c_str(), dst);
        }
        compter--;
    }
    cout<<"size1"<<endl;
    cout<<size1<<endl;
}

int etoile_k::taille(vector<Mat>allImages){
    int size2=0;
    Mat imgA,dist1,binary;
    for(int m = 0; m <allImages.size(); m++){
        std::vector < std::vector<cv::Point2i > > blobs;
        imgA = allImages[m];
        cv::Mat output = cv::Mat::zeros(imgA.size(), CV_8UC3);
        dist1 = Mat::zeros(imgA.size(), imgA.type());
        cvtColor(imgA, dist1, CV_RGB2GRAY);
        //std::vector < std::vector<cv::Point2i > > blobs;
        cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
        FindBlobs(binary, blobs);
        size2=size2+blobs.size();
    }
    return size2;
}

int etoile_k::distance(int x,int y,int frame, Mat centers1){
    double distance_av=1920000000.0;
    int label=0;
    double distance=0;
    for(int i=0;i<centers1.rows;i++){
        distance=(double) sqrt(((y-centers1.at<int>(i,1))*(y-centers1.at<int>(i,1)))+((x-centers1.at<int>(i,0)) 
                          *(x-centers1.at<int>(i,0)))+((6*10)-(10*(frame+1)))*((6*10)-(10*(frame+1))));
        if (distance < distance_av){
            label=i;
            distance_av=distance;
        }
    }
    return label;
}

// centre de gravité
Point etoile_k::barycentre(cv::Mat img){
    Mat imga=img;
    int somme_x=0,somme_y=0,N=0;
    for(int y=0;y<imga.rows;y++){
        for(int x=0;x<imga.cols;x++){
            Vec3b intensite = imga.at<Vec3b>(y,x);
            // modifie si tu a affaire a des trammes noir ou blanche
            if(intensite[0]!=255&&intensite[1]!=255&&intensite[2]!=255){
                somme_x+=x;
                somme_y+=y;
                N++;
            }
        }
    }
    cv::Point ctr_gravite((int)(somme_x/N),(int)(somme_y/N));
    return ctr_gravite;
}

//Centre de gravité Blobs
Point etoile_k::barycentrecompo(vector<cv::Point2i>b){
    int somme_x=0,somme_y=0,N=0;
    for(int i=0;i<b.size();i++){
        somme_x+=(int)b[i].x;
        somme_y+=(int)b[i].y;
        N++;
    }
    cv::Point ctr_gravite((int)(somme_x/N),(int)(somme_y/N));
    return ctr_gravite;
}

// Distribution Normal
double etoile_k::NormalDistribution(double mu,double sigma){
    if(sigma<=0.0){
        exit(EXIT_FAILURE);
    }
    return (mu+sigma*RANDN);
}

// Region Connexe
void etoile_k::FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs){
    blobs.clear();
    cv::Mat label_image;
    binary.convertTo(label_image, CV_32SC1);
    int label_count = 2;
    for(int y=0; y < label_image.rows; y++) {
        int *row = (int*)label_image.ptr(y);
        for(int x=0; x < label_image.cols; x++) {
            if(row[x] != 1) {
                continue;
            }
            cv::Rect rect;
            cv::floodFill(label_image, cv::Point(x,y), label_count, &rect, 0, 0, 4);
            std::vector <cv::Point2i> blob;
            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                int *row2 = (int*)label_image.ptr(i);
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if(row2[j] != label_count) {
                        continue;
                    }
                    blob.push_back(cv::Point2i(j,i));
                }
            }
            blobs.push_back(blob);
            label_count++;
        }
    }
}

// Kmeans pour les blobs
void etoile_k::Kmeans_blobs(vector<Mat>allImages,cv::Mat &img1,cv::Mat&confusion,int position,string nouveauDossier, string traitement,int pixels,cv::Mat&centers1){
    const int MAX_CLUSTERS =3;
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
    int size1=confusion.rows*confusion.cols;
    Mat  labels;
    kmeans(confusion,MAX_CLUSTERS, labels,TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),1, KMEANS_PP_CENTERS, centers1);
    Mat imgA,imgC,dist1,binary;
    int compt=0;
    srand(clock());
    std::vector < std::vector<cv::Point2i > > blobs;
    imgA = allImages[(int)(allImages.size()/2)];
    imgC = Mat::zeros(imgA.size(), CV_8UC3);
    imgC = cv::Scalar(0,0,0);
    cv::Mat output = cv::Mat::zeros(imgA.size(), CV_8UC3);
    dist1 = Mat::zeros(imgA.size(), imgA.type());
    cvtColor(imgA, dist1, CV_RGB2GRAY);
    cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
    FindBlobs(binary, blobs);
    cout<<"##########Cb1###########"<<endl;

    cout<<centers1<<endl;
     cout<<centers1.rows<<endl;
      cout<<centers1.cols<<endl;
    dist = Scalar::all(255);
    int size3=blobs.size() ;
    for(int i = 0; i <size3; i++ ){
        int clusterIdx = labels.at<int>(i);
        cv::Point centre_gravite=barycentrecompo(blobs[i]);
        rectangle(dist, Rect(centre_gravite.x, centre_gravite.y,20,20),colorTab[clusterIdx],-1 );
    }

    imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans/frame%d.tif").c_str(), 5).c_str(), dist);
    img.release();
    dist.release();
//   centers1.release();
}

vector<int> etoile_k::Kmeans_blobs1(vector<Mat>allImages,std::vector<int>&Labels,cv::Mat &img1,cv::Mat&confusion,string nouveauDossier,
                                    string traitement,int pixels){
    Mat centers;
    const int MAX_CLUSTERS =3;
    Scalar colorTab[] ={
        Scalar(0, 0, 255),
        Scalar(0,255,0),
        Scalar(255,100,100),
        Scalar(255,0,255),
        Scalar(0,255,255),
        Scalar(255,255,0),
        Scalar(0,0,0),
        Scalar(255,255,255  ),
        Scalar(100,100,100),
        Scalar(0,50,50),
        Scalar(150,0,150),
        Scalar(50,0,50),
    };
    cout<<"#############Kmeans2##############"<<endl;
    kmeans(confusion,MAX_CLUSTERS, Labels,TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
         3, KMEANS_USE_INITIAL_LABELS, centers);
 cout<<"#############labels##############"<<endl;

 for(int i = 0; i <Labels.size(); i++ ){
     cout<<Labels[i]+1<< " ";


 }

    cout<<"aaa"<<endl;
    cout<<centers<<endl;
    int size_1=0;
    cout<<"ici"<<endl;
    for(int m = 0; m <allImages.size(); m++){

        cout<<"ici1"<<endl;
        Mat imgA,imgC,dist1,binary,dst;
        Mat dist(img1.rows,img1.cols,CV_8UC3);
        dist = Scalar::all(255);
        imgA = allImages[m];
        imgC = Mat::zeros(imgA.size(), CV_8UC3);
        imgC = cv::Scalar(0,0,0);
        cout<<"ici2"<<endl;
        dist1 = Mat::zeros(imgA.size(), imgA.type());
        cvtColor(imgA, dist1, CV_RGB2GRAY);
        std::vector < std::vector<cv::Point2i > > blobs;
        cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
        FindBlobs(binary, blobs);
        cout<<"ici3"<<endl;
        for(int i=0;i<blobs.size();i++){
            cout<<"ici"<<endl;
             int clusterIdx = Labels[size_1];
             cout<<"ici4"<<endl;
//           for(int y=0;y<blobs[i].size();y++){
//cout<<"ici5"<<endl;
               cv::Point centre_gravite=barycentrecompo(blobs[i]);
               rectangle(dist,Rect(centre_gravite.x, centre_gravite.y,10,10),colorTab[clusterIdx],-1 );


//               }
           size_1++;
        }
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans2d/frame%d.tif").c_str(), m).c_str(), dist);
          imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans2d/resize/frame%d.tif").c_str(), m).c_str(), dist);
    }


//   centers1.release();
    return Labels;
}
