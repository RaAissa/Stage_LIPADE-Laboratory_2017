#include "lucaskanadedirection.h"

LucasKanadeDirection::LucasKanadeDirection()
{
}

//void LucasKanadeDirection::runDirectionsDeplacement(int taillevideo, string nouveauDossier, string traitement){

//    Dossier *dffff;
//    dffff->creerDossier(nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage");
//    delete dffff;

//    Dossier *dfdfff;
//    dfdfff->creerDossier(nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage/PNG");
//    delete dfdfff;

//    Dossier *dfffff;
//    dfffff->creerDossier(nouveauDossier + "/" + traitement);
//    delete dfffff;

//    Dossier *ddfffff;
//    ddfffff->creerDossier(nouveauDossier + "/" + traitement +"/PNG");
//    delete ddfffff;

//    for(int m = 1 ; m < taillevideo ; m++)
//    {
//        cout << m <<endl;
//        // Load two images and allocate other structures
//        Mat imgA = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

//        Size img_sz = imgA.size();
//        Mat imgC(img_sz, CV_8UC3,cv::Scalar(0,0,0));
//        int win_size = 21;
//        int maxCorners = 2000000000000000;

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

//        Mat direction = Mat::zeros(imgA.size(), CV_8UC3);
//        double alpha;
//        double dx;
//        double dy;

//        //creer une image avec les resultats
//        for( int i=0; i < features_found.size(); i++ ){
//            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
//            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
//            //dessin du deplacement en fonction des angles
//            dx = (p1.x-p0.x);
//            dy = (p1.y-p0.y);
//            alpha = (-dy/dx);
//            alpha  = atan(alpha);
//            alpha  = 180*alpha/CV_PI;

//            //cout << "alpha : " << alpha << " dx : " << dx << " dy : " << dy<< endl;
//            if(alpha < 45 && alpha > -45 && dx > 0){
//                line( direction, p0, p1, CV_RGB(255, 255, 0), 2 );
//            }
//            else if(alpha < 45 && alpha > -45 && dx < 0){
//                line( direction, p0, p1, CV_RGB(0, 0, 255), 2 );
//            }
//            else if((alpha > 45 && dx > 0) || (alpha < -45 && dx < 0)){
//                line( direction, p0, p1, CV_RGB(255, 0, 0), 2 );
//            }
//            else {
//                line( direction, p0, p1, CV_RGB(0, 255, 0), 2 );
//            }

//        }
//        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_COLOR);

//        Mat direction_dist = Mat::zeros(imgA.size(), CV_8UC3);
//        addWeighted(img, 0.5, direction, 0.5, 0.0, direction_dist);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage/frame%d.tif").c_str(), m).c_str(), direction_dist);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage/PNG/frame%d.png").c_str(), m).c_str(), direction_dist);

//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), m).c_str(), direction);
//        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), m).c_str(), direction);

//        //reinitialisation de limage pour eviter laddition des differents resultats du flot optique dans la meme trame
//        direction_dist.setTo(0);
//        direction.setTo(0);
//    }
//}

void LucasKanadeDirection::runDirectionsDeplacement(int taillevideo, string nouveauDossier, string traitement){

    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement);
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/PNG");
    Dossier::creerDossier(nouveauDossier + "/" + traitement + "/NonNormalise");
    Dossier::creerDossier(nouveauDossier + "/" + traitement +"/NonNormalise/PNG");

    int nombre_dist = 0;
    map<int,int> histogramme;

    for(int m = 1 ; m < taillevideo ; m++)
    {
        cout << m <<endl;
        // Load two images and allocate other structures
        Mat imgA = imread(cv::format((nouveauDossier + "/PNG/frame%d.png").c_str(), m).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        int win_size = 21;
        int maxCorners = INT_MAX;

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

        // Call Lucas Kanade algorithm
        std::vector<uchar> features_found;
        features_found.reserve(maxCorners);
        std::vector<float> feature_errors;
        feature_errors.reserve(maxCorners);

        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);

        Mat direction_trame = Mat::zeros(imgA.size(), CV_8UC3);

        double alpha;
        double dx;
        double dy;

        //creer une image avec les resultats
        for( int i=0; i < features_found.size(); i++ ){
            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            int dist_euclidienne_int = (int) dist_euclidienne;
            nombre_dist++;
            map<int,int>::iterator search = histogramme.find(dist_euclidienne_int);
            if(search != histogramme.end()) {
                //                   std::cout << "Found avant" << search->first << " " << search->second << '\n';
                search->second++;
                //                   std::cout << "Found apres" << search->first << " " << search->second << '\n';
            }
            else {
                //                   std::cout << "Not found\n";
                histogramme.insert(pair<int,int>(dist_euclidienne_int, 1));
            }

            dx = (p1.x-p0.x);
            dy = (p1.y-p0.y);
            alpha = (-dy/dx);
            alpha  = atan(alpha);
            alpha  = 180*alpha/CV_PI;

            //cout << "alpha : " << alpha << " dx : " << dx << " dy : " << dy<< endl;
            if(alpha < 45 && alpha > -45 && dx > 0){
                line( direction_trame, p0, p1, CV_RGB(255, 255, 0), 2 );
            }
            else if(alpha < 45 && alpha > -45 && dx < 0){
                line( direction_trame, p0, p1, CV_RGB(0, 0, 255), 2 );
            }
            else if((alpha > 45 && dx > 0) || (alpha < -45 && dx < 0)){
                line( direction_trame, p0, p1, CV_RGB(255, 0, 0), 2 );
            }
            else {
                line( direction_trame, p0, p1, CV_RGB(0, 255, 0), 2 );
            }
        }

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/frame%d.tif").c_str(), m).c_str(), direction_trame);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/NonNormalise/PNG/frame%d.png").c_str(), m).c_str(), direction_trame);
        //        break;
    }

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

    map<int,int>::iterator it;
    it=histogramme.find (derniere_valeur);
    histogramme.erase ( it, histogramme.end() );

    //************************************************************************************************

    for(int m = 1 ; m < taillevideo ; m++)
    {
        cout << m <<endl;
        // Load two images and allocate other structures
        Mat imgA = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        Mat imgB = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m+1).c_str(), CV_LOAD_IMAGE_GRAYSCALE);

        int win_size = 21;
        int maxCorners = INT_MAX;

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

        // Call Lucas Kanade algorithm
        std::vector<uchar> features_found;
        features_found.reserve(maxCorners);
        std::vector<float> feature_errors;
        feature_errors.reserve(maxCorners);

        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors, Size( win_size, win_size), 5, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3), 0);

        Mat direction = Mat::zeros(imgA.size(), CV_8UC3);
        double alpha;
        double dx;
        double dy;

        //creer une image avec les resultats
        for( int i=0; i < features_found.size(); i++ ){
            Point p0( ceil( cornersA[i].x ), ceil( cornersA[i].y ) );
            Point p1( ceil( cornersB[i].x ), ceil( cornersB[i].y ) );
            double dist_euclidienne = sqrt((p0.x-p1.x)*(p0.x-p1.x) +  (p0.y-p1.y)*(p0.y-p1.y));
            int dist_euclidienne_int = (int) dist_euclidienne;

            //            cout << "derniere_valeur" << derniere_valeur <<endl;

            if(dist_euclidienne_int <= derniere_valeur){
                //dessin du deplacement en fonction des angles
                dx = (p1.x-p0.x);
                dy = (p1.y-p0.y);
                alpha = (-dy/dx);
                alpha  = atan(alpha);
                alpha  = 180*alpha/CV_PI;

                //cout << "alpha : " << alpha << " dx : " << dx << " dy : " << dy<< endl;
                if(alpha < 45 && alpha > -45 && dx > 0){
                    line( direction, p0, p1, CV_RGB(255, 255, 0), 2 );
                }
                else if(alpha < 45 && alpha > -45 && dx < 0){
                    line( direction, p0, p1, CV_RGB(0, 0, 255), 2 );
                }
                else if((alpha > 45 && dx > 0) || (alpha < -45 && dx < 0)){
                    line( direction, p0, p1, CV_RGB(255, 0, 0), 2 );
                }
                else {
                    line( direction, p0, p1, CV_RGB(0, 255, 0), 2 );
                }
            }
        }

        Mat img = imread(cv::format((nouveauDossier + "/frame%d.tif").c_str(), m).c_str(), CV_LOAD_IMAGE_COLOR);

        Mat direction_dist = Mat::zeros(imgA.size(), CV_8UC3);
        addWeighted(img, 0.5, direction, 0.5, 0.0, direction_dist);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage/frame%d.tif").c_str(), m).c_str(), direction_dist);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/DirectionDeDeplacementImage/PNG/frame%d.png").c_str(), m).c_str(), direction_dist);

        imwrite(cv::format((nouveauDossier + "/" + traitement + "/frame%d.tif").c_str(), m).c_str(), direction);
        imwrite(cv::format((nouveauDossier + "/" + traitement + "/PNG/frame%d.png").c_str(), m).c_str(), direction);

        //reinitialisation de limage pour eviter laddition des differents resultats du flot optique dans la meme trame
        direction_dist.setTo(0);
        direction.setTo(0);
    }

}
