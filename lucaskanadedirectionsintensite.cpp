#include "lucaskanadedirectionsintensite.h"
#include <map>

//struct histogramme {
//    int distance;
//    int occurrence;
//};

LucasKanadeDirectionsIntensite::LucasKanadeDirectionsIntensite(vector<Mat> allImages)
{
    all_Images = allImages;
}
//void LucasKanadeDirectionsIntensite::runDirectionsDeplacementIntensite(int taillevideo, string nouveauDossier, string traitement){
//    Dossier *dfffff;
//    dfffff->creerDossier(nouveauDossier + "/" + traitement);
//    delete dfffff;
//    Dossier *ddfffff;
//    ddfffff->creerDossier(nouveauDossier + "/" + traitement +"/PNG");
//    delete ddfffff;
//    Dossier *ddfff;
//    ddfff->creerDossier(nouveauDossier + "/" + traitement +"/NonNormalise");
//    delete ddfff;
//    Dossier *dfff;
//    dfff->creerDossier(nouveauDossier + "/" + traitement +"/NonNormalise/PNG");
//    delete dfff;
//    for(int m = 1 ; m < taillevideo ; m++)
//    {
//        cout << m <<endl;
//        // Load two images and allocate other structures
//        Mat imgA = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//        int win_size = 21;
//        int maxCorners = 2000000000000000;
//        std::vector<cv::Point2f> cornersA;
//        cornersA.reserve(maxCorners);
//        std::vector<cv::Point2f> cornersB;
//        cornersB.reserve(maxCorners);
//        for(int y = 0 ; y < imgA.rows ; y = y + 10){
//            for(int x = 0 ; x < imgA.cols ; x = x+ 10){
//                     cornersA.push_back(Point(x,y));
//            }
//        }
//        for(int y = 0 ; y < imgB.rows ;  y = y + 10){
//            for(int x = 0 ; x < imgB.cols ;  x = x+ 10){
//                    cornersB.push_back(Point(x,y));
//            }
//        }
//        // Call Lucas Kanade algorithm
//        std::vector<uchar> features_found;
//        features_found.reserve(maxCorners);
//        std::vector<float> feature_errors;
//        feature_errors.reserve(maxCorners);
//        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);
//        Mat direction = Mat::zeros(imgA.size(), CV_8UC3);
//        Mat hsv = Mat::zeros(imgA.size(), CV_8UC3);
//        Mat directionIntensite = Mat::zeros(imgA.size(), CV_8UC3);
//        double alpha;
//        double dx;
//        double dy;
//       // double dist_euclidienne = 0;
//        double magnitude_max = -1;
//        std::vector<double> magnitudes;
//        //creer une image avec les resultats
//        for( int i=0; i < features_found.size(); i++ ){
//            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
//            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
//            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
//            magnitudes.push_back(dist_euclidienne);
//            if(magnitude_max < dist_euclidienne){
//                magnitude_max = dist_euclidienne;
//            }
//            //dessin du deplacement en fonction des angles
//            dx = (p1.x-p0.x);
//            dy = (p1.y-p0.y);
//            alpha = (-dy/dx);
//            alpha  = atan(alpha);
//            alpha  = 180*alpha/CV_PI;
//            //cout << "alpha : " << alpha << " dx : " << dx << " dy : " << dy<< endl;
//            if(alpha < 45 && alpha > -45 && dx > 0){
//                    direction.at<Vec3b>(p0.y, p0.x) = (0, 255, 255);
//                    rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 255 ,255),-1 );
//                    //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 255, 255),-1 );
//                    //line( direction, p0, p1, CV_RGB(255, 255, 0), 2 );
//                }
//            else if(alpha < 45 && alpha > -45 && dx < 0){
//                    direction.at<Vec3b>(p0.y, p0.x) = (255, 0, 0);
//                    rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (255, 0, 0),-1 );
//                    //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (255, 0, 0),-1 );
//                    //line( direction, p0, p1, CV_RGB(0, 0, 255), 2 );
//                }
//            else if((alpha > 45 && dx > 0) || (alpha < -45 && dx < 0)){
//                    direction.at<Vec3b>(p0.y, p0.x) = (0, 0, 255);
//                    rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 0, 255),-1 );
//                    //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 0, 255),-1 );
//                    //line( direction, p0, p1, CV_RGB(255, 0, 0), 2 );
//                }
//            else {
//                direction.at<Vec3b>(p0.y, p0.x) = (0, 255, 0);
//                rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 255, 0),-1 );
//                //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 255, 0),-1 );
//                //line( direction, p0, p1, CV_RGB(0, 255, 0), 2 );
//            }
//        }
//         cvtColor(direction, hsv, CV_BGR2HSV);
//         for( int i=0; i < features_found.size(); i++ ){
//             Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
//             int x = p0.x;
//             int y = p0.y;
//             int h = hsv.at<Vec3b>(y, x)[0];
//             int s = (255 * magnitudes[i]/magnitude_max);
//             //int s = hsv.at<Vec3b>(y, x)[1]= 0;
//             int v = hsv.at<Vec3b>(y, x)[2];
//             rectangle(hsv, Rect(p0.x, p0.y,9,9),Scalar (h ,s ,v),-1 );
//         }
//         cvtColor(hsv, directionIntensite, CV_HSV2BGR);
//         imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), m).c_str(), directionIntensite);
//         imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.png").c_str(), m).c_str(), directionIntensite);
//         imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/frame%d.tif").c_str(), m).c_str(), direction);
//         imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/PNG/frame%d.png").c_str(), m).c_str(), direction);
//        //reinitialisation de limage pour eviter laddition des differents resultats du flot optique dans la meme trame
//         direction.setTo(0);
//         hsv.setTo(0);
//         directionIntensite.setTo(0);
//    }
//}

void LucasKanadeDirectionsIntensite::runDirectionsDeplacementIntensite(int taillevideo, string nouveauDossier, string traitement){

    Dossier::creerDossier(nouveauDossier + "/" + traitement);
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/NonNormalise");
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/NonNormalise/PNG");
    //    vector<histogramme> magnitudes;
    map<int,int> histogramme;
    float magnitude_max = -1.0;
    int nombre_dist = 0;
    Mat imgA, imgB, imgC, img, dist, direction, hsv, directionIntensite;
    vector<vector<cv::Vec4i> > allDistances;

    for(int m = 1 ; m < all_Images.size()-1 ; m++)
    {   int l=all_Images.size();
        cout<<l<<endl;
        cout << "Trame : " << m <<endl;
        imgA = all_Images[m];
        imgB = all_Images[m + 1];
        vector<cv::Vec4i> distanceImage;
        int win_size = 21;
        int maxCorners = INT_MAX;
        std::vector<cv::Point2f> cornersA;
        cornersA.reserve(maxCorners);
        std::vector<cv::Point2f> cornersB;
        cornersB.reserve(maxCorners);
        for(int y = 0 ; y < imgA.rows ; y = y + 10){
            for(int x = 0 ; x < imgA.cols ; x = x+ 10){
                cornersA.push_back(Point(x,y));
            }
        }
        for(int y = 0 ; y < imgB.rows ;  y = y + 10){
            for(int x = 0 ; x < imgB.cols ;  x = x+ 10){
                cornersB.push_back(Point(x,y));
            }
        }
        // Call Lucas Kanade algorithm
        std::vector<uchar> features_found;
        features_found.reserve(maxCorners);
        std::vector<float> feature_errors;
        feature_errors.reserve(maxCorners);

        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);

        //creer une image avec les resultats
        //        for( int i=0; i < features_found.size(); i++ ){
        //            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
        //            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
        //            Vec4i p01(p0.x, p0.y, p1.x, p1.y);
        //            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
        //            int dist_euclidienne_int = (int) dist_euclidienne;
        //            nombre_dist++;
        //            map<int,int>::iterator search = histogramme.find(dist_euclidienne_int);
        //            if(search != histogramme.end()) {
        //                //                   std::cout << "Found avant" << search->first << " " << search->second << '\n';
        //                search->second++;
        //                //                   std::cout << "Found apres" << search->first << " " << search->second << '\n';
        //            }
        //            else {
        //                //                   std::cout << "Not found\n";
        //                histogramme.insert(pair<int,int>(dist_euclidienne_int, 1));
        //            }

        //            //            cout << "Trame : " << m << "   dist euc int: " << dist_euclidienne_int << endl;
        //            //        break;
        //        }
        //    }

        for( int i=0; i < features_found.size(); i++ ){
            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
            Vec4i p01(p0.x, p0.y, p1.x, p1.y);
            //           double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            int dist_euclidienne_int = (int) sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            //           int dist_euclidienne_int = (int) sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            nombre_dist++;
            map<int,int>::iterator search = histogramme.find(dist_euclidienne_int);
            distanceImage.push_back(p01);
               if(search != histogramme.end()) {
                    //       std::cout << "Found avant" << search->first << " " << search->second << '\n';
                search->second++;
                    //                   std::cout << "Found apres" << search->first << " " << search->second << '\n';
               }else{
                    //        std::cout << "Not found\n";
                histogramme.insert(pair<int,int>(dist_euclidienne_int, 1));
               }
        }
        allDistances.push_back(distanceImage);
    }
    cout << "fini" << endl;
    int nombre_dist_reduit = nombre_dist*0.95;
    cout << "nombre de dist : " << nombre_dist <<endl;
    cout << "95% du nombre de dist : " << nombre_dist_reduit <<endl;
    int somme = 0;
    int derniere_valeur = 0;
    for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it){
        somme = somme + it->second;
        cout << "somme : " << somme << endl;
        if(somme >= nombre_dist_reduit){
            derniere_valeur = it->first;
            cout << "derniere valeur : " << derniere_valeur << endl;
            break;
        }
    }
    //    cout << "nombre de vecteurs : " << histogramme.size() << endl;
    //    cout << "deplacement max : " <<  magnitude_max << endl;
    //    std::cout << "histogramme contains:\n";
    //    for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it)
    //        std::cout << it->first << " => " << it->second << '\n';
    //    int h = histogramme.size()*0.95;
    //    cout << "histogramme.size() : " << histogramme.size() <<endl;
    //    cout << "histogramme.size()*0.95 : " << h <<endl;
    //    int nombre_dist_reduit = nombre_dist*0.95;
    //    //    cout << "nombre de dist : " << nombre_dist <<endl;
    //    //    cout << "95% du nombre de dist : " << nombre_dist_reduit <<endl;
    //    int somme = 0;
    //    int derniere_valeur = 0;
    //    for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it){
    //        somme = somme + it->second;
    //        //        cout << "somme : " << somme << endl;
    //        if(somme >= nombre_dist_reduit){
    //            derniere_valeur = it->first;
    //            //            cout << "derniere valeur : " << derniere_valeur << endl;
    //            break;
    //        }
    //    }
    magnitude_max = (float)derniere_valeur;
    cout << "magnitude_max : " << magnitude_max <<endl;
    //    map<int,int>::iterator it;
    //    it=histogramme.find (derniere_valeur);
    //    histogramme.erase ( it, histogramme.end() );
    //    std::cout << "histogramme contains apres:\n";
    //    for (map<int,int>::iterator it=histogramme.begin(); it!=histogramme.end(); ++it)
    //        std::cout << it->first << " => " << it->second << '\n';
    //************************************************************************
    //    for(int m = 1 ; m < taillevideo ; m++)
    for(int m = 0 ; m < allDistances.size() ; m++)
    {
        // cout << "Tour 2 : Trame : " << m <<endl;
        // Load two images and allocate other structures
        cout << "jentre " << m << endl;
        // imgC = Mat::zeros(imgA.size(), CV_8UC3);
        vector<Vec4i> distanceImage = allDistances[m];
        //        int win_size = 21;
        //        int maxCorners = INT_MAX;
        //        std::vector<cv::Point2f> cornersA;
        //        cornersA.reserve(maxCorners);
        //        std::vector<cv::Point2f> cornersB;
        //        cornersB.reserve(maxCorners);
        //        for(int y = 0 ; y < imgA.rows ; y = y + 10){
        //            for(int x = 0 ; x < imgA.cols ; x = x+ 10){
        //                cornersA.push_back(Point(x,y));
        //            }
        //        }
        //        for(int y = 0 ; y < imgB.rows ;  y = y + 10){
        //            for(int x = 0 ; x < imgB.cols ;  x = x+ 10){
        //                cornersB.push_back(Point(x,y));
        //            }
        //        }
        //        // Call Lucas Kanade algorithm
        //        std::vector<uchar> features_found;
        //        features_found.reserve(maxCorners);
        //        std::vector<float> feature_errors;
        //        feature_errors.reserve(maxCorners);
        //        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);
        direction = Mat::zeros(imgA.size(), CV_8UC3);
        direction.setTo(Scalar(255,255,255));

        cvtColor(direction, hsv, CV_BGR2HLS);
        std::cout << "h= " << cv::sum(hsv)[0]/(direction.cols*direction.rows) << " s = " << cv::sum(hsv)[1]/(direction.cols*direction.rows) << " v = " << cv::sum(hsv)[2]/(direction.cols*direction.rows) << std::endl;
        //       directionIntensite = Mat::zeros(imgA.size(), CV_8UC3);
        double alpha;
        double dx;
        double dy;
        // double dist_euclidienne = 0;
        vector<int> magnitudes;
        //       directionIntensite.setTo(cv::Scalar(255,255,255));
        //creer une image avec les resultats

        for( int i=0; i < distanceImage.size(); i++ ){
            Vec4i p01 = distanceImage[i];
            Point p0(p01[0], p01[1]);
            Point p1(p01[2], p01[3]);
            float dist_euclidienne_int =  sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            if(dist_euclidienne_int<= derniere_valeur){
                //                line( imgC, p0, p1, cv::Scalar(255,255,255), 2 );
                magnitudes.push_back(dist_euclidienne_int);

                //        for( int i=0; i < features_found.size(); i++ ){
                //            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
                //            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
                //            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
                //            int dist_euclidienne_int = (int) dist_euclidienne;
                //            if(dist_euclidienne_int <= derniere_valeur){
                //                magnitudes.push_back(dist_euclidienne_int);
                //          }
                //dessin du deplacement en fonction des angles
                dx = (p1.x-p0.x);
                dy = (p1.y-p0.y);
                alpha = (-dy/dx);
                alpha  = atan(alpha);
                alpha  = 180*alpha/CV_PI;
                //cout << "alpha : " << alpha << " dx : " << dx << " dy : " << dy<< endl;
                float ratio = (dist_euclidienne_int/(float)derniere_valeur);
                float f = 0.0;
                float a = 128 / ( f - 1);
                float b = 128 - a;
                int l = (int)(a*ratio + b);
                //     cout << "K  : " << k << endl;
                //     cout << "(dist_euclidienne_int/(float)derniere_valeur) : " << (dist_euclidienne_int/(float)derniere_valeur) << endl;
                if(alpha < 45 && alpha > -45 && dx > 0){
                    hsv.at<Vec3b>(p0.y, p0.x) = (0, l, l);
                    rectangle(hsv, Rect(p0.x, p0.y,9,9),Scalar (30, l ,255),-1 );
                      //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 255, 255),-1 );
                      //line( direction, p0, p1, CV_RGB(255, 255, 0), 2 );
                }
                else if(alpha < 45 && alpha > -45 && dx < 0){
                    hsv.at<Vec3b>(p0.y, p0.x) = (l, 0, 0);
                    rectangle(hsv, Rect(p0.x, p0.y,9,9),Scalar (120, l, 255),-1 );
                    //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (255, 0, 0),-1 );
                    //line( direction, p0, p1, CV_RGB(0, 0, 255), 2 );
                }
                else if((alpha > 45 && dx > 0) || (alpha < -45 && dx < 0)){
                    hsv.at<Vec3b>(p0.y, p0.x) = (0, 0, l);
                    rectangle(hsv, Rect(p0.x, p0.y,9,9),Scalar (0, l, 255),-1 );
//                    //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 0, 255),-1 );
//                    //line( direction, p0, p1, CV_RGB(255, 0, 0), 2 );
                }
                else {
                    hsv.at<Vec3b>(p0.y, p0.x) = (0, l, 0);
                    rectangle(hsv, Rect(p0.x, p0.y,9,9),Scalar (60, l, 240),-1 );
//                    //rectangle(direction, Rect(p0.x, p0.y,9,9),Scalar (0, 255, 0),-1 );
//                    //line( direction, p0, p1, CV_RGB(0, 255, 0), 2 );
                }
            }
        }
        //    }

//        cvtColor(direction, hsv, CV_BGR2HSV);
//        //    for( int i=0; i < features_found.size(); i++ ){
//        for(int i = 0 ; i < allDistances.size() ; i++){
//            //        Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
//            Vec4i p01 = distanceImage[i];
//            Point p0(p01[0], p01[1]);
//            int x = p0.x;
//            int y = p0.y;
//            int h = hsv.at<Vec3b>(y, x)[0];
//            float s_f = (255.0 * magnitudes[i]/magnitude_max);
//            int s=(int) s_f;
//            //int s = hsv.at<Vec3b>(y, x)[1]= 0;
//            int v = hsv.at<Vec3b>(y, x)[2];
//            rectangle(hsv, Rect(p0.x, p0.y,9,9),Scalar (h ,s ,v),-1 );
//        }
        cvtColor(hsv, direction, CV_HLS2BGR);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), m+1).c_str(), direction);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), m+1).c_str(), direction);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/frame%d.tif").c_str(), m+1).c_str(), direction);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/PNG/frame%d.png").c_str(), m+1).c_str(), direction);
        magnitudes.clear();
//        directionIntensite.setTo(255,255,255);
    }
    imgA.release();
    imgB.release();
    imgC.release();
    img.release();
    dist.release();
}
