#include "traitement.h"



Traitement::Traitement()
{

}

//modifié
void Traitement::run(int&positionwinsize,int &positionSwitch1,int &position,vector<Mat> &allImages,bool &premiere_fois,int positionSwitch, int taillevideo, string nouveauDossier, int positionSlider, QLabel *label_videoInitiale, vector <QPoint> points, const QWidget* maFenetre,std::vector<std::string> imaFolder, vector <QPoint> points_image, QString dirPathImage, QLabel &label_image_inpainting, string nouveauDossierVideo, vector <QPoint> points_video2, QLabel *label_videoInpainting,int&indice_k){
    Mat img;
    Mat dist;
    Mat dst;
    int positiosw=positionSwitch1;
    int positiosw1=positionwinsize;
    std::string traitement = imaFolder[positionSwitch];
    cout << "Traitement : " << traitement << endl;
    cout << traitement<< endl;
    bool premiere_fois2=premiere_fois;
    //Creation du repertoire permettant de sauvegarder les trames en NVG
if (premiere_fois==true){
    Dossier::creerDossier(nouveauDossier + "/" +traitement);
    cout << "Cree1"<< endl;
   //a decocher
  Dossier::creerDossier(nouveauDossier + "/" +traitement + "/resize");
  //cout << "Cree2 "<< endl;

    premiere_fois=false;
    }

Mat imgref=imread("/home/aissa/Bureau/out5/frame1.tif",CV_LOAD_IMAGE_COLOR);
    switch(positionSwitch)
    {
    //Transformation de la video en NVG
     case 0:
     {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat noirEtBlanc = Tool::noirEtBlanc(img);
            //Sauvegarde de la trame en NVG/*"/Noir et Blanc*/
            if(noirEtBlanc.cols>768 && noirEtBlanc.rows>576){
            cv::resize(noirEtBlanc,dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/frame%d.tif").c_str(), position + i).c_str(), noirEtBlanc);
        }
        allImages.clear();
            //Affichage de la premiere trame de la video initiale et de la video traite
        break;
    }
        //Transformation de la video par le filtre de Sobel
    case 1:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat contours = Tool::contours(img);
            if(contours.cols>768 && contours.rows>576){
            cv::resize(contours, dst, imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), contours);
        }
        break;
    }
        //Flouter l'image par un filtre de Gauss
    case 2:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat flouter = Tool::flouter(img);
            if(flouter.cols>768&& flouter.rows>576){
            cv::resize(flouter, dst, imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), flouter);
        }
        break;
    }
        //Inverser les couleurs d'une image
    case 3:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat negatif = Tool::negatif(img);

            if(negatif.cols>768 && negatif.rows>576){
            cv::resize(negatif, dst, imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement +"/frame%d.tif").c_str(), position+i).c_str(), negatif);

        }
        break;
    }
        //Inversion de la couleur rouge
    case 4:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat rouge = Tool::rouge(img);
            if(rouge.cols>768 && rouge.rows>576){
            cv::resize(rouge, dst, imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }

            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), rouge);

        }
        break;
    }
        //Inversion la couleur Vert
    case 5:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat vert = Tool::vert(img);
            if(vert.cols>768 && vert.rows>576){
            cv::resize(vert, dst, imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), vert);

        }
        break;
    }

        //Inversion de la couleur bleu
    case 6:
    {

        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat bleu = Tool::bleu(img);

            if(bleu.cols>768 && bleu.rows>576){
            cv::resize(bleu, dst, imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement +"/frame%d.tif").c_str(), position+i).c_str(), bleu);
        }
        break;
    }

        //Enlever la teinte
    case 7:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            //Conversion de l'espace couleur RGB en espace couleur HSV
            cvtColor(img, dist, CV_BGR2HSV);
            Mat enleverTeinte = Tool::enleverTeinte(dist);
            cvtColor(enleverTeinte, enleverTeinte, CV_HSV2BGR);
            if(enleverTeinte.cols>768 && enleverTeinte.rows>576){
            cv::resize(enleverTeinte, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), enleverTeinte);

        }
        break;
    }

        //Saturater
    case 8:
    { for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            //Conversion de l'espace         // perte de temps  a revoir rechercher un fichier nombre dans un fichiere
            printf("Cannot Open Image\n");
            break;
            //couleur RGB en espace couleur HSV
            cvtColor(img, dist, CV_BGR2HSV);
            Mat enleverSaturation = Tool::enleverSaturation(dist);
            cvtColor(enleverSaturation, enleverSaturation, CV_HSV2BGR);
            if(enleverSaturation.cols>768 && enleverSaturation.rows>576){
            cv::resize(enleverSaturation, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }

            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), enleverSaturation);

        }
        break;
    }

        //Mettre la brillance
    case 9:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            //Conversion de l'espace couleur RGB en espace couleur HSV
            cvtColor(img, dist, CV_BGR2HSV);
            Mat enleverBrillance = Tool::enleverBrillance(dist);
            cvtColor(enleverBrillance, enleverBrillance, CV_HSV2BGR);
            if(enleverBrillance.cols>768 && enleverBrillance.rows>576){
            cv::resize(enleverBrillance, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), enleverBrillance);

        }
        break;
    }

        //Passer de l'espace RGB a HSV et de HSV a RGB
    case 10:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            //Conversion de l'espace couleur RGB en espace couleur HSV
            cvtColor(img, dist, CV_BGR2HSV);
            Mat changement = Tool::changement(dist);
            if(changement.cols>768 && changement.rows>576){
            cv::resize(changement, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), changement);

        }
        break;
    }

        //Filtre special16
    case 11:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat special16 = Tool::special16(img);
            if(special16.cols>768 && special16.rows>576){
                cv::resize(special16, dst,imgref.size());
                imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), special16);

        }
        break;
    }
        //Filtre special64
    case 12:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat special64 = Tool::special64(img);
            if(special64.cols>768 && special64.rows>576){
            cv::resize(special64, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), special64);

        }
        break;
    }
   //Filtre Sobel image rgb
    case 13:
    {
        img = img = allImages[0];

              Mat rouge = Mat::zeros(img.size(), CV_8UC1);
              Mat bleu = Mat::zeros(img.size(), CV_8UC1);
              Mat vert = Mat::zeros(img.size(), CV_8UC1);

              for(int m = 0 ; m < allImages.size(); m++)
              {
                  //Lecture des images enregistrees dans le dossier une par une
                  img = allImages[m];
                  for(int i = 0 ; i < img.rows ; i ++){
                      for(int j = 0 ; j < img.cols ; j++){
                          //Obtention des valeurs des canaux de l'image originale
                          Vec3b intensite = img.at<Vec3b>(i,j);

                          //Affectation des valeurs dans la matrice de sortie
                          bleu.at<uchar>(i, j) = intensite[0];

                          //Affectation des valeurs dans la matrice de sortie
                          vert.at<uchar>(i, j) = intensite[1];

                          //Affectation des valeurs dans la matrice de sortie
                          rouge.at<uchar>(i, j) = intensite[2];
                      }
                  }
                  // Somme des graients X et Y pour obtenir le gradient total
                  Mat gradient_rouge = Tool::gradient(rouge);
                  Mat gradient_bleu = Tool::gradient(bleu);
                  Mat gradient_vert = Tool::gradient(vert);
                  Mat gradient_rgb = Tool::gradientRGB(gradient_rouge, gradient_bleu, gradient_vert);
                  if(gradient_rgb.cols>768 && gradient_rgb.rows>576){
                  cv::resize(gradient_rgb, dst,imgref.size());
                  imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + m).c_str(), dst);
                  }
                  imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+m).c_str(), gradient_rgb);
              }
              break;
    }
        //GrabCut
    case 14:
    {
        //       clock_t start;
        //       double duration;
        //       start = clock();
        runGrabCut(taillevideo, nouveauDossier, positionSlider, label_videoInitiale, points, maFenetre, traitement);
        //       duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
        //       cout<<"Temps de calcul du GrabCut : "<< duration <<'\n';
        break;
    }

        //Inpainting Telea
    case 15:
    {
        //       clock_t start;
        //       double duration;
        //       start = clock();
        Inpainting *i = new Inpainting();
        i->runInpainting(taillevideo, nouveauDossier, traitement);
        delete i;
        //       duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
        //       cout<<"Temps de calcul de l'inpainting : "<< duration <<'\n';
        break;
    }

        //Inpaiting Criminisi
    case 16:
    {
        clock_t start;
        double duration;
        start = clock();         // perte de   allImages.clear();temps  a revoir rechercher un fichier nombre dans un fichiere
        printf("Cannot Open Image\n");
        break;

        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
           Mat originalImage= allImages[i];

            Mat vecteur_masque = imread(cv::format((nouveauDossier + "/GrabCut_LucasKanade/vecteur_masque/frame%d.tif").c_str(), position+i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
            Mat inpaintMask = imread(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), position+i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
            if(!originalImage.data){
                std::cout<<std::endl<<"Error unable to open input image"<<std::endl;
            }
            Inpainter inp(originalImage,vecteur_masque,16);
            inp.inpaint();
            cv::namedWindow("result");
            cv::imshow("result", inp.result);
            if(inp.result.cols>768 && inp.result.rows>576){
            cv::resize(inp.result, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), i).c_str(), inp.result);
        }
        duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
        cout<<"Temps de calcul de Criminisi : "<< duration <<'\n';
        break;
    }
        //Inpainting avec Image
    case 17:
    {
        //       clock_t start;
        //       double duration;
        //       start = clock();
        Inpainting *in = new Inpainting();
        in->runInpaintingImage(taillevideo, nouveauDossier, traitement, points_image, dirPathImage);
        delete in;
        //       duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
        //       cout<<"Temps de calcul du GrabCut : "<< duration <<'\n';
        break;
    }

        //Inpaiting Criminisi Image
    case 18:
    {
        Mat image = imread(dirPathImage.toStdString(), CV_LOAD_IMAGE_COLOR);
        int w_image = image.cols;
        int h_image = image.rows;

        QPoint secondPoint = points_image.back();
        points_image.pop_back();
        QPoint firstPoint = points_image.back();

        if(firstPoint.x() < 0 || firstPoint.x() > w_image){
            firstPoint.setX(0);
        }
        if(firstPoint.y() < 0 || firstPoint.y() > h_image){
            firstPoint.setY(0);
        }
        if(secondPoint.x() < 0 || secondPoint.x() > w_image){
            secondPoint.setX(w_image - 1);
        }
        if(secondPoint.y() < 0 || secondPoint.y() > h_image){
               secondPoint.setY(h_image - 1);
           }int positiosw=positionSwitch1;
        cv::Rect rectangle;
        rectangle.x = min(firstPoint.x(), secondPoint.x());
        rectangle.y = min(firstPoint.y(), secondPoint.y());
        rectangle.width = abs(firstPoint.x() - secondPoint.x());
        rectangle.height = abs(firstPoint.y() -secondPoint.y());

        Mat croppedImage = image(rectangle);
        imwrite(nouveauDossier + "/" + traitement + "/Image.tif", croppedImage);
        imwrite(nouveauDossier + "/" + traitement + "/Image.png", croppedImage);

        clock_t start;
        double duration;
        start = clock();
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            Mat originalImage = allImages[i];


            Mat inpaintMask = imread(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), position+i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

            if(!originalImage.data){
                std::cout<<std::endl<<"Impossible d'ouvrir l'image"<<std::endl;
            }

            InpaintingImage inp(originalImage,inpaintMask, croppedImage ,64);
            inp.inpaint();
            cv::namedWindow("result");
            cv::imshow("result", inp.result);
            if(inp.result.cols>768 && inp.result.rows>576){
            cv::resize(inp.result, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), position+i).c_str(), inp.result);

        }

        duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
        cout<<"Temps de calcul de Criminisi : "<< duration <<'\n';
        break;
    }

    //#################################################################################"
        //Lucas Kanade
    case 19:
    {
        all_Images=allImages;
        LucasKanade *l = new LucasKanade();
        l->runLukasKanade(positiosw1,positiosw,premiere_fois2,all_Images,position,taillevideo, nouveauDossier, traitement);
        all_Images.clear();
        allImages.clear();
        delete l;
        break;
    }
    //###################################################################################

        //Directions de déplacement
    case 20:
    {
        LucasKanadeDirection *lu = new LucasKanadeDirection();
        lu->runDirectionsDeplacement(taillevideo, nouveauDossier, traitement);
        delete lu;
        break;
    }

        //Carte de chaleur (intensié du déplacement)
    case 21:
    {
        LucasKanadeCarteDeChaleur *luc = new LucasKanadeCarteDeChaleur();
        luc->runCarteDeChaleur(taillevideo, nouveauDossier, traitement);
        delete luc;
        break;
    }

    case 22:
    {
        LucasKanadeDirectionsIntensite *lkdi = new LucasKanadeDirectionsIntensite(allImages);
        lkdi->runDirectionsDeplacementIntensite(taillevideo, nouveauDossier, traitement);
        delete lkdi;
        break;
    }

        //GrabCut Lukas Kanade
    case 23:
    {
        //       clock_t start;
        //       double duration;
        //       start = clock();
        runGrabCutLucasKanade(taillevideo, nouveauDossier, positionSlider, label_videoInitiale, points, maFenetre, traitement);
        //       duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
        //       cout<<"Temps de calcul du GrabCut : "<< duration <<'\n';
        break;
    }

    case 24:
    {
        Dossier::creerDossier(nouveauDossier + "/" +traitement + "/InpaintingFinal/PNG");
        Dossier::creerDossier(nouveauDossier + "/" +traitement + "/InpaintingFinal");

        runGrabCut(taillevideo, nouveauDossier, positionSlider, label_videoInitiale, points, maFenetre, traitement);
        runGrabCut(taillevideo, nouveauDossierVideo, positionSlider, label_videoInpainting, points_video2, maFenetre, traitement);

        InpaintingInverser::runInpaintingInverser(taillevideo, nouveauDossier, traitement, points_video2, nouveauDossierVideo);
        InpaintingInverser::runInpaintingInverser(taillevideo, nouveauDossierVideo, traitement, points, nouveauDossier);

        for(int i = 1; i < taillevideo + 1 ; i++){
            Mat video = imread(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);
            Mat video2 = imread(cv::format((nouveauDossierVideo + "/" + traitement + "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);
            Mat masque2 = imread(cv::format((nouveauDossierVideo + "/" + traitement + "/Masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
            Mat inpaintingInverserFinal = InpaintingInverser::InpaintingInverserFinal(video, video2, masque2);
            if(inpaintingInverserFinal.cols>768 && inpaintingInverserFinal.rows>576){
            cv::resize(inpaintingInverserFinal, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), i).c_str(), inpaintingInverserFinal);

        }
        break;
    }
    case 25:
    {   all_Images=allImages;
        Analyseletk *A = new Analyseletk();
        A->runAnalyseletk( points,positiosw1,positiosw,premiere_fois2,all_Images,position,taillevideo, nouveauDossier, traitement,indice_k);
        all_Images.clear();
        allImages.clear();
        delete A;
        break;
    }

    case 26:
    {
        for(int i = 0 ; i < allImages.size(); i++)
        {
            //Lecture des images enregistrees dans le dossier une par une
            img = allImages[i];
            Mat noirEtBlanc = Tool::noirEtBlanc(img);

            Mat img_bw;
            Mat dist3;
            //modifié
            cout<<"bin4"<<endl;
            cv::threshold(noirEtBlanc, img_bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
          cvtColor(img_bw, dist3, CV_GRAY2RGB);
            //Sauvegarde de la trame en NVG/*"/Noir et Blanc*/
            if(img_bw.cols>768 && img_bw.rows>576){
            cv::resize(dist3, dst,imgref.size());
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/resize/frame%d.tif").c_str(), position + i).c_str(), dst);
            }
            imwrite(cv::format((nouveauDossier + "/" + traitement +  "/frame%d.tif").c_str(), position+i).c_str(), dist3);


        }  allImages.clear();
        break;
     }
     case 27:{

                int positiosw=positionSwitch1;
                all_Images=allImages;
                Etoile *E = new Etoile();
                E->runEtoile_compo(positiosw,premiere_fois2,all_Images,position,taillevideo, nouveauDossier, traitement);
                //E->runEtoile(positiosw,premiere_fois2,all_Images,position,taillevideo, nouveauDossier, traitement);
                all_Images.clear();
                allImages.clear();
                delete E;
                break;
    }
    case 28:{

               int positiosw=positionSwitch1;
               all_Images=allImages;
              etoile_k *E = new etoile_k();
               E->runEtoile_compo(positiosw,premiere_fois2,all_Images,position,taillevideo, nouveauDossier, traitement);
               //E->runEtoile(positiosw,premiere_fois2,all_Images,position,taillevideo, nouveauDossier, traitement);
               all_Images.clear();
               allImages.clear();
               delete E;
               break;
   }
    default:
    {
        cout << "ERREUR : liste ne marche pas" << endl;
    }

}
}

void Traitement::runGrabCut(int taillevideo, string nouveauDossier, int positionSlider, QLabel *label_videoInitiale, vector <QPoint> points, const QWidget* maFenetre,string traitement){
    string chemin = nouveauDossier+"/" +traitement;
    Dossier::creerDossier(nouveauDossier + "/" +traitement + "/Boite_Englobante");
    Dossier::creerDossier(nouveauDossier + "/" +traitement + "/Boite_Englobante/PNG");
    Dossier::creerDossier(chemin + "/Masque");
    Dossier::creerDossier(chemin + "/Masque/PNG");
    Dossier::creerDossier(chemin + "/Objet");
    Dossier::creerDossier(chemin + "/Objet/PNG");
    Dossier::creerDossier(nouveauDossier + "/Inpainting_dil/Masque");
    Dossier::creerDossier(nouveauDossier + "/Inpainting_dil/PNG");
    Dossier::creerDossier(nouveauDossier + "/Inpainting_dil/Masque/PNG");
    Dossier::creerDossier(chemin + "/Masque");
    Dossier::creerDossier(chemin + "/Masque/PNG");

    Mat masquePrecedent;

    for(int j = positionSlider; j < taillevideo + 1 ; j++)
    {

        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_COLOR);
        cout << "Graphecut : " << j << endl;

        GraphCut *g = new GraphCut(maFenetre, label_videoInitiale);
        Mat graph = g->calculerGraphCut(img, points, nouveauDossier+"/" +traitement, j, nouveauDossier);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), j).c_str(), graph);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), j).c_str(), graph);

        Mat masque = imread(cv::format((nouveauDossier + "/" + traitement + "/Masque/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        int somme = cv::sum(masque)[0];
        if(somme <= 0) {
            masque = masquePrecedent;
        }

        vector<vector<Point> > contours;
        Mat dist;

        //Detection de contours en utilisant un seuil
        threshold(masque, dist, 100, 255, THRESH_BINARY);

        //Dectection de contours
        findContours(dist, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        // Approximation de contours des contours et obtenion des boites englobantes

        vector<Rect> boundRect;
        int max = 0;
        Rect Rmax;
        for( int i = 0; i < contours.size(); i++ )
        {
            Rect r  = boundingRect( Mat(contours[i]) );
            int square = r.width*r.height;
            if(square > max){
                max = square;
                Rmax = r;
            }
        }
        boundRect.push_back(Rmax);
        // Dessiner les contours du polygone et la boite englobante
        Mat drawing = g->calculerBoiteEnglobante(contours, boundRect);
        Rect r = boundRect[0];
        Point2i premierPointBoiteEnglobante = boundRect[0].tl();
        Point2i secondPointBoiteEnglobante = boundRect[0].br();

        QPoint premierPointBoiteEnglobanteSuivante(r.x - 10, r.y - 10);
        QPoint secondPointBoiteEnglobanteSuivante(r.x + r.width + 10, r.y + r.height + 10);
        //pour afficher la boote englobante aggrandie
        Point2i premierPointBoiteEnglobanteSuivanteRectangle(r.x - 10, r.y - 10);
        Point2i secondPointBoiteEnglobanteSuivanteRectangle(r.x + r.width + 10, r.y + r.height + 10);
        if(premierPointBoiteEnglobanteSuivante.x() < 0){
            premierPointBoiteEnglobanteSuivante.setX(0);
            premierPointBoiteEnglobanteSuivanteRectangle.x = 0;
        }
        if(premierPointBoiteEnglobanteSuivante.y() < 0){
            premierPointBoiteEnglobanteSuivante.setY(0);
            premierPointBoiteEnglobanteSuivanteRectangle.y = 0;
        }
        if(secondPointBoiteEnglobanteSuivante.x() > img.cols){
            secondPointBoiteEnglobanteSuivante.setX(img.cols - 1);
            secondPointBoiteEnglobanteSuivanteRectangle.x = (img.cols - 1);
        }
        if(secondPointBoiteEnglobanteSuivante.y() > img.rows){
            secondPointBoiteEnglobanteSuivante.setY(img.rows - 1);
            secondPointBoiteEnglobanteSuivanteRectangle.y = (img.rows - 1);
        }

        //        cout << "Premier Point boite englobante suivante X : "<< premierPointBoiteEnglobanteSuivante.x() << endl;
        //        cout << "Premier Point boite englobante suivante Y : "<< premierPointBoiteEnglobanteSuivante.y() << endl;
        //        cout << "Second Point boite englobante suivante X : "<< secondPointBoiteEnglobanteSuivante.x() << endl;
        //        cout << "Second Point boite englobante suivante Y : "<< secondPointBoiteEnglobanteSuivante.y() << endl;

        points.push_back(premierPointBoiteEnglobanteSuivante);
        points.push_back(secondPointBoiteEnglobanteSuivante);

        rectangle( drawing, premierPointBoiteEnglobanteSuivanteRectangle, secondPointBoiteEnglobanteSuivanteRectangle, Scalar(0, 0, 255), 2/*, 8, 0 */);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Boite_Englobante/frame%d.tif").c_str(), j).c_str(), drawing);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Boite_Englobante/PNG/frame%d.png").c_str(), j).c_str(), drawing);
        masquePrecedent = masque;

    }
}








//Calcul du deplacement de l'objet en focntion de la carte de chaleur
void Traitement::runGrabCutLucasKanade(int taillevideo, string nouveauDossier, int positionSlider, QLabel *label_videoInitiale, vector <QPoint> points, const QWidget* maFenetre,string traitement){
    Dossier::creerDossier(nouveauDossier + "/" +traitement + "/Boite_Englobante");
    Dossier::creerDossier(nouveauDossier + "/" +traitement + "/Boite_Englobante/PNG");
    //       Dossier *dot;
    //       dot->creerDossier(nouveauDossier + "/" +traitement + "/Masque_LucasKanade");
    //       delete dot;
    //       Dossier *dotpng;
    //       dotpng->creerDossier(nouveauDossier + "/" +traitement + "/Masque_LucasKanade/PNG");
    //       delete dotpng;
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/vecteur_masque");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/vecteur_masque/PNG");
    Mat masquePrecedent;
    for(int j = positionSlider; j < taillevideo ; j++){
        //         Mat carteDeChaleur = imread(cv::format((nouveauDossier + "/Lucas_Kanade/CarteDeChaleur/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_COLOR);
        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_COLOR);
        //----------------------pour lucas kanade / carte de chaleur
        Mat imgA = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), j+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        cout << "Graphecut : " << j << endl;

        //        Mat img = imread(cv::format((nouveauDossier + "/" + traitement + "/Objet/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_COLOR);

        GraphCut *g = new GraphCut(maFenetre, label_videoInitiale);
        Mat graph = g->calculerGraphCut(img, points, nouveauDossier+"/" +traitement, j, nouveauDossier);
        //            delete g;
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), j).c_str(), graph);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), j).c_str(), graph);

        Mat masque = imread(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        //  Mat masque = imread(cv::format((nouveauDossier + "/" + traitement + "/Masque/frame%d.tif").c_str(), j).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        //           Mat masque_LucasKanade = Mat::zeros(img.size(), img.type());
        //          // imshow("dist", dist);
        //           imshow("masque", masque);
        //           for(int i = 0 ; i < img.rows ; i++){
        //               for(int j = 0 ; j < img.cols; j++){
        //                   if(masque.at<uchar>(i,j) >= 200){
        //                       masque_LucasKanade.at<Vec3b>(i,j) = carteDeChaleur.at<Vec3b>(i,j);
        //                   }
        //                   else masque_LucasKanade.at<Vec3b>(i,j) = 0;
        //               }
        //           }

        //           imwrite(cv::format((nouveauDossier + "/" + traitement + "/Masque_LucasKanade/frame%d.tif").c_str(), j).c_str(), masque_LucasKanade);
        //           imwrite(cv::format((nouveauDossier + "/" + traitement + "/Masque_LucasKanade/PNG/frame%d.png").c_str(), j).c_str(), masque_LucasKanade);

        //----------------------pour lucas kanade / carte de chaleur
        Size img_sz = imgA.size();
        Mat imgC(img_sz, CV_8UC3,cv::Scalar(0,0,0));
        int win_size = 21;
        //nombre maximal de corners
        //           int maxCorners = 2000;
        int maxCorners = 2000000000000000;
        //paramètre caractérisant la qualité minimale de corners de l'image
        //           double qualityLevel = 0.05;
        double qualityLevel = 0.001;
        //distance Euclidienne minimale possible entre les corners retournés
        //           double minDistance = 1.0;
        double minDistance = 0.005;
        //           int blockSize = 3;
        //           int blockSize = 300;
        //           double k = 0.04;
        std::vector<cv::Point2f> cornersA;
        cornersA.reserve(maxCorners);
        std::vector<cv::Point2f> cornersB;
        cornersB.reserve(maxCorners);

        for(int y = 0 ; y < imgA.rows ; y = y + 1){
            for(int x = 0 ; x < imgA.cols ; x = x+ 1){

                cornersA.push_back(Point(x,y));
            }
        }

        for(int y = 0 ; y < imgB.rows ;  y = y + 1){
            for(int x = 0 ; x < imgB.cols ;  x = x+ 1){
                cornersB.push_back(Point(x,y));
            }
        }

        std::vector<uchar> features_found;
        features_found.reserve(maxCorners);
        std::vector<float> feature_errors;
        feature_errors.reserve(maxCorners);

        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);

        Mat carte_de_chaleur(imgA.size(), CV_8UC3,Scalar(255,255,255));

        Mat vecteur_masque(imgA.size(), CV_8UC3, Scalar(0,0,0));

        vector<LineIterator> alllines;
        vector<double> lines_masque;

        vector<Point> li_p0;
        vector<Point> li_p1;
        for( int i=0; i < features_found.size(); i++ ){
            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            // if(dist_euclidienne>=0){
            cv::LineIterator li(carte_de_chaleur, p0, p1);
            // cv::LineIterator lines_m(carte_de_chaleur, p0, p1);
            alllines.push_back(li);
            line( imgC, p0, p1, cv::Scalar(255,255,255), 2 );
            //obtenir les lignes dont le point de depart est a lintérieur du masque

            if(masque.at<uchar>(p0) >= 250){
                lines_masque.push_back(dist_euclidienne);
                li_p0.push_back(p0);
                li_p1.push_back(p1);
                line( vecteur_masque, p0, p1, cv::Scalar(255,255,255), 2 );
            }
            //line(carte_de_chaleur, p0, p1, Scalar(0,255,0));
            //}
        }

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/vecteur_masque/frame%d.tif").c_str(), j).c_str(), vecteur_masque);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/vecteur_masque/PNG/frame%d.png").c_str(), j).c_str(), vecteur_masque);
        sort(lines_masque.begin(), lines_masque.end());

        int index_t = lines_masque.size()*0.95;
        double delta = lines_masque.at(index_t);
        int max_x = -1;
        int max_y = -1;
        int min_y = INT_MAX;
        int min_x = INT_MAX;

        for(int i=0; i < li_p0.size(); i++){
            Point p0 = li_p0.at(i);
            Point p1 = li_p1.at(i);
            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            if(dist_euclidienne <= delta){
                Point p2 = calculerPoint(delta, p1, p0);
                if( minTri(p0.x, p1.x, p2.x) < min_x){
                    min_x =  minTri(p0.x, p1.x, p2.x);
                }

                if( maxTri(p0.x, p1.x, p2.x) > max_x){
                    max_x =  maxTri(p0.x, p1.x, p2.x);
                }
                if( minTri(p0.y, p1.y, p2.y) < min_y){
                    min_y =  minTri(p0.y, p1.y, p2.y);
                }

                if( maxTri(p0.y, p1.y, p2.y) > max_y){
                    max_y =  maxTri(p0.y, p1.y, p2.y);
                }

            }
        }

        int somme = cv::sum(masque)[0];
        if(somme <= 0) {
            masque = masquePrecedent;
        }

        vector<vector<Point> > contours;
        Mat dist;

        //Detection de contours en utilisant un seuil
        threshold(masque, dist, 100, 255, THRESH_BINARY);

        //Dectection de contours
        findContours(dist, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        // Approximation de contours des contours et obtenion des boites englobantes

        vector<Rect> boundRect;

        int max = 0;
        Rect Rmax;
        for( int i = 0; i < contours.size(); i++ )
        {
            Rect r  = boundingRect( Mat(contours[i]) );
            int square = r.width*r.height;
            if(square > max){
                max = square;
                Rmax = r;
            }

        }
        boundRect.push_back(Rmax);
        // Dessiner les contours du polygone et la boite englobante
        Mat drawing = g->calculerBoiteEnglobante(contours, boundRect);

        Rect r = boundRect[0];

        QPoint premierPointBoiteEnglobanteSuivante(min_x-10, min_y-10);
        QPoint secondPointBoiteEnglobanteSuivante(max_x+10, max_y+10);


        //pour afficher la boote englobante aggrandie
        Point2i premierPointBoiteEnglobanteSuivanteRectangle(min_x-10, min_y-10);
        Point2i secondPointBoiteEnglobanteSuivanteRectangle(max_x+10, max_y+10);
        if(premierPointBoiteEnglobanteSuivante.x() < 0){
            premierPointBoiteEnglobanteSuivante.setX(0);
            premierPointBoiteEnglobanteSuivanteRectangle.x = 0;
        }
        if(premierPointBoiteEnglobanteSuivante.y() < 0){
            premierPointBoiteEnglobanteSuivante.setY(0);
            premierPointBoiteEnglobanteSuivanteRectangle.y = 0;
        }
        if(secondPointBoiteEnglobanteSuivante.x() > img.cols){
            secondPointBoiteEnglobanteSuivante.setX(img.cols - 1);
            secondPointBoiteEnglobanteSuivanteRectangle.x = (img.cols - 1);
        }
        if(secondPointBoiteEnglobanteSuivante.y() > img.rows){
            secondPointBoiteEnglobanteSuivante.setY(img.rows - 1);
            secondPointBoiteEnglobanteSuivanteRectangle.y = (img.rows - 1);
        }

        cout << "Premier Point boite englobante suivante X : "<< premierPointBoiteEnglobanteSuivante.x() << endl;
        cout << "Premier Point boite englobante suivante Y : "<< premierPointBoiteEnglobanteSuivante.y() << endl;
        cout << "Second Point boite englobante suivante X : "<< secondPointBoiteEnglobanteSuivante.x() << endl;
        cout << "Second Point boite englobante suivante Y : "<< secondPointBoiteEnglobanteSuivante.y() << endl;

        points.push_back(premierPointBoiteEnglobanteSuivante);
        points.push_back(secondPointBoiteEnglobanteSuivante);

        rectangle( drawing, premierPointBoiteEnglobanteSuivanteRectangle, secondPointBoiteEnglobanteSuivanteRectangle, Scalar(0, 0, 255), 2/*, 8, 0 */);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Boite_Englobante/frame%d.tif").c_str(), j).c_str(), drawing);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Boite_Englobante/PNG/frame%d.png").c_str(), j).c_str(), drawing);
        masquePrecedent = masque;
    }
}


int Traitement::maxTri(int x, int y, int z){
    return std::max(x, std::max(y,z));
}

int Traitement::minTri(int x, int y, int z){
    return std::min(x, std::min(y,z));
}


Point Traitement::calculerPoint(double delta, cv::Point p0, cv::Point p1){
    int x2, y2;
    double dx = p1.x - p0.x;
    double dy = p1.y - p0.y;
    if (dx == 0){// 0 degree ou ligne horizontale
        x2 = p1.x;
        if (dy < 0){
            y2 = (p1.y > delta) ? (p1.y - delta) : (0);
        }
        else y2 = (p1.y + delta);
    }
    else if (dy == 0){ // 90 degree ou ligne verticale
        y2 = p1.y;
        if (dx < 0) x2 = (p1.x > delta) ? (p1.x - delta) : (0);
        else x2 = p1.x + delta;
    }
    else if (dx == 0 && dy == 0){
        std::cout << "Ceci n'est pas une ligne" << endl;
    }
    else{
        double r = dy / dx;
        double alpha = atan(r);
        if (dx > 0){
            y2 = p1.y + delta * sin(alpha);
            x2 = p1.x + delta * cos(alpha);
        }
        else{
            y2 = p1.y - delta * sin(alpha);
            x2 = p1.x - delta * cos(alpha);

        }
    }
    return cv::Point(x2, y2);
}








