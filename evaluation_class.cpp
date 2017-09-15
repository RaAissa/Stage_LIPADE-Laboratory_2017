#include "evaluation_class.h"
#include "Bibliotheque.h"
Evaluation_class::Evaluation_class()
{
}

void Evaluation_class::runevaluation(int&positionswitch,bool &premiere_fois,vector<Mat>allImages,int &position,int taillevideo, string nouveauDossier, string traitement){
    ofstream fichierpr1 ( "/home/aissa/Bureau/x.txt", ios::out | ios::trunc);
    ofstream fichierpr2 ( "/home/aissa/Bureau/y.txt", ios::out | ios::trunc);
cout<< "blablabla"<<endl;
int taillevideoz=1;
while(true){
    cout<<"0"<<endl;
    QFileInfo photo(cv::format("/home/aissa/Bureau/Evaluation/P/frame%d.jpg",taillevideoz).c_str());
    if(!photo.exists()){
        cout<<"cette image n existe"<<endl;
        break;
    }
    taillevideoz++;
}
taillevideoz--;
float sommepre=0;
float sommerap=0;

for(int i=0;i<taillevideoz;i++){

        int vpetfp=0;
        int FN=0;
        int VP=0;
         int FP=0;
         int fond=0;
         int VN=0;
         int L=0;
Mat imgA1=cv::imread(cv::format("/home/aissa/Bureau/Evaluation/R/frame%d.tif", i).c_str(), 1);

// Mat imgB=cv::imread("/home/aissa/Bureau/Evaluation/frame%d.tif", CV_LOAD_IMAGE_COLOR);

cout<<"1" <<endl;
Mat imgC=cv::imread(cv::format("/home/aissa/Bureau/Evaluation/P/frame%d.jpg", i+1).c_str(),1);

//                   imwrite("/home/aissa/Bureau/patch.tif", imgA);
//                      imwrite("/home/aissa/Bureau/patch2.tif", imgB);
//                         imwrite("/home/aissa/Bureau/patch1.tif", imgC);
//cout<<imgA.rows<<""<<imgA.cols<<endl;
//cout<<imgB.rows<<""<< imgB.cols<<endl;
//cout<<imgC.rows<< ""<<imgC.cols<<endl;
int size=imgA1.rows*imgA1.cols;
        for(int y = 0 ; y < imgA1.rows ; y ++){
             for(int x= 0 ; x < imgA1.cols ; x ++){

                 Vec3b intensite=imgA1.at<Vec3b>(y,x);
//                 Vec3b RESULTAT=imgB.at<Vec3b>(y,x);
                 Vec3b PATCH=imgC.at<Vec3b>(y,x);
                 //if (PATCH.val[0]!=255 && PATCH.val[1]!=255 && PATCH.val[2]!=255){


                   if((PATCH.val[0]==0&&PATCH.val[1]==0&&PATCH.val[2]==0)||(PATCH.val[0]==0&&PATCH.val[1]==0&&PATCH.val[2]==255)){

                            vpetfp++;
                   }
                    if(intensite.val[0]==0&&intensite.val[1]==0&&intensite.val[2]==0){
                        L++;

                        if((PATCH.val[0]==0&&PATCH.val[1]==0&&PATCH.val[2]==0)||(PATCH.val[0]==0&&PATCH.val[1]==0&&PATCH.val[2]==255)){
                                              VP++;

                                            }
                        if((PATCH.val[0]!=0&&PATCH.val[1]!=0&&PATCH.val[2]!=0)||(PATCH.val[0]!=0&&PATCH.val[1]!=0&&PATCH.val[2]!=255)){

                          FN++;
//                            cout<<"i"<<endl;
                        }

                    }else{

                        fond++;
                    }





                 //}

             }

        }
        cout<<"itération"<<i<<endl;
cout<<"Vrai positifs "<< VP<<" "<<"FAUX Positifs "<<FP<<endl;
//cout<<"fond "<< fond<<endl;
//cout<<"vpet fp "<< vpetfp<<endl;
//VN=fond-abs(vpetfp-L);
//cout<<"VN "<< VN<<endl;
//FN= size-(VN+vpetfp);
cout<<"Faux Négatifs "<< FN<<endl;


cout<< "precision"<<endl;
float precision=(float)VP/(float)(vpetfp);
cout<<precision <<endl;
sommepre=sommepre+precision;
cout<<"rappel"<<endl;
int k=(VP+FN);
float rappel=(float)((float)VP/(float)(k));
sommerap=sommerap+rappel;
cout<< rappel<<endl;
fichierpr1<<float(i+1)/1<<endl;
fichierpr2<<rappel<<endl;
}
string commande = "python /home/aissa/Bureau/from_armand/courbe.py";
 system(commande.c_str());

cout<<"precision moyenne"<<" "<<(float)(sommepre/taillevideoz)<<endl;
cout<<"rappel moyenne"<<" "<<(float)(sommerap/taillevideoz)<<endl;

}
