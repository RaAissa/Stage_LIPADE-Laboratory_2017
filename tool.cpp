#include "tool.h"

Mat Tool::noirEtBlanc(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    //Transformation de la trame courante en NVG
    cvtColor(img, dist, CV_BGR2GRAY);
    return dist;
}
void Tool::FindBlobs(Mat binary, std::vector<std::vector<Point2i> >  &blobs, int size)
{
    blobs.clear();
    // Fill the label_image with the blobs
    // 255  - background
    // 0  - unlabelled foreground
    // 256+ - labelled foreground

    cv::Mat imgLabel;
    binary.convertTo(imgLabel, CV_32FC1);
    int label_count = 256; // starts at 256 because 0-255 are used already

    cv::Rect rect;
    std::vector<Point2i> blob;
    int x, y, i, j;
    for (y = 0; y < imgLabel.rows; y++) {
        float *row  = imgLabel.ptr<float>(y);
        for (x = 0; x < imgLabel.cols; x++) {

            if (row[x] != 0) continue;

            blob.clear();

            cv::floodFill(imgLabel, cv::Point2i(x, y), label_count, &rect, 0, 0, size);

            for (i = rect.y; i < (rect.y + rect.height); i++) {
                float *row2  = imgLabel.ptr<float>(i);
                for (j = rect.x; j < (rect.x + rect.width); j++) {

                    if (row2[j] != label_count) continue;

                    blob.push_back(cv::Point2i(j, i));
                }
            }
            blobs.push_back(blob);

            label_count++;
        }
    }
    blob.clear();
    imgLabel.release();
}
Mat Tool::contours(Mat img){
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    Mat src_gray = Mat::zeros(img.size(), img.type());
    Mat grad_x = Mat::zeros(img.size(), CV_8UC1);
    Mat grad_y = Mat::zeros(img.size(), CV_8UC1);
    Mat abs_grad_x = Mat::zeros(img.size(), CV_8UC1);
    Mat abs_grad_y = Mat::zeros(img.size(), CV_8UC1);
    Mat grad = Mat::zeros(img.size(), CV_8UC1);
    //Application du filtre de Gauss afin de reduire le bruit
    GaussianBlur( img, img, Size(3,3), 0, 0, BORDER_DEFAULT );

    // Conversion en NVG
    cvtColor( img, src_gray, CV_BGR2GRAY );

    // Calcul du gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    // Calcul du gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    // Somme des graients X et Y pour obtenir le gradient total
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    return grad;
}

//Calcul pour filtre flouter
Mat Tool::flouter(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    //Application du filtre de Gauss pour rendre l'image floue
    GaussianBlur( img, dist, Size(13,13), 0, 0, BORDER_DEFAULT );
    return dist;
}

//Calcul pour filtre negatif
Mat Tool::negatif(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    //Inversion des couleurs de la trame
    bitwise_not(img, dist);
    return dist;
}

//Calcul pour filtre rouge
Mat Tool::rouge(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = intensite.val[0];
            dist.at<Vec3b>(i, j)[1] = intensite.val[1];
            dist.at<Vec3b>(i, j)[2] = 255 - intensite.val[2];
        }
    }
    return dist;
}

//Calcul pour filtre vert
Mat Tool::vert(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = intensite.val[0];
            dist.at<Vec3b>(i, j)[1] = 255 - intensite.val[1];
            dist.at<Vec3b>(i, j)[2] = intensite.val[2];
        }
    }
    return dist;
}

//Calcul pour filtre bleu
Mat Tool::bleu(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = 255 -intensite.val[0];
            dist.at<Vec3b>(i, j)[1] = intensite.val[1];
            dist.at<Vec3b>(i, j)[2] = intensite.val[2];
        }
    }
    return dist;
}

//Calcul pour filtre enlever teinte
Mat Tool::enleverTeinte(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = 0;
            dist.at<Vec3b>(i, j)[1] = intensite.val[1];
            dist.at<Vec3b>(i, j)[2] = intensite.val[2];
        }
    }
    return dist;
}

//Saturer
Mat Tool::enleverSaturation(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = intensite.val[0];
            dist.at<Vec3b>(i, j)[1] = 255;
            dist.at<Vec3b>(i, j)[2] = intensite.val[2];
        }
    }
    return dist;
}

//Calcul pour filtre enlever brillance
Mat Tool::enleverBrillance(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = intensite.val[0];
            dist.at<Vec3b>(i, j)[1] = intensite.val[1];
            dist.at<Vec3b>(i, j)[2] = 255;
        }
    }
    return dist;
}

//Calcul pour filtre changement
Mat Tool::changement(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = intensite.val[0];
            dist.at<Vec3b>(i, j)[1] = intensite.val[1];
            dist.at<Vec3b>(i, j)[2] = intensite.val[2];
        }
    }
    return dist;
}

//Calcul pour filtre special16
Mat Tool::special16(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            Vec3b intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = (((255/15) * (intensite.val[0] % 16)) + intensite.val[0])/2;
            dist.at<Vec3b>(i, j)[1] = (((255/15) * (intensite.val[1] % 16)) + intensite.val[1])/2;
            dist.at<Vec3b>(i, j)[2] = (((255/15) * (intensite.val[2] % 16)) + intensite.val[2])/2;
        }
    }
    return dist;
}

//Calcul pour filtre special 64
Mat Tool::special64(Mat img){
    Mat dist = Mat::zeros(img.size(), img.type());
    Vec3b intensite = img.at<Vec3b>(0,0);

    for(int i = 0 ; i < img.rows ; i ++){
        for(int j = 0 ; j < img.cols ; j++){
            //Obtention des valeurs des canaux de l'image originale
            intensite = img.at<Vec3b>(i,j);

            //Affectation des valeurs dans la matrice de sortie
            dist.at<Vec3b>(i, j)[0] = ((255/63) * (intensite.val[0] % 64));;
            dist.at<Vec3b>(i, j)[1] = ((255/63) * (intensite.val[1] % 64));
            dist.at<Vec3b>(i, j)[2] = ((255/63) * (intensite.val[2] % 64));
        }
    }
    return dist;
}


//Calcul pour filtre Countours gras
Mat Tool::calculerGradient(Mat gx, Mat gy){
    Mat gt = Mat::zeros(gx.size(), CV_8UC1);
    Mat gn = Mat::zeros(gx.size(), CV_32FC1);
    int largueur = gx.cols;
    int hauteur = gy.rows;
    float max = FLT_MIN;
    float min = FLT_MAX;
    for(int i = 0 ; i < largueur ; i++)
    {
        for(int j = 0 ; j < hauteur ; j++)
        {
            int gX = gx.at<uchar>(j, i);
            int gY = gy.at<uchar>(j, i);

            int gT = sqrt(gX * gX + gY * gY);
            //int gT = (gX + gY)/2;
            if(gT > max)
            {
                max = gT;
            }

            if(gT < min)
            {
                min = gT;
            }
            gn.at<float>(j,i) = gT;

        }
    }

    float delta = max - min;
    float a = (255.0);
    if(delta !=0) a /= delta;
    float b = (-a * min);

    for(int i = 0 ; i < largueur ; i++)
    {
        for(int j = 0 ; j < hauteur ; j++)
        {
            float x = gn.at<float>(j,i);
            float y = a * x + b;

            gt.at<uchar>(j,i) = (uchar)y;
        }
    }

    gn.release();

    return gt;
}

Mat Tool::gradient(Mat src){
    double scale = 1, delta =0;
    int ddepth = CV_16S;
    Mat gx, gy, abs_gx, abs_gy;
    Sobel( src, gx, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( gx, abs_gx );

    Sobel( src, gy, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( gy, abs_gy );

    Mat grad_norm = calculerGradient(abs_gx, abs_gy);

    gx.release();
    gy.release();
    abs_gx.release();
    abs_gy.release();

    return grad_norm;
}

Mat Tool::gradientRGB(Mat grad_r, Mat grad_g, Mat grad_b){
    Mat dist = Mat::zeros(grad_r.size(), grad_r.type());
    int largueur = grad_r.cols;
    int hauteur = grad_r.rows;

    for(int i = 0 ; i < largueur ; i++)
    {
        for(int j = 0 ; j < hauteur ; j++)
        {
            float x = grad_r.at<uchar>(j,i) + grad_g.at<uchar>(j,i) + grad_b.at<uchar>(j,i);
            if(x > 200)
            {
                dist.at<uchar>(j,i) = 255;
            }
            else dist.at<uchar>(j,i) = 0;
        }
    }
    return dist;
}

