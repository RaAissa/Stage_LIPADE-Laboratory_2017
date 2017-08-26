#include "inpainting.h"

Inpainting::Inpainting()
{
}

Mat Inpainting::calculerInpaintingTelea(Mat img, Mat masque){
    Mat inpainting;//= Mat::zeros(img.size(), img.type());
    cv::inpaint(img, masque, inpainting, 3, INPAINT_TELEA);
    calculerPixels(masque);
    return inpainting;
}

Mat Inpainting::calculerIntersection(Mat masque, Mat grabCut, Mat inpaintin){
    Mat resultat = Mat::zeros(grabCut.size(), grabCut.type());
    for(int i = 0 ; i < masque.rows ; i++){
        for(int j = 0 ; j < masque.cols; j++){
            if(masque.at<uchar>(i,j) >= 230){
                resultat.at<Vec3b>(i,j) = inpaintin.at<Vec3b>(i,j);
            }
            else resultat.at<Vec3b>(i,j) = grabCut.at<Vec3b>(i,j);
        }
    }
    return resultat;
}

void Inpainting::calculerPixels(Mat result){
    float total = 0.0;
    float blanc = 0.0;
    float noir = 0.0;
    for(int i = 0 ; i < result.rows ; i++){
        for(int j = 0 ; j < result.cols; j++){
            total++;
            if(result.at<uchar>(i,j) >= 230){
                blanc++;
            }
            else noir++;
        }
    }
    //    cout << "Nombre total de Pixels : " << total << endl;
    //    cout << "Nombre de Pixels blancs: " << blanc << endl;
    //    cout << "Nombre de Pixels noirs : " << noir << endl;
    //    cout << "Taille du masque : " << (float) (blanc/total)*100 << endl;
}

Mat Inpainting::calculerRectangleInscrit(Mat masque, int &hauteur, Rect &recPrecedent){
    vector<vector<Point> > contours;
    Mat masque_contours = masque.clone();

    //Dectection de contours
    findContours(masque_contours, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
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
    Mat drawing = calculerBoiteEnglobantee(contours, boundRect, masque);

    Point2i premierPointBoiteEnglobante = boundRect[0].tl();
    Point2i secondPointBoiteEnglobante = boundRect[0].br();


    Rect re;
    int largeur_boiteEnglobante = (secondPointBoiteEnglobante.y-premierPointBoiteEnglobante.y);
    int hauteur_boiteEnglobante = (secondPointBoiteEnglobante.x-premierPointBoiteEnglobante.x);
    int diff_hw;
    int max_cote;
    if(largeur_boiteEnglobante >= hauteur_boiteEnglobante){
        max_cote = largeur_boiteEnglobante;
        diff_hw = (largeur_boiteEnglobante - hauteur_boiteEnglobante);
        re.x = (premierPointBoiteEnglobante.x - (diff_hw/2));
        re.y = (premierPointBoiteEnglobante.y );
        re.width =  max_cote;
        re.height = max_cote;
    } else {
        max_cote = hauteur_boiteEnglobante;
        diff_hw = (hauteur_boiteEnglobante - largeur_boiteEnglobante);
        re.x = (premierPointBoiteEnglobante.x );
        re.y = (premierPointBoiteEnglobante.y - (diff_hw/2));
        re.width =  max_cote;
        re.height = max_cote ;
    }

    //TODO
    //     if(premierPoint.x < 0 || premierPoint.x > w_masque){
    //         premierPoint.x = 0;
    //     }
    //     if(premierPoint.y < 0 || premierPoint.y > h_masque){
    //         premierPoint.y = 0;
    //     }
    //     if(secondPoint.x < 0 || secondPoint.x > w_masque){
    //         secondPoint.x = (w_masque - 1);
    //     }
    //     if(secondPoint.y < 0 || secondPoint.y > h_masque){
    //         secondPoint.y = (h_masque - 1);
    //     }

    Mat dist_compare;
    Mat image_rect;
//    int hauteurPrecedente;
    do {
        image_rect = Mat::zeros(masque.size(), masque.type());
        rectangle(image_rect, re, 255, -1);
        Mat dist_bitwise = Mat::zeros(masque.size(), masque.type());
        dist_compare = Mat::zeros(masque.size(), masque.type());

        bitwise_and(masque, image_rect, dist_bitwise);
        compare(dist_bitwise, image_rect, dist_compare, CMP_NE);

        re.x = re.x+1;
        re.y = re.y+1;
        re.width = re.width-2;
        re.height = re.height-2;
        hauteur = re.height+2;

        if((re.width <= 0) || (re.height <= 0)){
            cout << "Impossible de faire inpainting : rectangle impossible de trouver" << endl;
            re.x = recPrecedent.x;
            re.y = recPrecedent.y;
            re.width = recPrecedent.width;
            re.height = recPrecedent.height;
            hauteur = recPrecedent.height;
            break;
        }
    } while (countNonZero(dist_compare) > 0);

    recPrecedent = re;

    return image_rect;
}

Mat Inpainting::calculerBoiteEnglobantee(vector<vector<Point> > contours_poly, vector<Rect> boundRect, Mat masque){
    Mat drawing = Mat::zeros( masque.size(), CV_8UC3 );

    for( int i = 0; i< contours_poly.size(); i++ )
    {
        vector<Point> contour = contours_poly.at(i);
        for(int j = 0 ; j < contour.size(); j++){
            line(drawing, contour[j], contour[(j+1)%contour.size()],Scalar(255, 0, 0), 1);
        }
        Rect r = boundRect[i];
        rectangle( drawing, r, Scalar(255, 0, 0), 2);
    }

    return drawing;
}

Mat Inpainting::resizeImage(Mat image, int hauteur){
    Mat resizedImage = Mat::zeros(image.size(), image.type());
    Size size(hauteur,hauteur);
    resize(image,resizedImage, size, INTER_LINEAR);
    return resizedImage;
}

Mat Inpainting::calculerMasque(Mat masque, Mat rectangleInscrit){
    Mat nouveauMasque = Mat::zeros(masque.size(), masque.type());
    for(int i = 0 ; i < masque.rows ; i++){
        for(int j = 0 ; j < masque.cols; j++){
            if(rectangleInscrit.at<uchar>(i,j) >= 250){
                nouveauMasque.at<uchar>(i,j) = 0;
            }
            else nouveauMasque.at<uchar>(i,j) = masque.at<uchar>(i,j);
        }
    }
    return nouveauMasque;
}

Mat Inpainting::copierImageDansTrame(Mat img, Mat rectangleInscrit, Mat image){
    Mat result = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i++){
        for(int j = 0 ; j < img.cols; j++){
            if(rectangleInscrit.at<uchar>(i,j) >= 250){
                result.at<Vec3b>(i,j) = image.at<Vec3b>(i,j);
            }
            else result.at<Vec3b>(i,j) = img.at<Vec3b>(i,j);
        }
    }
    return result;
}

Mat Inpainting::resizedImageTailleTramme(Mat rectangleInscrit, Mat resizedImage, int hauteur){
    Mat3b res = Mat3b::zeros(rectangleInscrit.size());
    Point p;
    int found = 0;
    for(int i = 0 ; i < rectangleInscrit.rows ; i++){
        for(int j = 0 ; j < rectangleInscrit.cols; j++){
            if(!found && rectangleInscrit.at<uchar>(i,j) >= 250){
                p.x = j;
                p.y = i;
                found = 1;

            }
        }
        if (found) {
            break;
        }
    }
    for(int i = 0 ; i < resizedImage.rows ; i++){
        for(int j = 0 ; j < resizedImage.cols; j++){
            res.at<Vec3b>(i+p.y,j+p.x) = resizedImage.at<Vec3b>(i,j);
        }
    }
    return res;
}

Mat Inpainting::calculerInpaintingTeleaImage(Mat img, Mat masque){
    Mat inpainting;//= Mat::zeros(img.size(), img.type());
    cv::inpaint(img, masque, inpainting, 3, INPAINT_TELEA);
    calculerPixels(masque);
    return inpainting;
}

Mat Inpainting::copierInpaintingeDansTrame(Mat img, Mat inpainting_rectangleInscrit, Rect r){
    Mat resultat = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < inpainting_rectangleInscrit.rows ; i++){
        for(int j = 0 ; j < inpainting_rectangleInscrit.cols; j++){
            resultat.at<Vec3b>(i+r.y,j+r.x) = inpainting_rectangleInscrit.at<Vec3b>(i,j);
        }
    }
    return resultat;
}

void Inpainting::runInpaintingImage(int taillevideo, string nouveauDossier, string traitement, vector <QPoint> points_image, QString dirPathImage){
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
    }

    cv::Rect rectangle;
    rectangle.x = min(firstPoint.x(), secondPoint.x());
    rectangle.y = min(firstPoint.y(), secondPoint.y());
    rectangle.width = abs(firstPoint.x() - secondPoint.x());
    rectangle.height = abs(firstPoint.y() -secondPoint.y());

    Mat croppedImage = image(rectangle);
    imwrite(nouveauDossier + "/" + traitement + "/Image.tif", croppedImage);
    imwrite(nouveauDossier + "/" + traitement + "/Image.png", croppedImage);

    Mat masquePrecedent;

    Rect rectanglePourPrecedent;
    for(int i = 1; i < taillevideo + 1 ; i++)
    {
        cout << "I : " << i << endl;
        Mat image = imread(cv::format((nouveauDossier + "/" + traitement +"/Image.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);
        Mat vrai_objet = imread(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);

        for(int i = 0 ; i < vrai_objet.rows ; i ++){
            for(int j = 0 ; j < vrai_objet.cols ; j++){
                if(vrai_objet.at<uchar>(i, j) >= 205)
                {
                    vrai_objet.at<uchar>(i, j) = 255;
                }
                else
                {
                    vrai_objet.at<uchar>(i, j) = 0;
                }
            }
        }

        //Inpainting avec le masque initial
        Mat inpainting = this->calculerInpaintingTelea(img, vrai_objet);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/GrabCutInpainting/frame%d.tif").c_str(), i).c_str(), inpainting);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/GrabCutInpainting/PNG/frame%d.png").c_str(), i).c_str(), inpainting);

        int somme = cv::sum(vrai_objet)[0];
        if(somme <= 0) {
            vrai_objet = masquePrecedent;
        }

        vector<vector<Point> > contours;
        Mat dist;

        //Detection de contours en utilisant un seuil
        threshold(vrai_objet, dist, 100, 255, THRESH_BINARY);

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

        Mat drawing = this->calculerBoiteEnglobantee(contours, boundRect, vrai_objet);

        Rect r = boundRect[0];

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Boite_Englobante/frame%d.tif").c_str(), i).c_str(), drawing);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Boite_Englobante/PNG/frame%d.png").c_str(), i).c_str(), drawing);
        masquePrecedent = vrai_objet;

        int hauteur = 0;

        Mat rectangleInscrit = this->calculerRectangleInscrit(vrai_objet, hauteur, rectanglePourPrecedent);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/RectangleInscrit/frame%d.tif").c_str(), i).c_str(), rectangleInscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/RectangleInscrit/PNG/frame%d.png").c_str(), i).c_str(), rectangleInscrit);

        Mat resizedImage = this->resizeImage(image, hauteur);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/ResizedImage/frame%d.tif").c_str(), i).c_str(), resizedImage);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/ResizedImage/PNG/frame%d.png").c_str(), i).c_str(), resizedImage);

        Mat resizedImageTailleTramme = this->resizedImageTailleTramme(rectangleInscrit,resizedImage, hauteur);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/resizedImageTailleTramme/frame%d.tif").c_str(), i).c_str(), resizedImageTailleTramme);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/resizedImageTailleTramme/PNG/frame%d.png").c_str(), i).c_str(), resizedImageTailleTramme);

        Mat rectangle_circonscrit = resizedImageTailleTramme(r);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Rectangle_Circonscrit/frame%d.tif").c_str(), i).c_str(), rectangle_circonscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Rectangle_Circonscrit/PNG/frame%d.png").c_str(), i).c_str(), rectangle_circonscrit);

        Mat nouveauMasque = this->calculerMasque(vrai_objet, rectangleInscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasque/frame%d.tif").c_str(), i).c_str(), nouveauMasque);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasque/PNG/frame%d.png").c_str(), i).c_str(), nouveauMasque);

        Mat nouveauMasquecropped = nouveauMasque(r);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasqueCropped/frame%d.tif").c_str(), i).c_str(), nouveauMasquecropped);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NouveauMasqueCropped/PNG/frame%d.png").c_str(), i).c_str(), nouveauMasquecropped);

        Mat inpainting_rectangleInscrit = this->calculerInpaintingTelea(rectangle_circonscrit, nouveauMasquecropped);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit/frame%d.tif").c_str(), i).c_str(), inpainting_rectangleInscrit);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingRectangleInscrit/PNG/frame%d.png").c_str(), i).c_str(), inpainting_rectangleInscrit);

        Mat inpaintingRectangleInscrit_DansTrame = this->copierInpaintingeDansTrame(img, inpainting_rectangleInscrit, r);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingDansTrame/frame%d.tif").c_str(), i).c_str(), inpaintingRectangleInscrit_DansTrame);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/InpaintingDansTrame/PNG/frame%d.png").c_str(), i).c_str(), inpaintingRectangleInscrit_DansTrame);

        Mat inpaintingFinal = Mat::zeros(img.size(), img.type());
        addWeighted(inpainting,0.7, inpaintingRectangleInscrit_DansTrame, 1, 0.0, inpaintingFinal);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), i).c_str(), inpaintingFinal);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), i).c_str(), inpaintingFinal);
    }
}

void Inpainting::runInpainting(int taillevideo, string nouveauDossier, string traitement){
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "_Intersection");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "_Intersection/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Inpainting_Masque_nonDil/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/Inpainting_Masque_nonDil");

    for(int i = 1; i < taillevideo +1 ; i++)
    {
        Mat masque = imread(cv::format((nouveauDossier + "/GrabCut/Masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat vrai_objet = imread(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);
        Mat grabCut = imread(cv::format((nouveauDossier + "/GrabCut/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_COLOR);

//        Mat vecteur_masque = imread(cv::format((nouveauDossier + "/GrabCut_LucasKanade/vecteur_masque/frame%d.tif").c_str(), i).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        //Inpainting avec le masque initial
        Mat inpainting = this->calculerInpaintingTelea(img, vrai_objet);


        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Inpainting_Masque_nonDil/frame%d.tif").c_str(), i).c_str(), inpainting);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/Inpainting_Masque_nonDil/PNG/frame%d.png").c_str(), i).c_str(), inpainting);

        //Inpainting avec le masque dilate et sans trous
        Mat inpaintin = this->calculerInpaintingTelea(img, vrai_objet);
        Mat intersection = this->calculerIntersection(masque, grabCut, inpaintin);

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), i).c_str(), inpaintin);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), i).c_str(), inpaintin);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "_Intersection/frame%d.tif").c_str(), i).c_str(), intersection);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "_Intersection/PNG/frame%d.png").c_str(), i).c_str(), intersection);
    }
}

