
/*
 * Auteur: Raouf AISSA
 * Date de creation: 01/03/2017
 */
#include "Etoile.h"
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

Etoile::Etoile()
    {
    }

void Etoile::runEtoile(int&positionswitch,bool &premiere_fois,vector<Mat>allImages,int &position,int taillevideo, string nouveauDossier, string traitement){
    RNG rng;
    if (premiere_fois==true){
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Traits");
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans");
        premiere_fois=false;
    }

    Mat imgref=imread("/home/aissa/Bureau/out5/frame1.tif",CV_LOAD_IMAGE_COLOR);
    cout<<"entré etoile"<<endl;
    Mat imgA,imgC,dist,dist1,binary,dst;
    int compt=0;
    srand(clock());

    for(int m = 0; m < allImages.size(); m++){
       std::vector<cv::Point2f> cornersA;
       imgA = allImages[m];
       imgC = Mat::zeros(imgA.size(), CV_8UC3);
       imgC=cv::Scalar(255,255,255);
       cv::Mat output = cv::Mat::zeros(imgA.size(), CV_8UC3);
       dist1 = Mat::zeros(imgA.size(), imgA.type());
       cvtColor(imgA, dist1, CV_RGB2GRAY);
       if(cv::countNonZero(dist1) !=0){
           Scalar bleu = Scalar(255,0,0);
           cvtColor(imgA, dist1, CV_RGB2GRAY);
           cv::Point centre_gravite=barycentre(imgA);
           cv::circle(imgC,centre_gravite, 2, bleu, 2);
           int compteur=0;
           int compteur1=0;
           //si je veux prendre plusieurs point dans ma forme aletoirement:
           int pixels=0;
           int pixels1=0;
           int decision;
           for(int y = 0 ; y < imgA.rows ;  y = y +pixels){
               for(int x = 0 ; x < imgA.cols ;  x = x +pixels1){
                  Vec3b intensite1= imgA.at<Vec3b>(y,x);
                   pixels=10+rand()% 20+1;
                   pixels1=10+rand()% 20+1;
                   decision=rand()% 4+1;
                  if ((decision==1||decision==3)&&intensite1.val[0]!=0 && intensite1.val[1]!=0 && intensite1.val[2]!=0){
                      cornersA.push_back(Point(x,y));
                  }

               }
           }

           //changer pour les  arcs à droite angle=390 a 320 a peu pres
           //si je veux changer un random en loi uniforme ou normal changer ça:
           //dans la boucle for angle=angle-Etoile::NormalDistribution(4,2)

           //for(int q=0;q<cornersA.size();q++){
           //Point centre_corners=cornersA[q];
           for(double angle =360; angle>0 ; angle=angle-1 ){
               // le sens de ce compteur est de m arreter a 150 traits exactement:
               //if(compteur==10){
               //break;
               //}

               // je decide du critere  de selection dans paramettre decision1
               //compteur1++;

               vector<Point> p;

               //si je veux faire une loi uniforme
               //si je veux faire  de la  distribution Normale: NormalDistribution(angle/2,10)
               //double k=Etoile::NormalDistribution(angle/2,10);

               //la longeur de nos ségment en uniforme aletoire[0,100]:
               //modifié de 100 a 10
               //à modifé
               int  mon_nombre_max=500;
               int temps=m+position;
               int k;
               if(temps<70){
                   k =rng.uniform(temps, 50+temps);
               }else{
                    k =rng.uniform(140-temps, 190-temps);
               }
               //int k=rand()% mon_nombre_max+1;
               int k1=rand()% mon_nombre_max+1;
               // si je veux faire  varier la langueur inversement
               // du nombre de points
               // pour faire varier mon K selon le nombre de corners que j'ai
               // (si je veux le faire aletoirement=>k=rand()% k+1):
               //int k=100;
               //k=(int)(k/(int)cornersA.size());
               //k=rand()% k+1;
               // si je veux faire la methode de proportion:
               int nombre_voulu=150;
               int o=(int)(nombre_voulu* mon_nombre_max)/360;
               //si je veux le faire varier:
               //selon T:
               //double decision1=rand()% 36+1;
               //à modifier
               //double y=k/100;
               //decision de dessiner ou pas
               //if(k1<o){
               float radian = angle*(0.0174533);
               //si je veux faire  plusieurs centre dans mon image
               //int x_ro = (int)centre_corners.x + (k * cos(radian));
               //int y_ro = (int)centre_corners.y + (k * sin(radian));
               // si je veux prenbdre le centre de gravité:
               int x_ro = (int)centre_gravite.x + (k * cos(radian));
               int y_ro = (int)centre_gravite.y+ (k * sin(radian));
               //si je veux enlever 200 pixels a mes traits
               //à partir le centre de gravité:
               //int x_ro1 = (int)centre_gravite.x + ((k-200) * cos(radian));
               //int y_ro1 = (int)centre_gravite.y+ ((k-200) * sin(radian));
               int compt_pixels=0;
               int x_ro1;
               int y_ro1;
               //Si je veux  faire débuter mes traits depuis le bords de la bouche
               //ou N pixels avant ou apres:
               //while(true){
               //if(imgA.at<Vec3b>((int)(centre_gravite.y+ (k-compt_pixels) * sin(radian)),(int)(centre_gravite.x + (k-compt_pixels) * cos(radian)))[0]==255 &&
               //imgA.at<Vec3b>((int)(centre_gravite.y+ (k-compt_pixels) * sin(radian)),(int)(centre_gravite.x + (k-compt_pixels) * cos(radian)))[1]==255&&
               //imgA.at<Vec3b>((int)(centre_gravite.y+ (k-compt_pixels) * sin(radian)),(int)(centre_gravite.x + (k-compt_pixels) * cos(radian)))[2]==255){
               //compt_pixels++;
               //}else{
               //break;
               //}
               //}
               //x_ro1 = (int)centre_gravite.x + ((k-compt_pixels-2) * cos(radian));            
               //y_ro1 = (int)centre_gravite.y+ ((k-compt_pixels-2) * sin(radian));
               //Point(centre_gravite.x+100,centre_gravite.y+100)
               //si je veux maintenant varier mes couleurs teinte HSV
               // H=(float) angle;
               float r=0, g =0, b=0;
               float H = 0;
               H =(float) angle;
               LucasKanadeCarteDeChaleur *carte = new LucasKanadeCarteDeChaleur();
               carte->HSVtoRGB(&r, &g, &b, H);
               //Le sens de cette condition(if):si ya un trait qui commence
               //à l'interieur de mon périmetre(interieur de la bouche)
               //quand je commence apartir du bord ou 2 pixels avant
               //pour les ségments trop petits (eliminer):
               //if(imgA.at<Vec3b>(y_ro,x_ro)[0]==255 && imgA.at<Vec3b>(y_ro,x_ro)[1]==255 && imgA.at<Vec3b>(y_ro,x_ro)[2]==255){
               //si je ne veux plus faire varier ma couleur:
               //remplacer: Scalar (b *255,g *255,r *255) par
               //Scalar (b *255,g *255,r *255) dans la fonction line

               // si je veux  pendre plusieurs points
               // remplacer Point(centre_gravite.x , centre_gravite.y) par
               //Point(centre_corners.x , centre_corners.y)
               line(imgC, Point(centre_gravite.x , centre_gravite.y), Point(x_ro, y_ro), Scalar (b*255,g*255,r*255), 1, CV_AA);

               //}
                           
               compteur++;
                       
               //}           
           }
           //}
       }else{
           compt++;
       }
       imwrite(cv::format((nouveauDossier + "/" + traitement + "/Traits/frame%d.tif").c_str(), position+m).c_str(),imgC);
       dist = Mat::zeros(imgC.size(), CV_8UC3);
       addWeighted(imgA, 0.5, imgC, 0.5, 0.0, dist);
       if(dist.cols>768 && dist.rows>576){
           cv::resize(dist, dst,imgref.size());
           imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position+m).c_str(), dst);
       }
       imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m).c_str(),dist);
    }
}



// à modifier

void Etoile::runEtoile_compo(int&positionswitch,bool &premiere_fois,vector<Mat>allImages,int &position,int taillevideo, string nouveauDossier, string traitement){
   RNG rng;
   RNG rng2;
   if (premiere_fois==true){
        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Traits");

        Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Kmeans");
        premiere_fois=false;
   }
   vector<int>positionblob;
   Mat imgref=imread("/home/aissa/Bureau/out5/frame1.tif",CV_LOAD_IMAGE_COLOR);
   cout<<"entré etoile"<<endl;
   Mat imgA,imgC,dist,dist1,binary,dst;
   int compt=0;
   srand(clock());
   int l=rand()%10;
   int y1=rand()% 6;

   Mat MATRICE(1000000, 2, CV_32F);
   int size=0; bool premiere=true;
   for(int m = 0; m < allImages.size(); m++){
       imgA = allImages[m];
       imgC = Mat::zeros(imgA.size(), CV_8UC3);
       imgC=cv::Scalar(0,0,0);
       cv::Mat output = cv::Mat::zeros(imgA.size(), CV_8UC3);
       dist1 = Mat::zeros(imgA.size(), imgA.type());
       cvtColor(imgA, dist1, CV_RGB2GRAY);
       Scalar bleu = Scalar(255,0,0);
       cvtColor(imgA, dist1, CV_RGB2GRAY);
       std::vector < std::vector<cv::Point2i > > blobs;
       cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
       FindBlobs(binary, blobs);
    }
    for(int m = 0; m < allImages.size(); m++){
       //if(l>0){
        imgA = allImages[m];
        imgC = Mat::zeros(imgA.size(), CV_8UC3);
        imgC=cv::Scalar(0,0,0);
        cv::Mat output = cv::Mat::zeros(imgA.size(), CV_8UC3);
        dist1 = Mat::zeros(imgA.size(), imgA.type());
        cvtColor(imgA, dist1, CV_RGB2GRAY);
        if(cv::countNonZero(dist1) !=0){
            Scalar bleu = Scalar(255,0,0);
            cvtColor(imgA, dist1, CV_RGB2GRAY);
            std::vector < std::vector<cv::Point2i > > blobs;
            cv::threshold(dist1, binary, 0.0, 1.0, cv::THRESH_BINARY);
            FindBlobs(binary, blobs);
            Mat MATRICE(blobs.size(), 2, CV_32F);
            for(int i=0;i<blobs.size();i++){
                if(premiere==true){
                    cv::Point centre_gravite=barycentrecompo(blobs[i]);
                    MATRICE.at<float>(i,0)=centre_gravite.x;
                    MATRICE.at<float>(i,1)=centre_gravite.y;
                }
            }
                  //Mat labels=Kmeans_blobs(imgA,MATRICE,position,nouveauDossier,traitement,1);
            int decision1=rand()% blobs.size();
            int decision2=rand()% blobs.size();
            int decision3=rand()% blobs.size();
            int nombre=(m*blobs.size())/255;
            int compteur=0;
            for(int i=0;i<blobs.size();i++){
                if(compteur<nombre && compteur<blobs.size()){
                    //taille de blobs a ignorer
                    //int taille_de_blobs =180;
                    //int taille_max =0;
                    //int indice=0;
                    //for(int i=0;i<blobs.size();i++){
                    //if(blobs[i].size()>taille_max){
                    //taille_max=blobs[i].size();
                    //indice=i;
                    //}
                    //}
               int y=rand()% 4;
                //if(labels.at<int>(i)==y1){
                //int nombre_voulu=150;
                //int o=(int)(nombre_voulu* mon_nombre_max)/360;
                //if(y==2){
               int decision5=rand()%blobs.size();
               cv::Point centre_gravite=barycentrecompo(blobs[decision5]);
                   //int compteur=0;
                   //int compteur1=0;
                   //changer pour les  arcs à droite angle=390 a 320 a peu pres
                   //si je veux changer un random en lois uniforme ou normal
                   //angle=angle-Etoile::NormalDistribution(4,2)
                   //int kl= rng.uniform(20,60);
               int k;
               compteur++;
               for (double angle =  360; angle>0 ; angle=angle-rng.uniform(10,60)){
                        //if(compteur==kl){
                        //break;
                        //}
                        //compteur1++;
                   vector<Point> p;
                       //si je veux faire une lois uniforme
                       //double y=rand()% 3+1;
                       //si je veux faire  de la  distribution Normale: NormalDistribution(angle/2,10)

//                      if (blobs[i].size()>150){
//                      if (labels.at<int>(i)==1) {
                   k= rng2.uniform(5,20);

//                      }
                      /*else{
                              k= rng2.uniform(1,10);
                      }*/

                      //double k=Etoile::NormalDistribution(angle/2,10);
                       //à modifier
                       //double y=k/100;
                           float radian = angle*(0.0174533);
                           int x_ro = (int)centre_gravite.x + (k * cos(radian));
                           int y_ro = (int)centre_gravite.y+ (k * sin(radian));
                           //int x_ro1 = (int)centre_gravite.x + ((k-200) * cos(radian));
                           //int y_ro1 = (int)centre_gravite.y+ ((k-200) * sin(radian));
                           int compt_pixels=0;
                           int x_ro1;
                           int y_ro1;
                           //while(true){
                           //if(imgA.at<Vec3b>((int)(centre_gravite.y+ (k-compt_pixels) * sin(radian)),(int)(centre_gravite.x + (k-compt_pixels) * cos(radian)))[0]==255 &&
                           //imgA.at<Vec3b>((int)(centre_gravite.y+ (k-compt_pixels) * sin(radian)),(int)(centre_gravite.x + (k-compt_pixels) * cos(radian)))[1]==255&&
                           //imgA.at<Vec3b>((int)(centre_gravite.y+ (k-compt_pixels) * sin(radian)),(int)(centre_gravite.x + (k-compt_pixels) * cos(radian)))[2]==255){
                           //compt_pixels++;
                           //}else{
                           //break;
                           //}
                           //}
                           x_ro1 = (int)centre_gravite.x + ((k-compt_pixels-2) * cos(radian));
                           y_ro1 = (int)centre_gravite.y+ ((k-compt_pixels-2) * sin(radian));
                           //Point(centre_gravite.x+100,centre_gravite.y+100)
                           float r=0, g =0, b=0;
                           float H = 0;
                           H =(float) angle;
                           LucasKanadeCarteDeChaleur *carte = new LucasKanadeCarteDeChaleur();
                           carte->HSVtoRGB(&r, &g, &b, H);
                           //if(imgA.at<Vec3b>(y_ro,x_ro)[0]==255 && imgA.at<Vec3b>(y_ro,x_ro)[1]==255 && imgA.at<Vec3b>(y_ro,x_ro)[2]==255){
                           line(imgC, Point(centre_gravite.x , centre_gravite.y), Point(x_ro, y_ro), Scalar (255,255,255), 1.5, CV_AA);
                   }

              }
                 //  }
                   //}
            //  }
             //cout<<blobs.size()<<endl;

        }


           //imwrite("/home/aissa/Bureau/frameetoile.tif", dist);
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
//   l--;
   // }else{
//        l=rand()%10;
//        y1=rand()%6;
    //}
    }
}



int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;
Mat src, dilation_dst;
Mat Etoile::Dilation(Mat h)
{
 int dilation_type;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  // Apply the dilation operation
  dilate( h, dilation_dst, element );

       return dilation_dst;

}

Point Etoile::barycentre(cv::Mat img){
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

Point Etoile::barycentrecompo(vector<cv::Point2i>b){
    int somme_x=0,somme_y=0,N=0;
    for(int i=0;i<b.size();i++){
        somme_x+=(int)b[i].x;
        somme_y+=(int)b[i].y;
        N++;
    }
    cv::Point ctr_gravite((int)(somme_x/N),(int)(somme_y/N));
    return ctr_gravite;
}

double Etoile::NormalDistribution(double mu,double sigma){
    if(sigma<=0.0){
       cout<<"Sigma est inferieur a 0"<<endl;
       exit(EXIT_FAILURE);
    }
    return (mu+sigma*RANDN);
}

// a completer
void Etoile::FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs){
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

Mat Etoile::Kmeans_blobs(cv::Mat &img1,cv::Mat&confusion,int position,string nouveauDossier, string traitement,int pixels)
{
    const int MAX_CLUSTERS =2;
    Scalar colorTab[] =
    {
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
    RNG rng(12345);
    Mat dist(img1.rows,img1.cols,CV_8UC3);

    int size1=confusion.rows*confusion.cols;
    Mat  labels;
    Mat centers;
    kmeans(confusion,MAX_CLUSTERS, labels,
           TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
           3, KMEANS_PP_CENTERS, centers);


   dist = Scalar::all(255);
   int size3= confusion.rows;


   for(int i = 0; i <size3; i++ ){
        int clusterIdx = labels.at<int>(i);
//      Etoile *c=new Etoile();
//       cv::Point centre_gravite=barycentrecompo(blobs[i]);

//      rectangle(dist, Rect(centre_gravite.x, centre_gravite.y,10,10),colorTab[clusterIdx],-1 );
   }
  // imwrite(cv::format((nouveauDossier + "/" + traitement + "/Kmeans/frame%d.tif").c_str(), position-1).c_str(), dist);

   img.release();
   dist.release();
   centers.release();
   return labels;
}
