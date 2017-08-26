#include "inpaintinginverser.h"

void InpaintingInverser::runInpaintingInverser(int taillevideo, string nouveauDossier, string traitement, vector <QPoint> points_image, string nouveauDossierVideo){

    Dossier::creerDossier(nouveauDossier + "/" + traitement);
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/GrabCutInpainting");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/GrabCutInpainting/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Boite_Englobante");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Boite_Englobante/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Rectangle_Circonscrit");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Rectangle_Circonscrit/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/NouveauMasque");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/NouveauMasque/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/NouveauMasqueCropped");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/NouveauMasqueCropped/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/ResizedImage");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/ResizedImage/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/resizedImageTailleTramme");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/resizedImageTailleTramme/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/InpaintingDansTrame");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/InpaintingDansTrame/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/RectangleInscrit");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/RectangleInscrit/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Video2");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Video2/PNG");

    Mat masquePrecedent;

    Rect rectanglePourPrecedent;
    for(int i = 1; i < taillevideo + 1 ; i++)
    {

        Mat image = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);
        Mat image2 = imread(cv::format((nouveauDossierVideo + "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);

        Mat masque = imread(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat masque2 = imread(cv::format((nouveauDossierVideo + "/Inpainting_dil/Masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        for(int i = 0 ; i < masque2.rows ; i ++){
            for(int j = 0 ; j < masque2.cols ; j++){
                if(masque2.at<uchar>(i, j) >= 205)
                {
                    masque2.at<uchar>(i, j) = 255;
                }
                else
                {
                    masque2.at<uchar>(i, j) = 0;
                }
            }
        }

        int somme = cv::sum(masque2)[0];
        if(somme <= 0) {
            masque2 = masquePrecedent;
        }

        vector<vector<Point> > contours;
        Mat dist;

        //Detection de contours en utilisant un seuil
        threshold(masque2, dist, 100, 255, THRESH_BINARY);

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

        Rect r = boundRect[0];
        Rect rec_bounding;
        rec_bounding.x = (r.tl().x /*- 5*/);
        rec_bounding.y = (r.tl().y /*- 5*/);
        rec_bounding.width = abs(r.br().x /*+ 5*/ - rec_bounding.x);
        rec_bounding.height = abs(r.br().y /*+ 5*/ - rec_bounding.y);

        Mat croppedImage = image2(rec_bounding);

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Video2/frame%d.tif").c_str(), i).c_str(), croppedImage);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Video2/PNG/frame%d.png").c_str(), i).c_str(), croppedImage);


        ////    Mat masquePrecedent;

        ////    Rect rectanglePourPrecedent;
        ////    for(int i = 1; i < taillevideo + 1 ; i++)
        ////    {
        //        cout << "I : " << i << endl;
        //        Mat image = imread(cv::format((nouveauDossier + "/" + traitement +"/Image.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);
        //        Mat vrai_objet = imread(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        //        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);

        //        for(int i = 0 ; i < vrai_objet.rows ; i ++){
        //            for(int j = 0 ; j < vrai_objet.cols ; j++){
        //                if(vrai_objet.at<uchar>(i, j) >= 205)
        //                {
        //                    vrai_objet.at<uchar>(i, j) = 255;
        //                }
        //                else
        //                {
        //                    vrai_objet.at<uchar>(i, j) = 0;
        //                }
        //            }
        //        }

        //Inpainting avec le masque initial
        Inpainting *in = new Inpainting();
        Mat inpainting = in->calculerInpaintingTelea(image, masque);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/GrabCutInpainting/frame%d.tif").c_str(), i).c_str(), inpainting);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/GrabCutInpainting/PNG/frame%d.png").c_str(), i).c_str(), inpainting);

        int somm = cv::sum(masque)[0];
        if(somm <= 0) {
            masque = masquePrecedent;
        }

        vector<vector<Point> > contour;
        Mat dis;

        //Detection de contours en utilisant un seuil
        threshold(masque, dis, 100, 255, THRESH_BINARY);

        //Dectection de contours
        findContours(dis, contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        // Approximation de contours des contours et obtenion des boites englobantes

        vector<Rect> boundRect2;

        int max2 = 0;
        Rect Rmax2;
        for( int i = 0; i < contour.size(); i++ )
        {
            Rect re  = boundingRect( Mat(contour[i]) );
            int square = r.width*r.height;
            if(square > max2){
                max2 = square;
                Rmax2 = re;
            }

        }
        boundRect2.push_back(Rmax2);
        // Dessiner les contours du polygone et la boite englobante

        Mat drawing = in->calculerBoiteEnglobantee(contour, boundRect2, masque);

        Rect re = boundRect2[0];

        int hauteur = 0;

        Mat rectangleInscrit = in->calculerRectangleInscrit(masque, hauteur, rectanglePourPrecedent);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/RectangleInscrit/frame%d.tif").c_str(), i).c_str(), rectangleInscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/RectangleInscrit/PNG/frame%d.png").c_str(), i).c_str(), rectangleInscrit);

        Mat resizedImage = in->resizeImage(croppedImage, hauteur);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/ResizedImage/frame%d.tif").c_str(), i).c_str(), resizedImage);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/ResizedImage/PNG/frame%d.png").c_str(), i).c_str(), resizedImage);

        Mat resizedImageTailleTramme = in->resizedImageTailleTramme(rectangleInscrit,resizedImage, hauteur);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/resizedImageTailleTramme/frame%d.tif").c_str(), i).c_str(), resizedImageTailleTramme);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/resizedImageTailleTramme/PNG/frame%d.png").c_str(), i).c_str(), resizedImageTailleTramme);

        Mat rectangle_circonscrit = resizedImageTailleTramme(re);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Rectangle_Circonscrit/frame%d.tif").c_str(), i).c_str(), rectangle_circonscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Rectangle_Circonscrit/PNG/frame%d.png").c_str(), i).c_str(), rectangle_circonscrit);

        Mat nouveauMasque = in->calculerMasque(masque, rectangleInscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasque/frame%d.tif").c_str(), i).c_str(), nouveauMasque);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasque/PNG/frame%d.png").c_str(), i).c_str(), nouveauMasque);

        Mat nouveauMasquecropped = nouveauMasque(re);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasqueCropped/frame%d.tif").c_str(), i).c_str(), nouveauMasquecropped);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasqueCropped/PNG/frame%d.png").c_str(), i).c_str(), nouveauMasquecropped);

        Mat inpainting_rectangleInscrit = in->calculerInpaintingTelea(rectangle_circonscrit, nouveauMasquecropped);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit/frame%d.tif").c_str(), i).c_str(), inpainting_rectangleInscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit/PNG/frame%d.png").c_str(), i).c_str(), inpainting_rectangleInscrit);

        Mat inpaintingRectangleInscrit_DansTrame = in->copierInpaintingeDansTrame(image, inpainting_rectangleInscrit, re);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingDansTrame/frame%d.tif").c_str(), i).c_str(), inpaintingRectangleInscrit_DansTrame);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingDansTrame/PNG/frame%d.png").c_str(), i).c_str(), inpaintingRectangleInscrit_DansTrame);

        Mat inpaintingFinal = Mat::zeros(image.size(), image.type());
        addWeighted(inpainting,0.7, inpaintingRectangleInscrit_DansTrame, 1, 0.0, inpaintingFinal);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), i).c_str(), inpaintingFinal);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), i).c_str(), inpaintingFinal);
    }
}

Mat InpaintingInverser::InpaintingInverserFinal(Mat video, Mat video2, Mat masque){
    Mat inpaintingFinal = Mat::zeros(video.size(), video.type());
    for(int i = 0 ; i < video.rows ; i++){
        for(int j = 0 ; j < video.cols; j++){
            if(masque.at<uchar>(i,j) == 0){
                inpaintingFinal.at<Vec3b>(i,j) = video.at<Vec3b>(i,j);
            }
            else inpaintingFinal.at<Vec3b>(i,j) = video2.at<Vec3b>(i,j);
        }
    }
    return inpaintingFinal;
}
