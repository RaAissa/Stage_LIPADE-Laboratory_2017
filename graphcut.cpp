#include "graphcut.h"
#include "QMouseEvent"

GraphCut::GraphCut(const QWidget* maFenetre, QLabel* lblImage){
    _maFenetre = maFenetre;
    _lblImage = lblImage;
    w = _lblImage->width();
    h = _lblImage->height();
}

Mat GraphCut::calculerFond(Mat result, Mat img){
    Mat3b fond = Mat3b::zeros(result.size());
    for(int i = 0 ; i < result.rows ; i++){
        for(int j = 0 ; j < result.cols; j++){
            if(result.at<uchar>(i,j) == 0){
                fond.at<Vec3b>(i,j) = img.at<Vec3b>(i,j);
            }
            else fond.at<Vec3b>(i,j) = 0;
        }
    }
    return fond;
}

Mat GraphCut::calculerGraphCut(Mat image, vector<QPoint> points, String chemin, int i, string nouveauDossier){
    //Verification si limage a bien pu s'ouvrir
    if (!image.data)
    {
        cout << "Impossible d'ouvrir l'image" << std::endl;
        //return -1;
    }
    QPoint secondPoint = points.back();
    points.pop_back();
    QPoint firstPoint = points.back();
    //    if(firstPoint.x < 0 || firstPoint.x > w){
    //        firstPoint.x = 0;
    //    }
    //    if(firstPoint.y < 0 || firstPoint.y > h){
    //        firstPoint.y = 0;
    //    }
    //    if(secondPoint.x < 0 || secondPoint.x > w){
    //        secondPoint.x = w - 1;
    //    }
    //    if(secondPoint.y < 0 || secondPoint.y > h){
    //        secondPoint.y = h - 1;
    //    }

    if(firstPoint.x() < 0 || firstPoint.x() > w){
        firstPoint.setX(0);
    }
    if(firstPoint.y() < 0 || firstPoint.y() > h){
        firstPoint.setY(0);
    }
    if(secondPoint.x() < 0 || secondPoint.x() > w){
        secondPoint.setX(w - 1);
    }
    if(secondPoint.y() < 0 || secondPoint.y() > h){
        secondPoint.setY(h - 1);
    }

    cv::Rect rectangle;
    rectangle.x = min(firstPoint.x(), secondPoint.x());
    rectangle.y = min(firstPoint.y(), secondPoint.y());
    rectangle.width = abs(firstPoint.x() - secondPoint.x());
    rectangle.height = abs(firstPoint.y() -secondPoint.y());

    cv::Mat result;
    cv::Mat bgModel, fgModel;

    // Segmentation GrabCut
    cv::grabCut(image, result, rectangle, bgModel, fgModel, 1, cv::GC_INIT_WITH_RECT);
    // Obtenir les pixels marques comme fond
    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
    // Generer l'image du resultat
    cv::Mat objet(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
    //image contenant l'objet
    image.copyTo(objet, result);

    Mat fond = calculerFond(result, image);
    imwrite(cv::format((chemin + "/Masque/frame%d.tif").c_str(), i).c_str(), result);
    imwrite(cv::format((chemin + "/Masque/PNG/frame%d.png").c_str(), i).c_str(), result);

    Mat masque_dil;
    int dilation_size = 1;
    //Creation de l'element strcuturant pour la dilatation
    Mat element = getStructuringElement(MORPH_RECT, Size( 2*dilation_size + 1, 2*dilation_size+1 ), Point( dilation_size, dilation_size ) );

    //Dilatation du masque
    dilate( result, masque_dil, element );

    vector<vector<Point2i> > contours;

    //Seuillage du masque
    Mat tmp_masque = masque_dil < 230;
    bitwise_not(tmp_masque,tmp_masque);

    Mat vrai_objet(result.size(), result.type(), Scalar(0));

    //Detection des contours
    findContours(tmp_masque, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0,0));

    //Obtention des contous exterieurs
    int max = 0;
    int objectIdx = 0;
    for(int i = 0 ; i < contours.size() ; i++){
        vector<Point2i> CC = contours[i];
        if(max < CC.size()){
            max = CC.size();
            objectIdx = i;
        }
    }
    drawContours(vrai_objet, contours, objectIdx, Scalar(100),-1);
    imwrite(cv::format((nouveauDossier + "/Inpainting_dil/Masque/frame%d.tif").c_str(), i).c_str(), vrai_objet);
    imwrite(cv::format((nouveauDossier + "/Inpainting_dil/Masque/PNG/frame%d.png").c_str(), i).c_str(), vrai_objet);
    imwrite(cv::format((chemin + "/Objet/frame%d.tif").c_str(), i).c_str(), objet);
    imwrite(cv::format((chemin + "/Objet/PNG/frame%d.png").c_str(), i).c_str(), objet);
    return fond;
}

Mat GraphCut::calculerBoiteEnglobante(vector<vector<Point> > contours_poly, vector<Rect> boundRect){
    Mat drawing = Mat::zeros( h, w, CV_8UC3 );
    int nb_contours = contours_poly.size();
    for( int i = 0; i< nb_contours ; i++ )
    {
        vector<Point> contour = contours_poly.at(i);
        int nb_contour_points = contour.size();
        for(int j = 0 ; j < nb_contour_points ; j++){
            line(drawing, contour[j], contour[(j+1)%nb_contour_points],Scalar(255, 0, 0), 1);
        }
    }
    rectangle( drawing, boundRect[0], Scalar(255, 0, 0), 2);
    return drawing;
}


